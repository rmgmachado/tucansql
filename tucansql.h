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

namespace tucan {

   namespace sql
   {
      enum status_t : int {ok};
   }

   using sqlid_t = size_t;

   class sql_t
   {
      std::vector<int> stmt_;

   public:
      sql_t() = default;
      ~sql_t() = default;
      sql_t(const sql_t&) = default;
      sql_t(sql_t&&) = default;
      sql_t& operator=(const sql_t&) = default;
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


} // namespace tucan
