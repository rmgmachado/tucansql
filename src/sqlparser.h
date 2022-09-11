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

#include <memory>
#include <functional>
#include <stack>
#include <map>

#include "value.h"
#include "scanner.h"
#include "ptree.h"
#include "memdb.h"

int sql_parser(void* pt);

namespace tucan {


   namespace parser {

      enum status_t : int 
      {  
           ok = 0
         , syntax_error
         , duplicate
         , invalid_name
         , table_create_error
         , invalid_handle
      };
   }

   class stack_t
   {
      std::stack<value_t> stack_;

   public:
      stack_t() = default;
      ~stack_t() = default;
      stack_t(const stack_t&) = default;
      stack_t(stack_t&&) = default;
      stack_t& operator=(const stack_t&) = default;
      stack_t& operator=(stack_t&&) = default;

      void push(const value_t& value) noexcept
      {
         stack_.push(value);
      }

      value_t top() const noexcept
      {
         if (!stack_.empty())
         {
            return stack_.top();
         }
         return value_t();
      }

      value_t pop() noexcept
      {
         if (!stack_.empty())
         {
            value_t value = stack_.top();
            stack_.pop();
            return value;
         }
         return value_t();
      }

      bool empty() const noexcept
      {
         return stack_.empty();
      }

      size_t size() const noexcept
      {
         return stack_.size();
      }

      void clear() noexcept
      {
         while (!stack_.empty())
         {
            stack_.pop();
         }
      }
   };

   class parser_t
   {
      std::string stmt_;
      int error_;
      std::string errmsg_;
      ptree_t* ptree_;
      scanner_t scan_;
      database_t& db_;
      name_t table_;
      std::vector<std::shared_ptr<ptree_t>> nodes_;
      table_t result_;
      stack_t stack_;
      count_t rows_affected_;

   public:
      parser_t() = default;
      ~parser_t() = default;
      parser_t(const parser_t&) = default;
      parser_t(parser_t&&) = default;
      parser_t& operator=(const parser_t&) = default;
      parser_t& operator=(parser_t&&) = default;

      parser_t(database_t& db) noexcept
         : stmt_()
         , error_(0)
         , errmsg_()
         , ptree_(nullptr)
         , scan_()
         , db_(db)
         , table_()
         , nodes_()
         , result_()
         , stack_()
         , rows_affected_(0)
      {}

      bool run(const text_t& stmt) noexcept
      {
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

      void set_error(int err, const char* msg, const token_t& token) noexcept
      {
         if (error_ == 0)
         {
            error_ = err;
            errmsg_ = "Error " + std::to_string(err) +
               " (" + std::to_string(scan_.current().line()) + ":" + std::to_string(scan_.current().column()) + ") " +
               msg;
         }
      }
      void set_error(int err, const char* msg) noexcept
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
         return db_;
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

      int get_error_code() const noexcept
      {
         return error_;
      }

      text_t get_error_message() const noexcept
      {
         return errmsg_;
      }

      void clear_execution() noexcept
      {
         error_ = 0;
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
                  tree_parser(tree)->set_error(parser::duplicate, text_t("duplicate field " + get_value<text_t>(fname)).c_str());
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
            tree->parser()->set_error(parser::duplicate, text_t("table exists " + tree->token().text()).c_str());
            return false;
         }
         return check_create_table_field_duplicated(tree);
      }

      inline static std::map<ptree::opcode_t, std::function<bool(ptree_t*)>> context_dispatch_table =
      {
           { ptree::noop,             [](ptree_t* tree) -> bool { return true; } }
         , { ptree::push_field,       [](ptree_t* tree) -> bool { return true; } }
         , { ptree::push_table,       [](ptree_t* tree) -> bool { return true; } }
         , { ptree::push_literal,     [](ptree_t* tree) -> bool { return true; } }
         , { ptree::minus,            [](ptree_t* tree) -> bool { return true; } }
         , { ptree::plus,             [](ptree_t* tree) -> bool { return true; } }
         , { ptree::negate,           [](ptree_t* tree) -> bool { return true; } }
         , { ptree::multiply,         [](ptree_t* tree) -> bool { return true; } }
         , { ptree::divide,           [](ptree_t* tree) -> bool { return true; } }
         , { ptree::add,              [](ptree_t* tree) -> bool { return true; } }
         , { ptree::subtract,         [](ptree_t* tree) -> bool { return true; } }
         , { ptree::equal,            [](ptree_t* tree) -> bool { return true; } }
         , { ptree::not_equal,        [](ptree_t* tree) -> bool { return true; } }
         , { ptree::less,             [](ptree_t* tree) -> bool { return true; } }
         , { ptree::less_equal,       [](ptree_t* tree) -> bool { return true; } }
         , { ptree::greater,          [](ptree_t* tree) -> bool { return true; } }
         , { ptree::greater_equal,    [](ptree_t* tree) -> bool { return true; } }
         , { ptree::is_null,          [](ptree_t* tree) -> bool { return true; } }
         , { ptree::is_not_null,      [](ptree_t* tree) -> bool { return true; } }
         , { ptree::logical_or,       [](ptree_t* tree) -> bool { return true; } }
         , { ptree::logical_and,      [](ptree_t* tree) -> bool { return true; } }
         , { ptree::expr,             [](ptree_t* tree) -> bool { return true; } }
         , { ptree::where,            [](ptree_t* tree) -> bool { return true; } }
         , { ptree::where_true,       [](ptree_t* tree) -> bool { return true; } }
         , { ptree::assign_list,      [](ptree_t* tree) -> bool { return true; } }
         , { ptree::assign,           [](ptree_t* tree) -> bool { return true; } }
         , { ptree::field_def,        [](ptree_t* tree) -> bool { return check_field_def(tree); } }
         , { ptree::field_def_list,   [](ptree_t* tree) -> bool { return check_field_def_list(tree); }}
         , { ptree::field_name,       [](ptree_t* tree) -> bool { return true; } }
         , { ptree::create_table,     [](ptree_t* tree) -> bool { return check_create_table(tree); } }
         , { ptree::insert,           [](ptree_t* tree) -> bool { return true; } }
         , { ptree::insert_values,    [](ptree_t* tree) -> bool { return true; } }
         , { ptree::update,           [](ptree_t* tree) -> bool { return true; } }
         , { ptree::update_set,       [](ptree_t* tree) -> bool { return true; } }
         , { ptree::drop_table,       [](ptree_t* tree) -> bool { return true; } }
         , { ptree::delete_row,       [](ptree_t* tree) -> bool { return true; } }
         , { ptree::select,           [](ptree_t* tree) -> bool { return true; } }
         , { ptree::select_where,     [](ptree_t* tree) -> bool { return true; } }
         , { ptree::select_from,      [](ptree_t* tree) -> bool { return true; } }
         , { ptree::field_all,        [](ptree_t* tree) -> bool { return true; } }
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