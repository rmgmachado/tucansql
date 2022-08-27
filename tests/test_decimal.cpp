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
#include "decimal.h"

using namespace tucan;

const int irows = 6;
const int icols = 2;
const int64_t itable[irows][icols] =
{
	  {INT64_C(123456789),	INT64_C(123456789000000)}
	, {INT64_C(9012345),		INT64_C(9012345000000)}
	, {INT64_C(9012),			INT64_C(9012000000)}
	, {INT64_C(-123456789),	INT64_C(-123456789000000)}
	, {INT64_C(-9012345),	INT64_C(-9012345000000)}
	, {INT64_C(-9012),		INT64_C(-9012000000)}
};

struct data
{
	double lhs;
	int64_t rhs;
};
const int drows = 6;
const data dtable[drows] =
{
	  {123.456789,		INT64_C(123456789)}
	, {9.012345,		INT64_C(9012345)}
	, {0.009012,		INT64_C(9012)}
	, {-123.456789,	INT64_C(-123456789)}
	, {-9.012345,		INT64_C(-9012345)}
	, {-0.009012,		INT64_C(-9012)}
};

TEST_CASE("decimal_t constructor tests", "[decimal]")
{
	SECTION("Test default constructor")
	{
		decimal_t d;
		REQUIRE(d() == 0);
	}
	SECTION("test copy and move constructor")
	{
		decimal_t d = make_decimal(INT64_C(12345678));
		decimal_t e(d);

		REQUIRE(e == make_decimal(INT64_C(12345678)));
		decimal_t c(std::move(d));
		REQUIRE(c == make_decimal(INT64_C(12345678)));
	}
	SECTION("Test int64_t conversion constructor")
	{
		for (int i = 0; i < irows; ++i)
		{
			decimal_t d(itable[i][0]);
			decimal_t res(make_decimal(itable[i][1]));
			REQUIRE(res == d);
		}
	}
	SECTION("Test double conversion constructor")
	{
		for (int i = 0; i < drows; ++i)
		{
			decimal_t d(dtable[i].lhs);
			decimal_t res(make_decimal(dtable[i].rhs));
			REQUIRE(res == d);
		}
	}
}

TEST_CASE("decimal_t assignment test", "[decimal]")
{
	SECTION("test copy and move constructor")
	{
		decimal_t d = make_decimal(INT64_C(12345678));
		decimal_t e;
		decimal_t c;

		e = d;
		REQUIRE(d == e);
		c = std::move(d);
		REQUIRE(d == c);
	}
	SECTION("Test int64_t assignment operator")
	{
		for (int i = 0; i < irows; ++i)
		{
			decimal_t res(make_decimal(itable[i][1]));
			decimal_t d;
			d = itable[i][0];
			REQUIRE(res == d);
		}
	}
	SECTION("Test double assignment operator")
	{
		for (int i = 0; i < drows; ++i)
		{
			decimal_t res(make_decimal(dtable[i].rhs));
			decimal_t d;
			
			d = dtable[i].lhs;
			REQUIRE(res == d);
		}
	}
}

TEST_CASE("decimal_t unary operator test", "[decimal]")
{
	SECTION("Test decimal unary '+' operator")
	{
		const int rows = 6, cols = 2;
		int64_t table[rows][cols] = 
		{
			  {INT64_C(123456789000000),	INT64_C(123456789000000)}
			, {INT64_C(9012345000000),		INT64_C(9012345000000)}
			, {INT64_C(9012000000),			INT64_C(9012000000)}
			, {INT64_C(-123456789000000),	INT64_C(-123456789000000)}
			, {INT64_C(-9012345000000),	INT64_C(-9012345000000)}
			, {INT64_C(-9012000000),		INT64_C(-9012000000)}
		};

		for (int i = 0; i < rows; ++i)
		{
			decimal_t res(make_decimal(table[i][1]));
			decimal_t d(make_decimal(table[i][0]));

			REQUIRE(res == +d);
		}
	}
	SECTION("Test decimal unary '-' operator")
	{
		const int rows = 6, cols = 2;
		int64_t table[rows][cols] =
		{
			  {INT64_C(123456789000000),	INT64_C(-123456789000000)}
			, {INT64_C(9012345000000),		INT64_C(-9012345000000)}
			, {INT64_C(9012000000),			INT64_C(-9012000000)}
			, {INT64_C(-123456789000000),	INT64_C(123456789000000)}
			, {INT64_C(-9012345000000),	INT64_C(9012345000000)}
			, {INT64_C(-9012000000),		INT64_C(9012000000)}
		};

		for (int i = 0; i < rows; ++i)
		{
			decimal_t res(make_decimal(table[i][1]));
			decimal_t d(make_decimal(table[i][0]));

			REQUIRE(res == -d);
		}
	}
}

TEST_CASE("decimal_t cast operator test", "[decimal]")
{
	SECTION("Test int64_t cast operator")
	{
		for (int i = 0; i < irows; ++i)
		{
			decimal_t d(make_decimal(itable[i][1]));
			REQUIRE(itable[i][0] == int64_t(d));
		}
	}
	SECTION("Test double cast operator")
	{
		for (int i = 0; i < drows; ++i)
		{
			decimal_t d(make_decimal(dtable[i].rhs));
			REQUIRE(dtable[i].lhs == double(d));
		}
	}
}

TEST_CASE("decimal_t arithmetic tests", "[decimal]")
{
	const int rows = 24;
	const int cols = 6;
	const int64_t table[rows][cols] = 
	{
	// LHS,			RHS,			Add,			Sub,			Mul,				Div
		{123456789,	9012345,		132469134,	114444444,	1112635175,		13698631		},
		{123456789, 9012,			123465801,	123447777,	1112592,			13699155459	},
		{9012345,	123456789,	132469134,	-114444444, 1112635175,		72999			},
		{9012345,	9012,			9021357,		9003333,		81219,			1000038282	},
		{9012,		123456789,	123465801,	-123447777, 1112592,			72				},
		{9012,		9012345,	   9021357,		-9003333,	81219,			999			},
		{123456789, -9012345,	114444444,	132469134,	-1112635175,	-13698631	},
		{123456789, -9012,		123447777,	123465801,	-1112592,		-13699155459},
		{9012345,	-123456789, -114444444, 132469134,	-1112635175,	-72999		},
		{9012345,	-9012,		9003333,		9021357,		-81219,			-1000038282	},
		{9012,		-123456789, -123447777, 123465801,	-1112592,		-72			},
		{9012,		-9012345,	-9003333,	9021357,		-81219,			-999			},
		{-123456789, 9012345,	-114444444, -132469134, -1112635175,	-13698631	},
		{-123456789, 9012,		-123447777, -123465801, -1112592,		-13699155459},
		{-9012345,	123456789,	114444444,	-132469134, -1112635175,	-72999		},
		{-9012345,	9012,			-9003333,	-9021357,	-81219,			-1000038282	},
		{-9012,		123456789,	123447777,	-123465801, -1112592,		-72			},
		{-9012,		9012345,		9003333,		-9021357,	-81219,			-999			},
		{-123456789,-9012345,	-132469134, -114444444, 1112635175,		13698631		},
		{-123456789,-9012,		-123465801, -123447777, 1112592,			13699155459	},
		{-9012345,	-123456789, -132469134, 114444444,	1112635175,		72999			},
		{-9012345,	-9012,		-9021357,	-9003333,	81219,			1000038282	},
		{-9012,		-123456789, -123465801, 123447777,	1112592,			72				},
		{-9012,		-9012345,	-9021357,	9003333,		81219,			999			}			
	};

	// test decimal arithmetic operators
	for (int i = 0; i < rows; ++i)
	{
		decimal_t lhs = make_decimal(table[i][0]);
		decimal_t rhs = make_decimal(table[i][1]);
		decimal_t add = make_decimal(table[i][2]);
		decimal_t sub = make_decimal(table[i][3]);
		decimal_t mul = make_decimal(table[i][4]);
		decimal_t div = make_decimal(table[i][5]);
		decimal_t res;

		res = lhs + rhs;
		REQUIRE(add == res);
		res = lhs - rhs;
		REQUIRE(sub == res);
		res = lhs * rhs;
		REQUIRE(mul == res);
		res = lhs / rhs;
		REQUIRE(div == res);
	}
}

TEST_CASE("decimal_t comparison tests", "[decimal]")
{
	const int rows = 25;
	struct data
	{
		int64_t lhs, rhs;
		bool eq, ne, lt, le, gt, ge;
	};
	const data table[rows] =
	{
		// LHS,			RHS,			eq,		ne,		lt,		le,		gt,		ge
			{123456789,	123456789,	true,		false,	false,	true,		false, 	true	},
			{123456789,	9012345,		false,	true,		false,	false,	true,		true	},
			{123456789, 9012,			false,	true,		false,	false,	true,		true	},
			{9012345,	123456789,	false,	true,		true,		true,		false,	false	},
			{9012345,	9012,			false,	true,		false,	false,	true,		true	},
			{9012,		123456789,	false,	true,		true,		true,  	false,	false	},
			{9012,		9012345,	   false,	true,		true,		true,	   false,	false	},
			{-9012345,	-9012345,	true,		false,	false,	true,	   false,	true	},
			{123456789, -9012,		false,	true,		false,	false,	true,		true	},
			{9012345,	-123456789, false,	true,		false,	false,	true,		true	},
			{9012345,	-9012,		false,	true,		false,	false,	true,		true	},
			{9012,		-123456789, false,	true,		false,	false,	true,		true	},
			{9012,		-9012345,	false,	true,		false,	false,	true,		true	},
			{-123456789, 9012345,	false,	true,		true,		true,	   false,	false	},
			{-123456789, 9012,		false,	true,		true,		true,	   false,	false	},
			{-9012345,	123456789,	false,	true,		true,		true,	 	false,	false	},
			{-9012345,	9012,			false,	true,		true,		true,	   false,	false	},
			{-9012,		123456789,	false,	true,		true,		true,	   false,	false	},
			{-9012,		9012345,		false,	true,		true,		true,	   false,	false	},
			{-123456789,-9012345,	false,	true,		true,		true,	   false,	false	},
			{-123456789,-9012,		false,	true,		true,		true,	   false,	false	},
			{-9012345,	-123456789, false,	true,		false,	false,	true,		true	},
			{-9012345,	-9012,		false,	true,		true,		true,		false,	false	},
			{-9012,		-123456789, false,	true,		false,	false,	true,		true	},
			{-9012,		-9012345,	false,	true,		false,	false,	true,		true	}
	};

	for (int i = 0; i < rows; ++i)
	{
		decimal_t lhs = make_decimal(table[i].lhs);
		decimal_t rhs = make_decimal(table[i].rhs);

		REQUIRE(table[i].eq == (lhs == rhs));
		REQUIRE(table[i].ne == (lhs != rhs));
		REQUIRE(table[i].lt == (lhs < rhs));
		REQUIRE(table[i].le == (lhs <= rhs));
		REQUIRE(table[i].gt == (lhs > rhs));
		REQUIRE(table[i].ge == (lhs >= rhs));
	}
}

std::string ostream_str(const int64_t& val)
{
	decimal_t dec = make_decimal(val);
	std::ostringstream os(std::to_string(make_decimal(val)));
	return os.str();
}

decimal_t istream_str(const std::string& str)
{
	decimal_t dec;
	std::istringstream is(str);
	is >> dec;
	return dec;
}

TEST_CASE("decimal_t stream operator tests", "[decimal]")
{
	SECTION("Test ostream operator")
	{
		REQUIRE(ostream_str(0) == "0");
		REQUIRE(ostream_str(123456789) == "123.456789");
		REQUIRE(ostream_str(9012340) == "9.01234");
		REQUIRE(ostream_str(9012300) == "9.0123");
		REQUIRE(ostream_str(9012) == "0.009012");
		REQUIRE(ostream_str(123000000) == "123");
		REQUIRE(ostream_str(-123456789) == "-123.456789");
		REQUIRE(ostream_str(-9012340) == "-9.01234");
		REQUIRE(ostream_str(-9012300) == "-9.0123");
		REQUIRE(ostream_str(-9012) == "-0.009012");
		REQUIRE(ostream_str(-123000000) == "-123");
		REQUIRE(ostream_str(-0) == "0");
	}
	SECTION("Test istream operator")
	{
		REQUIRE(istream_str("0") == make_decimal(0ll));
		REQUIRE(istream_str("123.456789") == make_decimal(123456789ll));
		REQUIRE(istream_str("1234567890123.456789") == make_decimal(1234567890123456789ll));
		REQUIRE(istream_str("9.01234") == make_decimal(9012340ll));
		REQUIRE(istream_str("9.0123") == make_decimal(9012300ll));
		REQUIRE(istream_str("0.009012") == make_decimal(9012ll));
		REQUIRE(istream_str("123") == make_decimal(123000000ll));

		REQUIRE(istream_str("-123.456789") == make_decimal(-123456789ll));
		REQUIRE(istream_str("-1234567890123.456789") == make_decimal(-1234567890123456789ll));
		REQUIRE(istream_str("-9.01234") == make_decimal(-9012340ll));
		REQUIRE(istream_str("-9.0123") == make_decimal(-9012300ll));
		REQUIRE(istream_str("-0.009012") == make_decimal(-9012ll));
		REQUIRE(istream_str("-123") == make_decimal(-123000000ll));

	}
}