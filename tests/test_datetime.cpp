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
#include <datetime.h>

using namespace tucan;

TEST_CASE("datetime_t constructor tests", "[datetime]")
{
	SECTION("Test default constructor")
	{
		datetime_t dt;
		REQUIRE(uint64_t(0) == dt());
		REQUIRE(1601 == datetime_part(dt, datetime_part_t::year));
		REQUIRE(1 == datetime_part(dt, datetime_part_t::month));
		REQUIRE(1 == datetime_part(dt, datetime_part_t::day));
		REQUIRE(0 == datetime_part(dt, datetime_part_t::hour));
		REQUIRE(0 == datetime_part(dt, datetime_part_t::minute));
		REQUIRE(0 == datetime_part(dt, datetime_part_t::second));
		REQUIRE(0 == datetime_part(dt, datetime_part_t::microsecs));
	}

	SECTION("Test copy constructor")
	{
		datetime_t dt(make_datetime(2021, 8, 26, 21, 34, 43));
		REQUIRE(2021 == datetime_part(dt, datetime_part_t::year));
		REQUIRE(8 == datetime_part(dt, datetime_part_t::month));
		REQUIRE(26 == datetime_part(dt, datetime_part_t::day));
		REQUIRE(21 == datetime_part(dt, datetime_part_t::hour));
		REQUIRE(34 == datetime_part(dt, datetime_part_t::minute));
		REQUIRE(43 == datetime_part(dt, datetime_part_t::second));
		REQUIRE(0 == datetime_part(dt, datetime_part_t::microsecs));
	}

	SECTION("Test move constructor")
	{
		datetime_t t(make_datetime(2021, 8, 26, 21, 34, 43));
		datetime_t dt(std::move(t));
		REQUIRE(2021 == datetime_part(dt, datetime_part_t::year));
		REQUIRE(8 == datetime_part(dt, datetime_part_t::month));
		REQUIRE(26 == datetime_part(dt, datetime_part_t::day));
		REQUIRE(21 == datetime_part(dt, datetime_part_t::hour));
		REQUIRE(34 == datetime_part(dt, datetime_part_t::minute));
		REQUIRE(43 == datetime_part(dt, datetime_part_t::second));
		REQUIRE(0 == datetime_part(dt, datetime_part_t::microsecs));
	}

	SECTION("Test copy operator")
	{
		datetime_t t(make_datetime(2021, 8, 26, 21, 34, 43));
		datetime_t dt;
		dt = t;
		REQUIRE(2021 == datetime_part(dt, datetime_part_t::year));
		REQUIRE(8 == datetime_part(dt, datetime_part_t::month));
		REQUIRE(26 == datetime_part(dt, datetime_part_t::day));
		REQUIRE(21 == datetime_part(dt, datetime_part_t::hour));
		REQUIRE(34 == datetime_part(dt, datetime_part_t::minute));
		REQUIRE(43 == datetime_part(dt, datetime_part_t::second));
		REQUIRE(0 == datetime_part(dt, datetime_part_t::microsecs));
	}

	SECTION("Test move operator")
	{
		datetime_t t(make_datetime(2021, 8, 26, 21, 34, 43));
		datetime_t dt;
		dt = std::move(t);
		REQUIRE(2021 == datetime_part(dt, datetime_part_t::year));
		REQUIRE(8 == datetime_part(dt, datetime_part_t::month));
		REQUIRE(26 == datetime_part(dt, datetime_part_t::day));
		REQUIRE(21 == datetime_part(dt, datetime_part_t::hour));
		REQUIRE(34 == datetime_part(dt, datetime_part_t::minute));
		REQUIRE(43 == datetime_part(dt, datetime_part_t::second));
		REQUIRE(0 == datetime_part(dt, datetime_part_t::microsecs));
	}
}

struct datetime_test_t
{
	std::string str;
	int year, month, day, hour, min, sec, msecs;
};

datetime_test_t dt_test_cases[] =
{
	  {"2022-08-22 23:30:07.123456", 2022, 8, 22, 23, 30, 7, 123456}
	, {"2021-03-10 03:11:34.12", 2021, 3, 10, 3, 11, 34, 12}
	, {"2017-01-10 11:32:04", 2017, 1, 10, 11, 32, 4, 0}
	, {"2017-01-10 11:32", 2017, 1, 10, 11, 32, 0, 0}
	, {"2017-01-10 11", 2017, 1, 10, 11, 0, 0, 0}
};

TEST_CASE("datetime_t make_datetime tests", "[datetime]")
{
	datetime_t dt;
	for (auto& test : dt_test_cases)
	{
		datetime_t dt = make_datetime(test.str);
		REQUIRE(datetime_part(dt, datetime_part_t::year) == test.year);
		REQUIRE(datetime_part(dt, datetime_part_t::month) == test.month);
		REQUIRE(datetime_part(dt, datetime_part_t::day) == test.day);
		REQUIRE(datetime_part(dt, datetime_part_t::hour) == test.hour);
		REQUIRE(datetime_part(dt, datetime_part_t::minute) == test.min);
		REQUIRE(datetime_part(dt, datetime_part_t::second) == test.sec);
		REQUIRE(datetime_part(dt, datetime_part_t::microsecs) == test.msecs);
	}
}

TEST_CASE("datetime_t ostream operator tests", "[datetime]")
{
	datetime_t dt;
	for (auto& test : dt_test_cases)
	{
		datetime_t dt = make_datetime(test.year, test.month, test.day, test.hour, test.min, test.sec, test.msecs);
		std::string str = std::to_string(dt);
		REQUIRE( str == test.str);
	}
	SECTION("datetime_t to_string with ' '")
	{
		datetime_t dt = make_datetime(2022, 8, 22, 0, 43, 17, 1234);
		std::string str = std::to_string(dt);
		REQUIRE(str == "2022-08-22 00:43:17.1234");
		str = std::to_string(dt, 'T');
		REQUIRE(str == "2022-08-22T00:43:17.1234");
		str = std::to_string(dt, 't');
		REQUIRE(str == "2022-08-22t00:43:17.1234");
	}
}

