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
#include "sqlparser.h"

using namespace tucan;

TEST_CASE("sqlparser_t tests", "[sqlparser]")
{
   SECTION("Test successful parsing of CREATE TABLE")
   {
      std::string stmt = "CREATE TABLE table1 (field1 boolean)";
      database_t db;
      parser_t parser;

      REQUIRE(parser.run(&db, stmt));
   }
   SECTION("Test parsing of CREATE TABLE with syntax error")
   {
      std::string stmt = "CREATE TABLE table1 (field1 boolean, field2)";
      database_t db;
      parser_t parser;

      REQUIRE(parser.run(&db, stmt) == false);
      REQUIRE(parser.get_error_code() == status::syntax_error);
      REQUIRE(parser.get_error_message().length() > 0);
   }
   SECTION("Test parsing of CREATE TABLE with duplicate field error")
   {
      std::string stmt = "CREATE TABLE table1 (field1 boolean, field2 decimal, field1 integer)";
      database_t db;
      parser_t parser;

      REQUIRE(parser.run(&db, stmt) == false);
      REQUIRE(parser.get_error_code() == status::duplicate);
      REQUIRE(parser.get_error_message().length() > 0);
   }
}
