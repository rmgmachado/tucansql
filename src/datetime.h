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

#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include <array>
#include <cassert>
#include <stdexcept>

#include "system.h"
#include "utility.h"

#ifdef XP_OS_WIN32
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#include <sysinfoapi.h>

	#ifdef __cplusplus
		extern "C" {
	#endif

	// implement a Linux compatible clock_gettime runtime function for Windows
	inline int clock_gettime(int, struct timespec* spec)      //C-file part
	{
		int64_t wintime;
		FILETIME filtime;
		LARGE_INTEGER li;
		GetSystemTimeAsFileTime(&filtime);
		li.LowPart = filtime.dwLowDateTime;
		li.HighPart = filtime.dwHighDateTime;
		wintime = li.QuadPart - INT64_C(116444736000000000);  //1jan1601 to 1jan1970
		spec->tv_sec = wintime / INT64_C(10000000);           //seconds
		spec->tv_nsec = (wintime % INT64_C(10000000));
		spec->tv_nsec *= INT64_C(100);								//nano-seconds
		return 0;
	}

	#ifdef __cplusplus
		} /* extern "C" */
	#endif

#endif // XP_OS_WIN32

namespace tucan {

	namespace datetime {

		constexpr uint64_t JAN_1_1601 = INT64_C(2305814);   // take datetime to Jan 1 1601
		constexpr uint64_t MAX_HOUR = 24;
		constexpr uint64_t MAX_MINUTE = 60;
		constexpr uint64_t MAX_SECOND = 60;
		constexpr uint64_t MAX_MICROSECS = 1000000;
		constexpr uint64_t MAX_TIME = uint64_t(MAX_HOUR * MAX_MINUTE * MAX_SECOND * MAX_MICROSECS);
		constexpr uint64_t HOUR_FACTOR = (MAX_MINUTE * MAX_SECOND * MAX_MICROSECS);
		constexpr uint64_t MINUTE_FACTOR = (MAX_SECOND * MAX_MICROSECS);
		constexpr uint64_t SECOND_FACTOR = MAX_MICROSECS;

		inline uint64_t date_make(int year, int month, int day)
		{
			auto date = static_cast<uint64_t>(((1461 * (year + 4800 + (month - 14) / 12)) / 4 + (367 * (month - 2 - 12 * ((month - 14) / 12))) / 12 - (3 * ((year + 4900 + (month - 14) / 12) / 100)) / 4 + day - 32075));
			return (date - JAN_1_1601) * MAX_TIME;

		}

		inline uint64_t get_date(uint64_t dt)
		{
			return (dt / MAX_TIME) * MAX_TIME;
		}

		inline uint64_t get_time(uint64_t dt)
		{
			return dt % MAX_TIME;
		}

		inline void date_split(const uint64_t& date, int& year, int& month, int& day)
		{
			int l, n, i, j;
			l = int(date / MAX_TIME) + JAN_1_1601 + 68569;
			n = (4 * l) / 146097;
			l = l - (146097 * n + 3) / 4;
			i = (4000 * (l + 1)) / 1461001;
			l = l - (1461 * i) / 4 + 31;
			j = (80 * l) / 2447;
			day = l - (2447 * j) / 80;
			l = j / 11;
			month = j + 2 - (12 * l);
			year = 100 * (n - 49) + i + l;
		}

		inline int day_of_week(const uint64_t& date)
		{
			return ((date / MAX_TIME) + JAN_1_1601) % 7;
		}

		inline uint64_t time_make(int hour, int minute, int seconds = 0, int microsecs = 0)
		{
			return (hour * MAX_MINUTE * MAX_SECOND * MAX_MICROSECS) + (minute * MAX_SECOND * MAX_MICROSECS) + (seconds * MAX_MICROSECS) + microsecs;
		}

		inline void time_split(const uint64_t& time, int& hour, int& minute, int& seconds, int& microsecs)
		{
			uint64_t temp = (time % MAX_TIME);
			hour = int(temp / HOUR_FACTOR);
			temp = temp % HOUR_FACTOR;
			minute = int(temp / MINUTE_FACTOR);
			temp = temp % MINUTE_FACTOR;
			seconds = int(temp / SECOND_FACTOR);
			microsecs = int(temp % SECOND_FACTOR);
		}

		inline bool is_leap_year(int year)
		{
			return (year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0);
		}

		inline bool get_date(std::istream& is, int& year, int& month, int& day)
		{
			if (get_digits(is, year, 4) == 0) return false;
			if (!get_separator(is, '-')) return false;
			if (get_digits(is, month, 2) == 0) return false;
			if (!get_separator(is, '-')) return false;
			if (get_digits(is, day, 2) == 0) return false;
			return true;
		}

		inline bool get_time(std::istream& is, int& hour, int& min, int& sec, int& msecs)
		{
			hour = min = sec = msecs = 0;
			if (!(get_separator(is, 'T') || get_separator(is, 't') || get_separator(is, ' '))) return false;
			if (get_digits(is, hour, 2) == 0) return false;
			if (get_separator(is, ':') && get_digits(is, min, 2) > 0)
			{
				if (get_separator(is, ':') && get_digits(is, sec, 2) > 0)
				{
					get_separator(is, '.') && get_digits(is, msecs, 6);
				}
			}
			return true;
		}
	} // namespace datetime

	// week represent the day of the week with monday = 0, tuesday = 1, ...
	// count represent the day count within the year
	enum class datetime_part_t { year, month, day, week, count, hour, minute, second, microsecs };

	class datetime_t
	{
		uint64_t dt_;		// represents the number of microseconds since midnight Jan 1 1601

		public:
			datetime_t() noexcept 
				: dt_(0) 
			{}
			
			~datetime_t() = default;
			datetime_t(const datetime_t& other) noexcept = default;
			datetime_t(datetime_t&& other)  noexcept = default;
			datetime_t& operator=(const datetime_t& other) noexcept = default;
			datetime_t& operator=(datetime_t&& other) noexcept = default;

			explicit datetime_t(uint64_t dt) noexcept
				: dt_(dt)
			{}

			uint64_t operator()() const noexcept
			{
				return dt_;
			}

			bool operator==(const datetime_t& other) const noexcept
			{
				return dt_ == other.dt_;
			}

			bool operator!=(const datetime_t& other) const noexcept
			{
				return dt_ != other.dt_;
			}

			bool operator<(const datetime_t& other) const noexcept
			{
				return dt_ < other.dt_;
			}

			bool operator<=(const datetime_t& other) const noexcept
			{
				return dt_ <= other.dt_;
			}

			bool operator>(const datetime_t& other) const noexcept
			{
				return dt_ > other.dt_;
			}

			bool operator>=(const datetime_t& other) const noexcept
			{
				return dt_ >= other.dt_;
			}

	};

	inline datetime_t make_datetime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int microsecs = 0) noexcept
	{
		assert(year >= 1601);
		assert(month >= 1 && month <= 12);
		assert(day >= 1 && day <= 31);
		assert(hour >= 0 && hour < 24);
		assert(minute >= 0 && minute < 60);
		assert(second >= 0 && second < 60);
		assert(microsecs >= 0);
		return datetime_t((datetime::date_make(year, month, day) + datetime::time_make(hour, minute, second, microsecs)));
	}

	inline int split_date(const datetime_t& dt, datetime_part_t part) noexcept
	{
		int year;
		int month;
		int day;

		datetime::date_split(datetime::get_date(dt()), year, month, day);
		if (part == datetime_part_t::year) return year;
		if (part == datetime_part_t::month) return month;
		if (part == datetime_part_t::day) return day;
		if (part == datetime_part_t::week) return int(((dt() / datetime::MAX_TIME) + datetime::JAN_1_1601) % 7); // 0 Monday, 1 Tuesday, ....
		if (part == datetime_part_t::count) return int(make_datetime(year, month, day)() - make_datetime(year, 1, 1)());
		return 0;
	}

	inline int split_time(const datetime_t& dt, datetime_part_t part) noexcept
	{	
		int hour;
		int minute;
		int second;
		int microsecs;

		datetime::time_split(datetime::get_time(dt()), hour, minute, second, microsecs);
		if (part == datetime_part_t::hour) return hour;
		if (part == datetime_part_t::minute) return minute;
		if (part == datetime_part_t::second) return second;
		if (part == datetime_part_t::microsecs) return microsecs;
		return 0;
	}

	inline int split_datetime(const datetime_t& dt, datetime_part_t part) noexcept
	{
		if (part >= datetime_part_t::hour) return split_time(dt, part);
		return split_date(dt, part);
	}

	inline int datetime_part(const datetime_t& dt, datetime_part_t part) noexcept
	{
		return split_datetime(dt, part);
	}

	inline bool is_leap_year(int year) noexcept
	{
		assert(year >= 1601);
		return (year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0);
	}

	inline bool is_leap_year(const datetime_t& dt) noexcept
	{
		return is_leap_year(split_date(dt, datetime_part_t::year));
	}

	// throws std::range_error if resulting year is less than 1601
	inline datetime_t add_years(const datetime_t& dt, int value)
	{
		int year;
		int month;
		int day;

		datetime::date_split(datetime::get_date(dt()), year, month, day);
		year += value;
		if (year < 1601) throw std::range_error("year less than 1601");
		if (!is_leap_year(year) && month == 2 && day > 28) day = 28;
		return datetime_t(datetime::date_make(year, month, day) + (dt() % datetime::MAX_TIME));
	}

	inline datetime_t add_months(const datetime_t& dt, int value)
	{
		int year;
		int month;
		int day;

		datetime::date_split(datetime::get_date(dt()), year, month, day);
		month = (month - 1) + value;
		if (month < 0)
		{
			year = year - 1 - (std::abs(month) / 12);
			month = (12 - (month % 12)) + 1;
		}
		else
		{
			year += month / 12;
			month = (month %12) + 1;
		}
		if (year < 1601) throw std::range_error("year less than 1601");
		if (!is_leap_year(year) && month == 2 && day > 28) day = 28;
		return datetime_t(datetime::date_make(year, month, day) + (dt() % datetime::MAX_TIME));
	}

	// to subract pass a negative value
	inline datetime_t datetime_add(const datetime_t& dt, datetime_part_t part, int value) noexcept
	{
		uint64_t multiplier{0};
		switch (part)
		{
		   case datetime_part_t::year: return add_years(dt, value);
		   case datetime_part_t::month: return add_months(dt, value);
			case datetime_part_t::week: value *= 7; multiplier = datetime::MAX_TIME; break;
		   case datetime_part_t::count: return dt;
			case datetime_part_t::day: multiplier = datetime::MAX_TIME; break;
			case datetime_part_t::hour: multiplier = datetime::MAX_MINUTE * datetime::MAX_SECOND * datetime::MAX_MICROSECS; break;
			case datetime_part_t::minute: multiplier = datetime::MAX_SECOND * datetime::MAX_MICROSECS; break;
			case datetime_part_t::second: multiplier = datetime::MAX_MICROSECS; break;
			default: multiplier = 0; break;
		}
		return datetime_t(dt() + (value * multiplier));
	}

	// return the current date and time as UTC 
	inline datetime_t today() noexcept
	{
		struct timespec spec;
		struct tm tm;

		clock_gettime(0, &spec);
		gmtime_r(&spec.tv_sec, &tm);
		return make_datetime(tm.tm_year, (tm.tm_mon + 1), tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, (spec.tv_nsec / 1000));
	}

	inline std::ostream& operator<<(std::ostream& os, const datetime_t& dt) noexcept
	{
		os << std::setw(4) << std::setfill('0') << datetime_part(dt, datetime_part_t::year) ;
		os << "-" << std::setw(2) << std::setfill('0') << datetime_part(dt, datetime_part_t::month);
		os << "-" << std::setw(2) << std::setfill('0') << datetime_part(dt, datetime_part_t::day);
		os << " " << std::setw(2) << std::setfill('0') << datetime_part(dt, datetime_part_t::hour);
		int min = datetime_part(dt, datetime_part_t::minute);
		if (min > 0)
		{
			os << ":" << std::setw(2) << std::setfill('0') << min;
			int sec = datetime_part(dt, datetime_part_t::second);
			if (sec > 0)
			{
				os << ":" << std::setw(2) << std::setfill('0') << sec;
				int msecs = datetime_part(dt, datetime_part_t::microsecs);
				if (msecs > 0)
				{
					os << "." << msecs;
				}
			}
		}
		return os;
	}

	inline std::istream& operator>>(std::istream& is, datetime_t& dt) noexcept
	{
		int year, month, day, hour = 0, min = 0, sec = 0, msecs = 0;
		skip_spaces(is);
		if (datetime::get_date(is, year, month, day))
		{
			datetime::get_time(is, hour, min, sec, msecs);
			dt = make_datetime(year, month, day, hour, min, sec, msecs);
		}
		return is;
	}

} // namespace tucan

namespace std {

	inline std::string to_string(const tucan::datetime_t& dt, char separator = ' ')
	{
		std::ostringstream os(std::move(std::ostringstream() << dt));
		std::string str = os.str();
		size_t index = str.find(' ');
		if (index != std::string::npos)
		{
			str[index] = separator;
		}
		return str;
	}
}

namespace tucan
{
	inline datetime_t make_datetime(const std::string& str)
	{
		datetime_t dt;
		if (validate_datetime(str))
		{
			std::istringstream is(str);
			is >> dt;
		}
		return dt;
	}

}