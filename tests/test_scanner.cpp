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
#include "scanner.h"

using namespace tucan;

TEST_CASE("scanner_t tests", "[scanner]")
{
   // if you change the text, you need to fix the line and cols of tests
   std::string stmt = "SELECT *, (field1 + field2) AS \"field1 + field2\" FROM table \nWHERE name <> 'Reg''lar''ization' or field1 = 123.0 and (field2 <= 2022-08-26T16:56 or field2 >=2022-08-26T16:56:33)";
   scanner_t sc(stmt);
   token_t tok;
   int id;

   // select
   id = sc.next(tok);
   REQUIRE(id == token::identifier);
   REQUIRE(tok.id() == token::identifier);
   REQUIRE(tok.token() == "SELECT");
   REQUIRE(tok.line() == 1);
   REQUIRE(tok.column() == 1);
   
   // *
   id = sc.next(tok);
   REQUIRE(id == '*');
   REQUIRE(tok.id() == '*');
   REQUIRE(tok.token() == "*");
   REQUIRE(tok.line() == 1);
   REQUIRE(tok.column() == 8);

   // ,
   id = sc.next(tok);
   REQUIRE(id == ',');
   REQUIRE(tok.id() == ',');
   REQUIRE(tok.token() == ",");
   REQUIRE(tok.line() == 1);
   REQUIRE(tok.column() == 9);

   // (
   id = sc.next(tok);
   REQUIRE(id == '(');
   REQUIRE(tok.id() == '(');
   REQUIRE(tok.token() == "(");
   REQUIRE(tok.line() == 1);
   REQUIRE(tok.column() == 11);

   // field1
   id = sc.next(tok);
   REQUIRE(id == token::identifier);
   REQUIRE(tok.id() == token::identifier);
   REQUIRE(tok.token() == "field1");
   REQUIRE(tok.line() == 1);
   REQUIRE(tok.column() == 12);

   // +
   id = sc.next(tok);
   REQUIRE(id == '+');
   REQUIRE(tok.id() == '+');
   REQUIRE(tok.token() == "+");
   REQUIRE(tok.line() == 1);
   REQUIRE(tok.column() == 19);

   // field2
   id = sc.next(tok);
   REQUIRE(id == token::identifier);
   REQUIRE(tok.id() == token::identifier);
   REQUIRE(tok.token() == "field2");
   REQUIRE(tok.line() == 1);
   REQUIRE(tok.column() == 21);

   // )
   id = sc.next(tok);
   REQUIRE(id == ')');
   REQUIRE(tok.id() == ')');
   REQUIRE(tok.token() == ")");
   REQUIRE(tok.line() == 1);
   REQUIRE(tok.column() == 27);

   // AS
   id = sc.next(tok);
   REQUIRE(id == token::identifier);
   REQUIRE(tok.id() == token::identifier);
   REQUIRE(tok.token() == "AS");
   REQUIRE(tok.line() == 1);
   REQUIRE(tok.column() == 29);

   // "field1 + field2"
   id = sc.next(tok);
   REQUIRE(id == token::name);
   REQUIRE(tok.id() == token::name);
   REQUIRE(tok.token() == "field1 + field2");
   REQUIRE(tok.line() == 1);
   REQUIRE(tok.column() == 32);

   // FROM
   id = sc.next(tok);
   REQUIRE(id == token::identifier);
   REQUIRE(tok.id() == token::identifier);
   REQUIRE(tok.token() == "FROM");
   REQUIRE(tok.line() == 1);
   REQUIRE(tok.column() == 50);

   // table
   id = sc.next(tok);
   REQUIRE(id == token::identifier);
   REQUIRE(tok.id() == token::identifier);
   REQUIRE(tok.token() == "table");
   REQUIRE(tok.line() == 1);
   REQUIRE(tok.column() == 55);

   // WHERE
   id = sc.next(tok);
   REQUIRE(id == token::identifier);
   REQUIRE(tok.id() == token::identifier);
   REQUIRE(tok.token() == "WHERE");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 1);

   // name
   id = sc.next(tok);
   REQUIRE(id == token::identifier);
   REQUIRE(tok.id() == token::identifier);
   REQUIRE(tok.token() == "name");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 7);

   // <>
   id = sc.next(tok);
   REQUIRE(id == token::ne);
   REQUIRE(tok.id() == token::ne);
   REQUIRE(tok.token() == "<>");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 12);

   // 'Reg''lar''ization'
   id = sc.next(tok);
   REQUIRE(id == token::text);
   REQUIRE(tok.id() == token::text);
   REQUIRE(tok.token() == "Reg'lar'ization");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 15);

   // or
   id = sc.next(tok);
   REQUIRE(id == token::identifier);
   REQUIRE(tok.id() == token::identifier);
   REQUIRE(tok.token() == "or");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 35);

   // field1
   id = sc.next(tok);
   REQUIRE(id == token::identifier);
   REQUIRE(tok.id() == token::identifier);
   REQUIRE(tok.token() == "field1");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 38);

   // =
   id = sc.next(tok);
   REQUIRE(id == '=');
   REQUIRE(tok.id() == '=');
   REQUIRE(tok.token() == "=");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 45);

   // 123.0
   id = sc.next(tok);
   REQUIRE(id == token::decimal);
   REQUIRE(tok.id() == token::decimal);
   REQUIRE(tok.token() == "123.0");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 47);

   // and
   id = sc.next(tok);
   REQUIRE(id == token::identifier);
   REQUIRE(tok.id() == token::identifier);
   REQUIRE(tok.token() == "and");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 53);

   // (
   id = sc.next(tok);
   REQUIRE(id == '(');
   REQUIRE(tok.id() == '(');
   REQUIRE(tok.token() == "(");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 57);

   // field2
   id = sc.next(tok);
   REQUIRE(id == token::identifier);
   REQUIRE(tok.id() == token::identifier);
   REQUIRE(tok.token() == "field2");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 58);

   // <=
   id = sc.next(tok);
   REQUIRE(id == token::le);
   REQUIRE(tok.id() == token::le);
   REQUIRE(tok.token() == "<=");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 65);

   // 2022-08-26T16:56
   id = sc.next(tok);
   REQUIRE(id == token::datetime);
   REQUIRE(tok.id() == token::datetime);
   REQUIRE(tok.token() == "2022-08-26T16:56");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 68);

   // or
   id = sc.next(tok);
   REQUIRE(id == token::identifier);
   REQUIRE(tok.id() == token::identifier);
   REQUIRE(tok.token() == "or");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 85);

   // field2
   id = sc.next(tok);
   REQUIRE(id == token::identifier);
   REQUIRE(tok.id() == token::identifier);
   REQUIRE(tok.token() == "field2");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 88);

   // >=
   id = sc.next(tok);
   REQUIRE(id == token::ge);
   REQUIRE(tok.id() == token::ge);
   REQUIRE(tok.token() == ">=");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 95);

   // 2022-08-26T16:56:33
   id = sc.next(tok);
   REQUIRE(id == token::datetime);
   REQUIRE(tok.id() == token::datetime);
   REQUIRE(tok.token() == "2022-08-26T16:56:33");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 97);

   // )
   id = sc.next(tok);
   REQUIRE(id == ')');
   REQUIRE(tok.id() == ')');
   REQUIRE(tok.token() == ")");
   REQUIRE(tok.line() == 2);
   REQUIRE(tok.column() == 116);

   // eof
   id = sc.next(tok);
   REQUIRE(id == token::eof);
}
