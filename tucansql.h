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

   namespace sql
   {
      enum status_t : int {ok, syntax_error};
   }

   using sqlid_t = size_t;

   inline bool execute(ptree_t* tree) noexcept;

   class sql_t
   {
      database_t db_;
      std::vector<parser_t> stmt_;


   public:
      sql_t() = default;
      ~sql_t() = default;
      sql_t(const sql_t&) = delete;
      sql_t(sql_t&&) = default;
      sql_t& operator=(const sql_t&) = delete;
      sql_t& operator=(sql_t&&) = default;

      sql::status_t prepare(sqlid_t& id, const std::string& stmt) noexcept
      {
         return sql::ok;
      }

      sql::status_t execute(const sqlid_t& id) noexcept
      {
         return sql::ok;
      }

      sql::status_t next(const sqlid_t& id) noexcept
      {
         return sql::ok;
      }

      sql::status_t reset(const sqlid_t& id) noexcept
      {
         return sql::ok;
      }

      sql::status_t finalize(const sqlid_t& id) noexcept
      {
         return sql::ok;
      }

      count_t row_count() const noexcept
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
      inline bool exec_push_table(ptree_t* tree) noexcept
      {
         return true;
      }

      inline bool exec_push_literal(ptree_t* tree) noexcept { return true; }
      inline bool exec_minus(ptree_t* tree) noexcept { return true; }
      inline bool exec_plus(ptree_t* tree) noexcept { return true; }
      inline bool exec_negate(ptree_t* tree) noexcept { return true; }
      inline bool exec_multiply(ptree_t* tree) noexcept { return true; }
      inline bool exec_divide(ptree_t* tree) noexcept { return true; }
      inline bool exec_add(ptree_t* tree) noexcept { return true; }
      inline bool exec_subtract(ptree_t* tree) noexcept { return true; }
      inline bool exec_equal(ptree_t* tree) noexcept { return true; }
      inline bool exec_not_equal(ptree_t* tree) noexcept { return true; }
      inline bool exec_less(ptree_t* tree) noexcept { return true; }
      inline bool exec_less_equal(ptree_t* tree) noexcept { return true; }
      inline bool exec_greater(ptree_t* tree) noexcept { return true; }
      inline bool exec_greater_equal(ptree_t* tree) noexcept { return true; }
      inline bool exec_is_null(ptree_t* tree) noexcept { return true; }
      inline bool exec_is_not_null(ptree_t* tree) noexcept { return true; }
      inline bool exec_logical_or(ptree_t* tree) noexcept { return true; }
      inline bool exec_logical_and(ptree_t* tree) noexcept { return true; }
      inline bool exec_expr(ptree_t* tree) noexcept { return true; }
      inline bool exec_where(ptree_t* tree) noexcept { return true; }
      inline bool exec_where_true(ptree_t* tree) noexcept { return true; }
      inline bool exec_assign_list(ptree_t* tree) noexcept { return true; }
      inline bool exec_assign(ptree_t* tree) noexcept { return true; }
      inline bool exec_field_def(ptree_t* tree) noexcept { return true; }
      inline bool exec_field_def_list(ptree_t* tree) noexcept { return true; }
      inline bool exec_field_name(ptree_t* tree) noexcept { return true; }
      inline bool exec_create_table(ptree_t* tree) noexcept { return true; }
      inline bool exec_insert(ptree_t* tree) noexcept { return true; }
      inline bool exec_insert_values(ptree_t* tree) noexcept { return true; }
      inline bool exec_update(ptree_t* tree) noexcept { return true; }
      inline bool exec_update_set(ptree_t* tree) noexcept { return true; }
      inline bool exec_drop_table(ptree_t* tree) noexcept { return true; }
      inline bool exec_delete_row(ptree_t* tree) noexcept { return true; }
      inline bool exec_select(ptree_t* tree) noexcept { return true; }
      inline bool exec_select_where(ptree_t* tree) noexcept { return true; }
      inline bool exec_select_from(ptree_t* tree) noexcept { return true; }
      inline bool exec_field_all(ptree_t* tree) noexcept { return true; }

      inline static std::vector<std::function<bool(ptree_t*)>> table
      {
           exec_noop
         , exec_push_field
         , exec_push_table
         , exec_push_literal
         , exec_minus
         , exec_plus
         , exec_negate
         , exec_multiply
         , exec_divide
         , exec_add
         , exec_subtract
         , exec_equal
         , exec_not_equal
         , exec_less
         , exec_less_equal
         , exec_greater
         , exec_greater_equal
         , exec_is_null
         , exec_is_not_null
         , exec_logical_or
         , exec_logical_and
         , exec_expr
         , exec_where
         , exec_where_true
         , exec_assign_list
         , exec_assign
         , exec_field_def
         , exec_field_name
         , exec_create_table
         , exec_insert
         , exec_insert_values
         , exec_update
         , exec_update_set
         , exec_drop_table
         , exec_delete_row
         , exec_select
         , exec_select_where
         , exec_select_from
         , exec_field_all
      };

      inline bool execute_ptree(ptree_t* tree) noexcept
      {
         if (!tree) return true;
         if (execute_ptree(tree->left()) && execute_ptree(tree->right()))
         {
            return runtime::table[tree->opcode()](tree);
         }
         return false;
      }

   } // namespace runtime

   inline bool execute(ptree_t* tree) noexcept
   {
      if (!tree) return false;
      return runtime::execute_ptree(tree);
   }



} // namespace tucan
