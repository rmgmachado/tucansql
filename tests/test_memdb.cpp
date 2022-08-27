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
#include "memdb.h"

using namespace tucan;

TEST_CASE("database_t tests", "[memdb]")
{
   SECTION("database_t constructor tests")
   {
      database_t db;
      REQUIRE(db.table_count() == 0);
   }
   SECTION("database_t operations")
   {
      database_t db;
      REQUIRE(db.create_table("table1") == status_t::ok);
      REQUIRE(db.table_count() == 1);
      REQUIRE(db.create_table("table2") == status_t::ok);
      REQUIRE(db.table_count() == 2);
      REQUIRE(db.create_table("table3") == status_t::ok);
      REQUIRE(db.table_count() == 3);
      REQUIRE(db.create_table("table1") == status_t::duplicate);
      REQUIRE(db.table_count() == 3);

      REQUIRE(db.table_exists("table1") == status_t::ok);
      REQUIRE(db.table_exists("table2") == status_t::ok);
      REQUIRE(db.table_exists("TabLe2") == status_t::ok);
      REQUIRE(db.table_exists("table3") == status_t::ok);
      REQUIRE(db.table_exists("table4") == status_t::not_found);

      REQUIRE(db.get_table("table1").name() == "table1");
      REQUIRE(db.get_table("table1").name() == "table1");
      REQUIRE(db.get_table("table2").name() == "table2");
      REQUIRE(db.get_table("table3").name() == "table3");
      REQUIRE(db.get_table("table4").name() == "");

      REQUIRE(db.drop_table("table2") == status_t::ok);
      REQUIRE(db.table_count() == 2);
      REQUIRE(db.get_table("table1").name() == "table1");
      REQUIRE(db.get_table("table2").name() == "");
      REQUIRE(db.get_table("table3").name() == "table3");

   }
}

TEST_CASE("table_t tests", "[memdb]")
{
   table_t tb;

   REQUIRE(tb.column_count() == 0);
   REQUIRE(tb.row_count() == 0);
   REQUIRE(tb.name() == "");
   tb.name("table1");
   REQUIRE(tb.name() == "table1");
   REQUIRE(tb.add_column("name", opcode_t::text) == status_t::ok);
   REQUIRE(tb.add_column("age", opcode_t::decimal) == status_t::ok);
   REQUIRE(tb.column_count() == 2);
   REQUIRE(tb.row_count() == 0);
   REQUIRE(tb.add_column("1ad", opcode_t::decimal) == status_t::invalid_name);
   REQUIRE(tb.add_column("name", opcode_t::datetime) == status_t::duplicate);

   column_t& col = tb.get_cursor().get_column("name");
   REQUIRE(col.name == "name");
   REQUIRE(col.type == opcode_t::text);
   col = tb.get_cursor().get_column("age");
   REQUIRE(col.name == "age");
   REQUIRE(col.type == opcode_t::decimal);
   col = tb.get_cursor().get_column("1a");
   REQUIRE(col.name == "");
   REQUIRE(col.type == opcode_t::boolean);
}

TEST_CASE("cursor_t tests", "[memdb]")
{
   table_t tb;

   REQUIRE(tb.get_cursor().rowid() == 0);
   REQUIRE(tb.get_cursor().column_count() == 0);
   REQUIRE(tb.get_cursor().row_count() == 0);

   REQUIRE(tb.get_cursor().add_column("Name", opcode_t::text) == status_t::ok);
   REQUIRE(tb.get_cursor().add_column("Age", opcode_t::decimal) == status_t::ok);
   REQUIRE(tb.get_cursor().add_column("Male", opcode_t::boolean) == status_t::ok);
   REQUIRE(tb.get_cursor().add_column("Code", opcode_t::binary) == status_t::ok);
   REQUIRE(tb.get_cursor().column_count() == 4);
   REQUIRE(tb.get_cursor().row_count() == 0);

   cursor_t cursor = tb.get_cursor();
   REQUIRE(cursor.first_row() == status_t::not_found);
   REQUIRE(cursor.last_row() == status_t::not_found);
   REQUIRE(cursor.next_row() == status_t::not_found);
   REQUIRE(cursor.prior_row() == status_t::not_found);
   REQUIRE(cursor.goto_row(0) == status_t::not_found);

   REQUIRE(cursor.add_row() == 0);
   REQUIRE(cursor.first_row() == status_t::ok && cursor.rowid() == 0);
   REQUIRE(cursor.last_row() == status_t::ok && cursor.rowid() == 0);
   REQUIRE(cursor.next_row() == status_t::not_found && cursor.rowid() == 0);
   REQUIRE(cursor.prior_row() == status_t::not_found && cursor.rowid() == 0);
   REQUIRE(cursor.goto_row(0) == status_t::ok && cursor.rowid() == 0);
   REQUIRE(tb.get_cursor().column_count() == 4);
   REQUIRE(tb.get_cursor().row_count() == 1);

   REQUIRE(cursor.add_row() == 1);
   REQUIRE(cursor.first_row() == status_t::ok && cursor.rowid() == 0);
   REQUIRE(cursor.last_row() == status_t::ok && cursor.rowid() == 1);
   REQUIRE(cursor.prior_row() == status_t::ok && cursor.rowid() == 0);
   REQUIRE(cursor.next_row() == status_t::ok && cursor.rowid() == 1);
   REQUIRE(cursor.goto_row(1) == status_t::ok && cursor.rowid() == 1);
   REQUIRE(tb.get_cursor().column_count() == 4);
   REQUIRE(tb.get_cursor().row_count() == 2);

   REQUIRE(cursor.add_row() == 2);
   REQUIRE(cursor.first_row() == status_t::ok && cursor.rowid() == 0);
   REQUIRE(cursor.last_row() == status_t::ok && cursor.rowid() == 2);
   REQUIRE(cursor.prior_row() == status_t::ok && cursor.rowid() == 1);
   REQUIRE(cursor.next_row() == status_t::ok && cursor.rowid() == 2);
   REQUIRE(cursor.goto_row(1) == status_t::ok && cursor.rowid() == 1);
   REQUIRE(tb.get_cursor().column_count() == 4);
   REQUIRE(tb.get_cursor().row_count() == 3);

   REQUIRE(cursor.goto_row(2) == status_t::ok && cursor.rowid() == 2);
   REQUIRE(cursor.delete_row() == status_t::ok && cursor.rowid() == 1);
   REQUIRE(tb.get_cursor().column_count() == 4);
   REQUIRE(tb.get_cursor().row_count() == 2);

   REQUIRE(cursor.goto_row(0) == status_t::ok);
   REQUIRE(cursor.write_column(0, make_value("Ricardo")) == status_t::ok);
   REQUIRE(cursor.write_column(1, make_value(18)) == status_t::ok);
   REQUIRE(cursor.write_column(2, make_value(true)) == status_t::ok);
   binary_t bin = { 0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf };
   REQUIRE(cursor.write_column(3, make_value(bin)) == status_t::ok);

   REQUIRE(cursor.read_column_as_string(0) == "Ricardo");
   REQUIRE(cursor.read_column_as_string(1) == "18");
   REQUIRE(cursor.read_column_as_string(2) == "true");
   REQUIRE(cursor.read_column_as_string(3) == encode(bin));

   REQUIRE(cursor.write_column(1, make_value(decimal_t(18))) == status_t::ok);

   REQUIRE(cursor.goto_row(1) == status_t::ok);
   REQUIRE(cursor.read_column_as_string(0) == "null");
   REQUIRE(cursor.read_column_as_string(1) == "null");
   REQUIRE(cursor.read_column_as_string(2) == "null");

   REQUIRE(cursor.is_column_null(0) == true);
}
