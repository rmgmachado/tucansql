/*****************************************************************************\
*  Copyright (c) 2022 Tucan Software Pty Ltd. All rights reserved.
*
*  MIT License
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to
*  deal in the Software without restriction, including without limitation the
*  rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
*  sell copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in
*  all copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
*  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
*  IN THE SOFTWARE.
*
*  You should have received a copy of the MIT License along with this program.
*  If not, see https://opensource.org/licenses/MIT.
\*****************************************************************************/
#pragma once

#include <functional>

#include "value.h"
#include "scanner.h"
#include "ptree.h"
#include "memdb.h"
#include "stack.h"
#include "status.h"

int sql_parser(void* pt);

namespace tucan {

   class parser_t
   {
      std::string stmt_;
      status_t error_;
      std::string errmsg_;
      ptree_t* ptree_;
      scanner_t scan_;
      database_t* db_;
      name_t table_;
      std::vector<std::shared_ptr<ptree_t>> nodes_;
      table_t result_;
      stack_t stack_;
      count_t rows_affected_;

   public:
      ~parser_t() = default;
      parser_t(const parser_t&) = default;
      parser_t(parser_t&&) = default;
      parser_t& operator=(const parser_t&) = default;
      parser_t& operator=(parser_t&&) = default;

      parser_t() noexcept
         : stmt_()
         , error_(status::ok)
         , errmsg_()
         , ptree_(nullptr)
         , scan_()
         , db_(nullptr)
         , table_()
         , nodes_()
         , result_()
         , stack_()
         , rows_affected_(0)
      {}

      bool run(database_t* db, const text_t& stmt) noexcept
      {
         db_ = db;
         stmt_ = stmt;
         errmsg_ = "No errors detected";
         ptree_ = nullptr;
         table_ = "";
         nodes_.clear();
         result_.clear();
         stack_.clear();
         rows_affected_ = 0;
         scan_.run(stmt_);
         int error_ = 0;
         if (!sql_parser((void*)this))
         {
            return context_check();
         }
         return false;
      }

      void set_error(status_t err, const char* msg, const token_t& token) noexcept
      {
         if (error_ == 0)
         {
            error_ = err;
            errmsg_ = "Error " + std::to_string(err) +
               " (" + std::to_string(scan_.current().line()) + ":" + std::to_string(scan_.current().column()) + ") " +
               msg;
         }
      }
      void set_error(status_t err, const char* msg) noexcept
      {
         set_error(err, msg, scan_.current());
      }

      scanner_t& scanner() noexcept
      {
         return scan_;
      }

      void set_tree(ptree_t* tree) noexcept
      {
         ptree_ = tree;
      }

      ptree_t* get_tree() noexcept
      {
         return ptree_;
      }

      database_t& database() noexcept
      {
         return *db_;
      }

      name_t table() const noexcept
      {
         return table_;
      }

      void table(const name_t& tb) noexcept
      {
         table_ = tb;
      }

      stack_t& stack() noexcept
      {
         return stack_;
      }

      status_t get_error_code() const noexcept
      {
         return error_;
      }

      text_t get_error_message() const noexcept
      {
         return errmsg_;
      }

      void clear_execution() noexcept
      {
         error_ = status::ok;
         errmsg_ = "";
         result_.clear();
         stack_.clear();
         rows_affected_ = 0;
      }

      ptree_t* make(parser_t* parser, ptree::opcode_t opcode, const token_t& token, const value_t& value, ptree_t* left, ptree_t* right) noexcept
      {
         auto tree = std::shared_ptr<ptree_t>(new ptree_t(parser, opcode, token, value, left, right));
         nodes_.push_back(tree);
         return tree.get();
      }

      bool context_check() noexcept;
   };

   // alwyas use make_ptree to create ptree_t objects. 
   inline ptree_t* make_ptree(parser_t* parser, ptree::opcode_t opcode, const token_t& token, const value_t& value, ptree_t* left = nullptr, ptree_t* right = nullptr) noexcept
   {
      if (parser)
      {
         return parser->make(parser, opcode, token, value, left, right);
      }
      return nullptr;
   }

   inline ptree_t* make_ptree(parser_t* parser, ptree::opcode_t opcode, const token_t* token, const value_t& value, ptree_t* left = nullptr, ptree_t* right = nullptr) noexcept
   {
      if (!parser) return nullptr;
      token_t tok = token != nullptr ? *token : token_t();
      return parser->make(parser, opcode, tok, value, left, right);
   }

   inline parser_t* tree_parser(ptree_t* tree) noexcept
   {
      return tree->parser();
   }

   inline stack_t& tree_stack(ptree_t* tree) noexcept
   {
      return tree->parser()->stack();
   }

   namespace context {

      inline bool check_field_def(ptree_t* tree) noexcept 
      { 
         // push field type then push field name
         tree_stack(tree).push(tree->value());
         tree_stack(tree).push(value_t(tree->token().text()));
         return true; 
      }

      inline bool check_field_def_list(ptree_t* tree) noexcept 
      { 
         return true; 
      }
      
      inline bool check_create_table_field_duplicated(ptree_t* tree) noexcept
      {
         using pair_t = std::pair<value_t, value_t>;
         std::vector<pair_t> names;
         while (!tree_stack(tree).empty())
         {
            value_t fname = tree_stack(tree).pop();
            value_t ftype = tree_stack(tree).pop();
            for (auto& item : names)
            {
               if (compare(get_value<text_t>(fname), get_value<text_t>(item.first)))
               {
                  tree_parser(tree)->set_error(status::duplicate, text_t("duplicate field " + get_value<text_t>(fname)).c_str());
                  return false;
               }
            }
            names.push_back(pair_t(fname, ftype));
         }
         return true;
      }

      inline bool check_create_table(ptree_t* tree) noexcept 
      { 
         database_t& db(tree->parser()->database());
         if (db.table_exists(tree->token().text()) == status_t::ok)
         {
            tree->parser()->set_error(status::duplicate, text_t("table exists " + tree->token().text()).c_str());
            return false;
         }
         return check_create_table_field_duplicated(tree);
      }

      inline static std::array<std::function<bool(ptree_t*)>, 40> context_dispatch_table =
      {
         /* noop 				*/   [](ptree_t* tree) -> bool { return true; }
         /* push_field 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* push_table 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* push_literal 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* minus 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* plus 				*/ , [](ptree_t* tree) -> bool { return true; }
         /* negate 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* multiply 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* divide 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* add 				*/ , [](ptree_t* tree) -> bool { return true; }
         /* subtract 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* equal 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* not_equal 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* less 				*/ , [](ptree_t* tree) -> bool { return true; }
         /* less_equal 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* greater 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* greater_equal 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* is_null 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* is_not_null 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* logical_or 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* logical_and 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* expr 				*/ , [](ptree_t* tree) -> bool { return true; }
         /* where 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* where_true 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* assign_list 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* assign 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* field_def 		*/ , [](ptree_t* tree) -> bool { return check_field_def(tree); }
         /* field_def_list */ , [](ptree_t* tree) -> bool { return check_field_def_list(tree); }
         /* field_name 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* create_table 	*/ , [](ptree_t* tree) -> bool { return check_create_table(tree); }
         /* insert 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* insert_values 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* update 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* update_set 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* drop_table 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* delete_row 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* select 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* select_where 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* select_from 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* field_all 		*/ , [](ptree_t* tree) -> bool { return true; } 
      };
   } // namespace context

   inline bool check_context(ptree_t* tree) noexcept
   {
      if (!tree) return true;
      if (check_context(tree->left()) && check_context(tree->right()))
      {
         return context::context_dispatch_table[tree->opcode()](tree);
      }
      return false;
   }

   inline bool parser_t::context_check() noexcept
   {
      return check_context(ptree_);
   }

} // namespace tucan