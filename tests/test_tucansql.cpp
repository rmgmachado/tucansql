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
#include "xpunit.h"
#include "tucansql.h"

using namespace tucan;

TEST_CASE("sqlparser_t tests", "[sqlparser]")
{
   SECTION("Test successful prepare and executyion of CREATE TABLE")
   {
      sql_t sql;
      sqlid_t handle;

      REQUIRE((handle = sql.prepare("CREATE TABLE person (name text, age integer)")) == parser::ok);
      if (handle != sql::npos)
      {
         REQUIRE(sql.execute(handle) == parser::ok);
         REQUIRE(sql.database().table_exists("person") == status_t::ok);

         cursor_t cursor = sql.database().get_table("person").get_cursor();
         REQUIRE(cursor.column_count() == 2);
         REQUIRE(cursor.get_column_name(0) == "name");
         REQUIRE(cursor.get_column_type(0) == type_t::text);
         REQUIRE(cursor.get_column_name(1) == "age");
         REQUIRE(cursor.get_column_type(1) == type_t::integer);
      }
   }
}
