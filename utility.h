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
#include <sstream>
#include <iomanip>
#include <regex>
#include <algorithm>
#include <string>
#include <cctype>

namespace tucan {

	inline void removeTrailingCharacters(std::string &str, const char charToRemove) noexcept
	{
	    str.erase (str.find_last_not_of(charToRemove) + 1, std::string::npos );
	}
	
	inline void removeLeadingCharacters(std::string &str, const char charToRemove) noexcept
	{
	    str.erase(0, std::min(str.find_first_not_of(charToRemove), str.size() - 1));
	}
	
	inline void skip_spaces(std::istream& is) noexcept
	{
		while (!is.eof() && std::isspace(is.peek()))
		{
			is.get();
		}
	}

	inline bool get_separator(std::istream& is, char separator) noexcept
	{
		if (!is.eof() && is.peek() == separator)
		{
			is.get();
			return true;
		}
		return false;
	}

	inline size_t get_digits(std::istream& is, int64_t& value) noexcept
	{
		size_t count = 0;
		value = 0;
		while (!is.eof() && std::isdigit(is.peek()))
		{
			value = (value * 10ll) + (is.get() - '0');
			++count;
		}
		return count;
	}

	template <typename T>
	inline size_t get_digits(std::istream& is, T& value, unsigned int digits) noexcept
	{
		size_t count = 0;
		value = 0;
		while (!is.eof() && std::isdigit(is.peek()))
		{
			if (count == digits) break;
			value = (value * 10ll) + (is.get() - '0');
			++count;
		}
		return count;
	}

	inline bool validate(const std::string& text, const std::string& regx) noexcept
	{
		return std::regex_match(text, std::regex(regx));
	}

	inline bool validate_decimal(const std::string& text) noexcept
	{
		return validate(text, "-?\\d+(\\.\\d+)?");
	}

	inline bool validate_datetime(const std::string& text) noexcept
	{
		return validate(text, "(\\d{4})-(\\d{2})-(\\d{2})([ T](\\d{2})(:(\\d{2})(:(\\d{2})(\\.(\\d{1,6}))?)?)?)?");
	}

	inline bool compare(const std::string& lhs, const std::string& rhs)
	{
		return (lhs.size() == rhs.size() && 
			     std::equal(lhs.begin(), lhs.end(), rhs.begin(), 
				[](const char& c1, const char& c2) {	return (c1 == c2 || std::toupper(c1) == std::toupper(c2));
			     }));
	}

} // namespace tucan
