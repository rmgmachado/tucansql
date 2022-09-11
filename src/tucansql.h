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

#include "memdb.h"
#include "sqlparser.h"

namespace tucan {

   namespace sql {
      using status_t = int;
      size_t npos = -1;
   }

   using sqlid_t = size_t;


   inline bool execute_tree(ptree_t* tree) noexcept;

   class sql_t
   {
      database_t db_;
      std::vector<parser_t> parsers_;
      int error_;
      text_t errmsg_;

   public:
      sql_t() = default;
      ~sql_t() = default;
      sql_t(const sql_t&) = delete;
      sql_t(sql_t&&) = default;
      sql_t& operator=(const sql_t&) = delete;
      sql_t& operator=(sql_t&&) = default;

      void set_error(int errcode, const text_t& errmsg) noexcept
      {
         error_ = errcode;
         errmsg_ = errmsg;
      }

      int get_error() const noexcept
      {
         return error_;
      }

      text_t get_error_message() const noexcept
      {
         return errmsg_;
      }

      database_t& database() noexcept
      {
         return db_;
      }

      sqlid_t prepare(const std::string& stmt) noexcept
      {
         error_ = 0;
         errmsg_ = "No errors detected";
         parsers_.push_back(parser_t(db_));
         sqlid_t id = int(std::distance(parsers_.begin(), parsers_.end())) - 1;
         if (parsers_[id].run(stmt)) return id;
         set_error(parsers_[id].get_error_code(), parsers_[id].get_error_message());
         return sql::npos;
      }

      sql::status_t execute(const sqlid_t& id) noexcept
      {
         if (id != sql::npos)
         {
            if (execute_tree(parsers_[id].get_tree())) return parser::ok;
            return parsers_[id].get_error_code();
         }
         return parser::invalid_handle;
      }

      sql::status_t next(const sqlid_t& id) noexcept
      {
         return parser::ok;
      }

      sql::status_t reset(const sqlid_t& id) noexcept
      {
         return parser::ok;
      }

      sql::status_t finalize(const sqlid_t& id) noexcept
      {
         return parser::ok;
      }

      count_t rows_afftected() const noexcept
      {
         return 0;
      }

      count_t column_count() const noexcept
      {
         return 0;
      }

      colid_t column_index(const name_t& column_name) const noexcept
      {
         return memdb::npos;
      }

      name_t column_name(colid_t id) const noexcept
      {
         return "";
      }

      type_t column_type(colid_t id) const noexcept
      {
         return type_t::null;
      }

      bool is_column_null(colid_t id) const noexcept
      {
         return true;
      }

      value_t& column_value(colid_t) const noexcept
      {
         static value_t val;
         return val;
      }

      std::string column_value_as_string(colid_t id) const noexcept
      {
         return "";
      }

      count_t column_width(colid_t id) const noexcept
      {
         return 0;
      }
   };

   namespace runtime
   {
      parser_t& parser(ptree_t* tree) noexcept
      {
         return *tree->parser();
      }

      stack_t& stack(ptree_t* tree) noexcept
      {
         return parser(tree).stack();
      }

      database_t& database(ptree_t* tree) noexcept
      {
         return parser(tree).database();
      }

      value_t top(ptree_t* tree) noexcept
      {
         return stack(tree).top();
      }

      value_t pop(ptree_t* tree) noexcept
      {
         return stack(tree).pop();
      }

      void push(ptree_t* tree, const value_t& value) noexcept
      {
         stack(tree).push(value);
      }

      size_t size(ptree_t* tree) noexcept
      {
         return stack(tree).size();
      }

      bool empty(ptree_t* tree) noexcept
      {
         return stack(tree).empty();
      }

      inline bool execute_noop(ptree_t* tree) noexcept { return true; }
      inline bool execute_push_field(ptree_t* tree) noexcept { return true; }
      inline bool execute_push_table(ptree_t* tree) noexcept { return true; }
      inline bool execute_push_literal(ptree_t* tree) noexcept { return true; }
      inline bool execute_minus(ptree_t* tree) noexcept { return true; }
      inline bool execute_plus(ptree_t* tree) noexcept { return true; }
      inline bool execute_negate(ptree_t* tree) noexcept { return true; }
      inline bool execute_multiply(ptree_t* tree) noexcept { return true; }
      inline bool execute_divide(ptree_t* tree) noexcept { return true; }
      inline bool execute_add(ptree_t* tree) noexcept { return true; }
      inline bool execute_subtract(ptree_t* tree) noexcept { return true; }
      inline bool execute_equal(ptree_t* tree) noexcept { return true; }
      inline bool execute_not_equal(ptree_t* tree) noexcept { return true; }
      inline bool execute_less(ptree_t* tree) noexcept { return true; }
      inline bool execute_less_equal(ptree_t* tree) noexcept { return true; }
      inline bool execute_greater(ptree_t* tree) noexcept { return true; }
      inline bool execute_greater_equal(ptree_t* tree) noexcept { return true; }
      inline bool execute_is_null(ptree_t* tree) noexcept { return true; }
      inline bool execute_is_not_null(ptree_t* tree) noexcept { return true; }
      inline bool execute_logical_or(ptree_t* tree) noexcept { return true; }
      inline bool execute_logical_and(ptree_t* tree) noexcept { return true; }
      inline bool execute_expr(ptree_t* tree) noexcept { return true; }
      inline bool execute_where(ptree_t* tree) noexcept { return true; }
      inline bool execute_where_true(ptree_t* tree) noexcept { return true; }
      inline bool execute_assign_list(ptree_t* tree) noexcept { return true; }
      inline bool execute_assign(ptree_t* tree) noexcept { return true; }

      inline bool execute_field_def(ptree_t* tree) noexcept
      {
         push(tree, tree->value());
         push(tree, value_t(tree->token().text()));
         return true;
      }

      inline bool execute_field_def_list(ptree_t* tree) noexcept
      {
         return true;
      }

      inline bool execute_field_name(ptree_t* tree) noexcept { return true; }


      inline bool execute_create_table(ptree_t* tree) noexcept
      {
         text_t tblname = tree->token().text();
         status_t status = database(tree).create_table(tblname);
         if (status == status_t::ok)
         {
            table_t& tbl = database(tree).get_table(tblname);
            while (!empty(tree))
            {
               text_t colname = get_value<text_t>(tree_stack(tree).pop());
               value_t coltype = tree_stack(tree).pop();

               status = tbl.add_column(colname, coltype.type());
               if (status != status_t::ok)
               {
                  parser(tree).set_error(parser::table_create_error, std::string("error adding field: " + colname).c_str());
                  return false;
               }
            }
         }
         if (status == status_t::invalid_name)
         {
            parser(tree).set_error(parser::table_create_error, std::string("invalid table name: " + tblname).c_str());
            return false;
         }
         if (status == status_t::duplicate)
         {
            parser(tree).set_error(parser::table_create_error, std::string("table already created: " + tblname).c_str());
            return false;
         }
         return true;
      }

      inline bool execute_insert(ptree_t* tree) noexcept { return true; }
      inline bool execute_insert_values(ptree_t* tree) noexcept { return true; }
      inline bool execute_update(ptree_t* tree) noexcept { return true; }
      inline bool execute_update_set(ptree_t* tree) noexcept { return true; }
      inline bool execute_drop_table(ptree_t* tree) noexcept { return true; }
      inline bool execute_delete_row(ptree_t* tree) noexcept { return true; }
      inline bool execute_select(ptree_t* tree) noexcept { return true; }
      inline bool execute_select_where(ptree_t* tree) noexcept { return true; }
      inline bool execute_select_from(ptree_t* tree) noexcept { return true; }
      inline bool execute_field_all(ptree_t* tree) noexcept { return true; }

      inline static std::vector<std::function<bool(ptree_t*)>> table
      {
           execute_noop
         , execute_push_field
         , execute_push_table
         , execute_push_literal
         , execute_minus
         , execute_plus
         , execute_negate
         , execute_multiply
         , execute_divide
         , execute_add
         , execute_subtract
         , execute_equal
         , execute_not_equal
         , execute_less
         , execute_less_equal
         , execute_greater
         , execute_greater_equal
         , execute_is_null
         , execute_is_not_null
         , execute_logical_or
         , execute_logical_and
         , execute_expr
         , execute_where
         , execute_where_true
         , execute_assign_list
         , execute_assign
         , execute_field_def
         , execute_field_def_list
         , execute_field_name
         , execute_create_table
         , execute_insert
         , execute_insert_values
         , execute_update
         , execute_update_set
         , execute_drop_table
         , execute_delete_row
         , execute_select
         , execute_select_where
         , execute_select_from
         , execute_field_all
      };

      inline bool execute(ptree_t* tree) noexcept
      {
         if (!tree) return true;
         if (execute(tree->left()) && execute(tree->right()))
         {
            return runtime::table[tree->opcode()](tree);
         }
         return false;
      }

   } // namespace runtime

   inline bool execute_tree(ptree_t* tree) noexcept
   {
      if (!tree) return false;
      if (!tree->parser()) return false;
      tree->parser()->clear_execution();
      return runtime::execute(tree);
   }



} // namespace tucan
