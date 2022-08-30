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

#include "value.h"
#include "scanner.h"
#include "ptree.h"
#include "memdb.h"

int sql_parser(void* pt);

namespace tucan {


   namespace parser {

      enum status_t : int { ok = 0, syntax_error, duplicate };
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

      parser_t(database_t& db, const std::string& stmt) noexcept
         : stmt_(stmt)
         , error_(0)
         , errmsg_()
         , ptree_(nullptr)
         , scan_(stmt)
         , db_(db)
         , table_()
         , nodes_()
         , result_()
         , stack_()
         , rows_affected_(0)
      {}

      bool run() noexcept
      {
         error_ = 0;
         errmsg_ = "No error detected";
         nodes_.clear();
         scan_.run(stmt_);
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

      inline scanner_t& scanner() noexcept
      {
         return scan_;
      }

      inline void set_tree(ptree_t* tree) noexcept
      {
         ptree_ = tree;
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

      ptree_t* make(parser_t* parser, int opcode, const token_t& token, const value_t& value, ptree_t* left, ptree_t* right) noexcept
      {
         auto tree = std::shared_ptr<ptree_t>(new ptree_t(parser, opcode, token, value, left, right));
         nodes_.push_back(tree);
         return tree.get();
      }

      bool context_check() noexcept;
   };

   // alwyas use make_ptree to create ptree_t objects. 
   inline ptree_t* make_ptree(parser_t* parser, int opcode, const token_t& token, const value_t& value, ptree_t* left = nullptr, ptree_t* right = nullptr) noexcept
   {
      if (parser)
      {
         return parser->make(parser, opcode, token, value, left, right);
      }
      return nullptr;
   }

   inline ptree_t* make_ptree(parser_t* parser, int opcode, const token_t* token, const value_t& value, ptree_t* left = nullptr, ptree_t* right = nullptr) noexcept
   {
      if (!parser) return nullptr;
      token_t tok = token != nullptr ? *token : token_t();
      return parser->make(parser, opcode, tok, value, left, right);
   }

   namespace context {

      inline bool check_noop(ptree_t* tree) noexcept 
      { 
         return true; 
      }

      inline bool check_push_field(ptree_t* tree) noexcept 
      { 
         return true; 
      }

      inline bool check_push_table(ptree_t* tree) noexcept { return true; }
      inline bool check_push_literal(ptree_t* tree) noexcept { return true; }
      inline bool check_minus(ptree_t* tree) noexcept { return true; }
      inline bool check_plus(ptree_t* tree) noexcept { return true; }
      inline bool check_negate(ptree_t* tree) noexcept { return true; }
      inline bool check_multiply(ptree_t* tree) noexcept { return true; }
      inline bool check_divide(ptree_t* tree) noexcept { return true; }
      inline bool check_add(ptree_t* tree) noexcept { return true; }
      inline bool check_subtract(ptree_t* tree) noexcept { return true; }
      inline bool check_equal(ptree_t* tree) noexcept { return true; }
      inline bool check_not_equal(ptree_t* tree) noexcept { return true; }
      inline bool check_less(ptree_t* tree) noexcept { return true; }
      inline bool check_less_equal(ptree_t* tree) noexcept { return true; }
      inline bool check_greater(ptree_t* tree) noexcept { return true; }
      inline bool check_greater_equal(ptree_t* tree) noexcept { return true; }
      inline bool check_is_null(ptree_t* tree) noexcept { return true; }
      inline bool check_is_not_null(ptree_t* tree) noexcept { return true; }
      inline bool check_logical_or(ptree_t* tree) noexcept { return true; }
      inline bool check_logical_and(ptree_t* tree) noexcept { return true; }
      inline bool check_expr(ptree_t* tree) noexcept { return true; }
      inline bool check_where(ptree_t* tree) noexcept { return true; }
      inline bool check_where_true(ptree_t* tree) noexcept { return true; }
      inline bool check_assign_list(ptree_t* tree) noexcept { return true; }
      inline bool check_assign(ptree_t* tree) noexcept { return true; }
      
      inline bool check_field_def(ptree_t* tree) noexcept 
      { 
         // push field type then push field name
         tree->parser()->stack().push(tree->value());
         tree->parser()->stack().push(value_t(tree->token().text()));
         return true; 
      }

      inline bool check_field_def_list(ptree_t* tree) noexcept 
      { 
         return true; 
      }
      
      inline bool check_field_name(ptree_t* tree) noexcept { return true; }

      inline bool check_create_table_field_duplicated(ptree_t* tree) noexcept
      {
         using pair_t = std::pair<value_t, value_t>;
         std::vector<pair_t> names;
         while (!tree->parser()->stack().empty())
         {
            value_t fname = tree->parser()->stack().pop();
            value_t ftype = tree->parser()->stack().pop();
            for (auto& item : names)
            {
               if (compare(get_value<text_t>(fname), get_value<text_t>(item.first)))
               {
                  tree->parser()->set_error(parser::duplicate, text_t("duplicate field " + get_value<text_t>(fname)).c_str());
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

      inline bool check_insert(ptree_t* tree) noexcept { return true; }
      inline bool check_insert_values(ptree_t* tree) noexcept { return true; }
      inline bool check_update(ptree_t* tree) noexcept { return true; }
      inline bool check_update_set(ptree_t* tree) noexcept { return true; }
      inline bool check_drop_table(ptree_t* tree) noexcept { return true; }
      inline bool check_delete_row(ptree_t* tree) noexcept { return true; }
      inline bool check_select(ptree_t* tree) noexcept { return true; }
      inline bool check_select_where(ptree_t* tree) noexcept { return true; }
      inline bool check_select_from(ptree_t* tree) noexcept { return true; }
      inline bool check_field_all(ptree_t* tree) noexcept { return true; }

      inline static std::vector<std::function<bool(ptree_t*)>> table
      {
           check_noop
         , check_push_field
         , check_push_table
         , check_push_literal
         , check_minus
         , check_plus
         , check_negate
         , check_multiply
         , check_divide
         , check_add
         , check_subtract
         , check_equal
         , check_not_equal
         , check_less
         , check_less_equal
         , check_greater
         , check_greater_equal
         , check_is_null
         , check_is_not_null
         , check_logical_or
         , check_logical_and
         , check_expr
         , check_where
         , check_where_true
         , check_assign_list
         , check_assign
         , check_field_def
         , check_field_def_list
         , check_field_name
         , check_create_table
         , check_insert
         , check_insert_values
         , check_update
         , check_update_set
         , check_drop_table
         , check_delete_row
         , check_select
         , check_select_where
         , check_select_from
         , check_field_all
      };
   } // namespace context

   inline bool check_context(ptree_t* tree) noexcept
   {
      if (!tree) return true;
      if (check_context(tree->left()) && check_context(tree->right()))
      {
         return context::table[tree->opcode()](tree);
      }
      return false;
   }

   inline bool parser_t::context_check() noexcept
   {
      return check_context(ptree_);
   }

} // namespace tucan