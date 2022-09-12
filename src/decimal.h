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

#include <cstdint>
#include <utility>
#include <array>
#include <cassert>
#include <sstream>
#include <iomanip>

#include "utility.h"

/*****************************************************************************\
*	(From Wikipwdia)
*	In computing, a fixed-point number representation is a real data type for
*	a number that has a fixed number of digits after the decimal point '.'.
*	Fixed-point number representation can be compared to the more complicated
*	(and more computationally demanding) floating-point number representation.
*	Fixed-point numbers are useful for representing fractional values, usually
*	in base 2 or base 10.
*
*	A value of a fixed-point data type is essentially an integer that is
*	scaled by an implicit specific factor determined by the type. For example,
*	the value 1.23 can be represented as 1230 in a fixed-point data type with
*	scaling factor of 100.
*
\*****************************************************************************/

namespace tucan {

	namespace decimal
	{
		const unsigned min_scale = 0;
		const unsigned max_scale = 8;

		const std::array<int64_t, 10> precision =
		{
			  INT64_C(1)
			, INT64_C(10)
			, INT64_C(100)
			, INT64_C(1000)
			, INT64_C(10000)
			, INT64_C(10000)
			, INT64_C(1000000)
			, INT64_C(1000000)
			, INT64_C(100000000)
			, INT64_C(1000000000)
		};

		// return true if x and y have different sign
		inline bool opposite_sign(const int64_t& x, const int64_t& y)  noexcept
		{
			return ((x ^ y) < 0);
		}

		// unsigned multiplication
		inline uint64_t umultiply(const uint64_t& lhs, const uint64_t& rhs, unsigned scale) noexcept
		{
			assert(scale <= max_scale);
			int64_t prec = precision[scale];
			return (lhs * (rhs / prec) + (lhs * (rhs % prec)) / prec);
		}

		// unsigned division
		inline uint64_t udivide(const uint64_t& lhs, const uint64_t& rhs, unsigned scale) noexcept(false)
		{
			assert(scale <= max_scale);
			int64_t prec = precision[scale];
			uint64_t left = lhs;
			uint64_t retval = 0;
			uint64_t remainder;
			while (prec > 0)
			{
				remainder = left % rhs;
				retval = (retval + ((left / rhs) * prec));
				left = remainder * 10;
				prec /= 10;
			}
			return retval;
		}

		// signed multiplication
		inline int64_t multiply(const int64_t& lhs, const int64_t& rhs, unsigned scale) noexcept
		{
			int64_t retval = umultiply(std::abs(lhs), std::abs(rhs), scale);
			return opposite_sign(lhs, rhs) ? -retval : retval;
		}

		// signed division
		inline int64_t divide(const int64_t& lhs, const int64_t& rhs, unsigned scale) noexcept
		{
			int64_t retval = udivide(std::abs(lhs), std::abs(rhs), scale);
			return opposite_sign(lhs, rhs) ? -retval : retval;
		}

	} // namespace decimal

	template <int SCALE>
	class decimal_base_t
	{
		int64_t dec_;

	public:
		decimal_base_t() noexcept
			: dec_(0)
		{}

		~decimal_base_t() = default;
		decimal_base_t(const decimal_base_t& other) noexcept = default;
		decimal_base_t(decimal_base_t&& other) noexcept = default;

		explicit decimal_base_t(const short& value) noexcept
			: dec_(value * decimal::precision[SCALE])
		{}

		explicit decimal_base_t(const int& value) noexcept
			: dec_(value * decimal::precision[SCALE])
		{}

		explicit decimal_base_t(const long int& value) noexcept
			: dec_(value * decimal::precision[SCALE])
		{}

		explicit decimal_base_t(const long long int& value) noexcept
			: dec_(value * decimal::precision[SCALE])
		{}

		explicit decimal_base_t(const double& value) noexcept
			: dec_(int64_t(value * double(decimal::precision[SCALE])))
		{}

		decimal_base_t(long long int integer, long long int frac) noexcept
			: dec_((integer* decimal::precision[SCALE]) + frac)
		{}

		decimal_base_t& operator=(const decimal_base_t& other) noexcept = default;
		decimal_base_t& operator=(decimal_base_t&& other) noexcept = default;

		decimal_base_t& operator=(const int64_t& value) noexcept
		{
			dec_ = value * decimal::precision[SCALE];
			return *this;
		}

		decimal_base_t& operator=(const double& value) noexcept
		{
			dec_ = int64_t(value * decimal::precision[SCALE]);
			return *this;
		}

		decimal_base_t operator+() const noexcept
		{
			return *this;
		}

		decimal_base_t operator-() const noexcept
		{
			decimal_base_t retval;
			retval.dec_ = -dec_;
			return retval;
		}

		operator char() const noexcept
		{
			return char(dec_ / decimal::precision[SCALE]);
		}

		operator short() const noexcept
		{
			return short(dec_ / decimal::precision[SCALE]);
		}

		operator int() const noexcept
		{
			return int(dec_ / decimal::precision[SCALE]);
		}

		operator long() const noexcept
		{
			return long(dec_ / decimal::precision[SCALE]);
		}

		explicit operator long long() const  noexcept
		{
			return dec_ / decimal::precision[SCALE];
		}

		explicit operator double() const  noexcept
		{
			double retval(static_cast<double>(dec_));
			return retval / decimal::precision[SCALE];
		}

		decimal_base_t& operator+=(const decimal_base_t& other) noexcept
		{
			dec_ += other.dec_;
			return *this;
		}

		decimal_base_t& operator-=(const decimal_base_t& other) noexcept
		{
			dec_ -= other.dec_;
			return *this;
		}

		decimal_base_t& operator*=(const decimal_base_t& other) noexcept
		{
			dec_ = decimal::multiply(dec_, other.dec_, SCALE);
			return *this;
		}

		decimal_base_t& operator/=(const decimal_base_t& other) noexcept(false)
		{
			dec_ = decimal::divide(dec_, other.dec_, SCALE);
			return *this;
			return *this;
		}

		decimal_base_t operator+(const decimal_base_t& rhs) const noexcept
		{
			decimal_base_t retval(*this);
			retval += rhs;
			return retval;
		}

		decimal_base_t operator-(const decimal_base_t& rhs) const noexcept
		{
			decimal_base_t retval(*this);
			retval -= rhs;
			return retval;
		}

		decimal_base_t operator*(const decimal_base_t& rhs) const noexcept
		{
			decimal_base_t retval(*this);
			retval *= rhs;
			return retval;
		}

		decimal_base_t operator/(const decimal_base_t& rhs) const noexcept(false)
		{
			decimal_base_t retval(*this);
			retval /= rhs;
			return retval;
		}

		int64_t precision() const noexcept
		{
			return decimal::precision[SCALE];
		}

		bool operator==(const decimal_base_t& other) const noexcept
		{
			return dec_ == other.dec_;
		}

		bool operator!=(const decimal_base_t& other) const noexcept
		{
			return dec_ != other.dec_;
		}

		bool operator<(const decimal_base_t& other) const noexcept
		{
			return dec_ < other.dec_;
		}

		bool operator<=(const decimal_base_t& other) const noexcept
		{
			return dec_ <= other.dec_;
		}

		bool operator>(const decimal_base_t& other) const noexcept
		{
			return dec_ > other.dec_;
		}

		bool operator>=(const decimal_base_t& other) const noexcept
		{
			return dec_ >= other.dec_;
		}

		int64_t operator()() const
		{
			return dec_;
		}

		static int scale()
		{
			return SCALE;
		}
	};

	using decimal_t = decimal_base_t<6>;

	inline decimal_t make_decimal(int64_t n) noexcept
	{
		return decimal_t((n / decimal::precision[decimal_t::scale()]), (n % decimal::precision[decimal_t::scale()]));
	}

} //namespace tucan

namespace std
{
	template <int SCALE>
	inline std::string to_string(const tucan::decimal_base_t<SCALE>& dec) noexcept
	{
		int64_t integer = int64_t(dec() / tucan::decimal::precision[SCALE]);
		std::string str = std::to_string(integer);
		int64_t frac = std::abs(dec()) % tucan::decimal::precision[SCALE];

		if (integer == 0 && dec() < 0)
		{
			str = "-" + str;
		}
		if (frac > 0)
		{
			std::string frac_str = std::to_string(frac);
			int scale = SCALE - int(frac_str.length());

			if (scale > 0)
			{
				frac_str = std::string(scale, '0') + frac_str;
			}
			frac_str.erase(frac_str.find_last_not_of('0') + 1, std::string::npos);
			str = str + "." + frac_str;
		}
		return str;
	}
} // namespace std

namespace tucan {
	template <int SCALE>
	inline std::ostream& operator<<(std::ostream& os, const decimal_base_t<SCALE>& dec)
	{
		os << std::to_string(dec);
		return os;
	}

	template <int SCALE>
	inline std::istream& operator>>(std::istream& is, decimal_base_t<SCALE>& dec)
	{
		int64_t value = 0;
		dec = make_decimal(0ll);
		skip_spaces(is);
		bool negate = get_separator(is, '-');
		if (get_digits(is, value) == 0) return is;
		if (get_separator(is, '.'))
		{
			for (int i = 0; i < SCALE; ++i)
			{
				value *= 10ll;
				if (!is.eof() && std::isdigit(is.peek()))
				{
					value += (char(is.get()) - '0');
				}
			}
			while (!is.eof() && std::isdigit(is.peek()))
			{
				is.get();
			}
		}
		else
		{
			value *= decimal::precision[SCALE];
		}
		dec = make_decimal(negate ? -value : value);
		return is;
	}

	inline decimal_t make_decimal(const std::string& str) noexcept
	{
		decimal_t dec;
		if (validate_decimal(str))
		{
			std::istringstream is(str);
			is >> dec;
		}
		return dec;
	}

	template <int SCALE>
	inline bool operator==(const decimal_base_t<SCALE>& lhs, const int64_t& rhs) noexcept
	{
		return lhs == decimal_base_t<SCALE>(rhs);
	}

	template <int SCALE>
	inline bool operator==(const int64_t& lhs, const decimal_base_t<SCALE>& rhs) noexcept
	{
		return decimal_base_t<SCALE>(lhs) == rhs;
	}

	template <int SCALE>
	inline bool operator==(const decimal_base_t<SCALE>& lhs, const double& rhs) noexcept
	{
		return lhs == decimal_base_t<SCALE>(rhs);
	}

	template <int SCALE>
	inline bool operator==(const double& lhs, const decimal_base_t<SCALE>& rhs) noexcept
	{
		return decimal_base_t<SCALE>(lhs) == rhs;
	}

	template <int SCALE>
	inline bool operator!=(const decimal_base_t<SCALE>& lhs, const int64_t& rhs) noexcept
	{
		return lhs != decimal_base_t<SCALE>(rhs);
	}

	template <int SCALE>
	inline bool operator!=(const int64_t& lhs, const decimal_base_t<SCALE>& rhs) noexcept
	{
		return decimal_base_t<SCALE>(lhs) != rhs;
	}

	template <int SCALE>
	inline bool operator!=(const decimal_base_t<SCALE>& lhs, const double& rhs) noexcept
	{
		return lhs != decimal_base_t<SCALE>(rhs);
	}

	template <int SCALE>
	inline bool operator!=(const double& lhs, const decimal_base_t<SCALE>& rhs) noexcept
	{
		return decimal_base_t<SCALE>(lhs) != rhs;
	}

	template <int SCALE>
	inline bool operator<(const decimal_base_t<SCALE>& lhs, const int64_t& rhs) noexcept
	{
		return lhs < decimal_base_t<SCALE>(rhs);
	}

	template <int SCALE>
	inline bool operator<(const int64_t& lhs, const decimal_base_t<SCALE>& rhs) noexcept
	{
		return decimal_base_t<SCALE>(lhs) < rhs;
	}

	template <int SCALE>
	inline bool operator<(const decimal_base_t<SCALE>& lhs, const double& rhs) noexcept
	{
		return lhs < decimal_base_t<SCALE>(rhs);
	}

	template <int SCALE>
	inline bool operator<(const double& lhs, const decimal_base_t<SCALE>& rhs) noexcept
	{
		return decimal_base_t<SCALE>(lhs) < rhs;
	}

	template <int SCALE>
	inline bool operator<=(const decimal_base_t<SCALE>& lhs, const int64_t& rhs) noexcept
	{
		return lhs <= decimal_base_t<SCALE>(rhs);
	}

	template <int SCALE>
	inline bool operator<=(const int64_t& lhs, const decimal_base_t<SCALE>& rhs) noexcept
	{
		return decimal_base_t<SCALE>(lhs) <= rhs;
	}

	template <int SCALE>
	inline bool operator<=(const decimal_base_t<SCALE>& lhs, const double& rhs) noexcept
	{
		return lhs <= decimal_base_t<SCALE>(rhs);
	}

	template <int SCALE>
	inline bool operator<=(const double& lhs, const decimal_base_t<SCALE>& rhs) noexcept
	{
		return decimal_base_t<SCALE>(lhs) <= rhs;
	}

	template <int SCALE>
	inline bool operator>(const decimal_base_t<SCALE>& lhs, const int64_t& rhs) noexcept
	{
		return lhs > decimal_base_t<SCALE>(rhs);
	}

	template <int SCALE>
	inline bool operator>(const int64_t& lhs, const decimal_base_t<SCALE>& rhs) noexcept
	{
		return decimal_base_t<SCALE>(lhs) > rhs;
	}

	template <int SCALE>
	inline bool operator>(const decimal_base_t<SCALE>& lhs, const double& rhs) noexcept
	{
		return lhs > decimal_base_t<SCALE>(rhs);
	}

	template <int SCALE>
	inline bool operator>(const double& lhs, const decimal_base_t<SCALE>& rhs) noexcept
	{
		return decimal_base_t<SCALE>(lhs) > rhs;
	}

	template <int SCALE>
	inline bool operator>=(const decimal_base_t<SCALE>& lhs, const int64_t& rhs) noexcept
	{
		return lhs >= decimal_base_t<SCALE>(rhs);
	}

	template <int SCALE>
	inline bool operator>=(const int64_t& lhs, const decimal_base_t<SCALE>& rhs) noexcept
	{
		return decimal_base_t<SCALE>(lhs) >= rhs;
	}

	template <int SCALE>
	inline bool operator>=(const decimal_base_t<SCALE>& lhs, const double& rhs) noexcept
	{
		return lhs >= decimal_base_t<SCALE>(rhs);
	}

	template <int SCALE>
	inline bool operator>=(const double& lhs, const decimal_base_t<SCALE>& rhs) noexcept
	{
		return decimal_base_t<SCALE>(lhs) >= rhs;
	}

} // namespace tucandb
