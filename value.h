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

#include <string>
#include <vector>
#include <any>
#include <iostream>
#include <utility>
#include <algorithm>
#include <type_traits>

#include "system.h"
#include "datetime.h"
#include "decimal.h"
#include "base64.h"

namespace tucan {

   enum class opcode_t { null, boolean, integer, decimal, datetime, text, binary };

   using integer_t = long long int;
   using text_t = std::string;
   using binary_t = std::vector<byte_t>;

   class value_t
   {
      std::any value_;

   public:
      value_t() = default;
      ~value_t() = default;
      value_t(const value_t&) = default;
      value_t(value_t&&) = default;
      value_t& operator=(const value_t&) = default;
      value_t& operator=(value_t&&) = default;

      explicit value_t(bool value) noexcept
         : value_(value)
      {}

      explicit value_t(float value) noexcept
         : value_(decimal_t(static_cast<double>(value)))
      {}

      explicit value_t(double value) noexcept
         : value_(decimal_t(value))
      {}

      explicit value_t(const decimal_t& value) noexcept
         : value_(value)
      {}

      explicit value_t(const datetime_t& value) noexcept
         : value_(value)
      {}

      explicit value_t(const char* value) noexcept
         : value_(std::string(value))
      {}

      explicit value_t(const text_t& value) noexcept
         : value_(value)
      {}

      explicit value_t(const binary_t& value) noexcept
         : value_(value)
      {}

      template <typename T>
      explicit value_t(const T& value) noexcept
         : value_(static_cast<integer_t>(value))
      {}

      value_t& operator=(bool value) noexcept
      {
         value_.emplace<bool>(value);
         return *this;
      }

      value_t& operator=(float value) noexcept
      {
         value_.emplace <decimal_t>(decimal_t(static_cast<double>(value)));
         return *this;
      }

      value_t& operator=(double value) noexcept
      {
         value_.emplace<decimal_t>(decimal_t(value));
         return *this;
      }

      value_t& operator=(const decimal_t& value) noexcept
      {
         value_.emplace <decimal_t>(value);
         return *this;
      }

      value_t& operator=(const datetime_t& value) noexcept
      {
         value_.emplace <datetime_t>(value);
         return *this;
      }

      value_t& operator=(const char* value) noexcept
      {
         value_.emplace <text_t>(std::string(value));
         return *this;
      }

      value_t& operator=(const text_t& value) noexcept
      {
         value_.emplace <text_t>(value);
         return *this;
      }

      value_t& operator=(const binary_t& value) noexcept
      {
         value_.emplace <binary_t>(value);
         return *this;
      }

      template <typename T>
      value_t& operator=(const T& value) noexcept
      {
         value_.emplace<integer_t>(static_cast<integer_t>(value));
         return *this;
      }

      opcode_t type() const noexcept
      {
         if (!value_.has_value()) return opcode_t::null;
         if (value_.type() == typeid(bool)) return opcode_t::boolean;
         if (value_.type() == typeid(integer_t)) return opcode_t::integer;
         if (value_.type() == typeid(decimal_t)) return opcode_t::decimal;
         if (value_.type() == typeid(datetime_t)) return opcode_t::datetime;
         if (value_.type() == typeid(text_t)) return opcode_t::text;
         if (value_.type() == typeid(binary_t)) return opcode_t::binary;
         return opcode_t::null;
      }

      bool is_null() const noexcept
      {
         return !value_.has_value();
      }

      const std::any& get() const noexcept
      {
         return value_;
      }
   };

   inline value_t make_value() noexcept
   {
      return value_t();
   }

   template <typename T>
   inline value_t make_value(const T& value) noexcept
   {
      return value_t(value);
   }

   template <typename T>
   inline void get_value(const value_t& value, T& out) noexcept
   {
      switch (value.type())
      {
      case opcode_t::boolean: out = std::any_cast<bool>(value.get()) ? 1 : 0; break;
      case opcode_t::integer: out = std::any_cast<integer_t>(value.get()); break;
      case opcode_t::decimal: out = static_cast<integer_t>(std::any_cast<decimal_t>(value.get())); break;
      default: out = T(); break;
      }
   }

   inline void get_value(const value_t& value, text_t& out) noexcept
   {
      switch (value.type())
      {
      case opcode_t::boolean: out = (std::any_cast<bool>(value.get()) ? "true" : "false"); break;
      case opcode_t::integer: out = std::to_string(std::any_cast<integer_t>(value.get())); break;
      case opcode_t::decimal: out = std::to_string(std::any_cast<decimal_t>(value.get())); break;
      case opcode_t::datetime: out = std::to_string(std::any_cast<datetime_t>(value.get())); break;
      case opcode_t::text: out = std::any_cast<text_t>(value.get()); break;
      case opcode_t::binary: out = encode(std::any_cast<binary_t>(value.get())); break;
      default: out = "null";  break;
      }
   }

   inline void get_value(const value_t& value, binary_t& out) noexcept
   {
      switch (value.type())
      {
      case opcode_t::binary: out = std::any_cast<binary_t>(value.get()); break;
      default: out = binary_t(); break;
      }
   }

   inline void get_value(const value_t& value, datetime_t& out) noexcept
   {
      switch (value.type())
      {
      case opcode_t::datetime: out = std::any_cast<datetime_t>(value.get()); break;
      default: out = datetime_t(); break;
      }
   }

   inline void get_value(const value_t& value, decimal_t& out) noexcept
   {
      switch (value.type())
      {
      case opcode_t::boolean: out = decimal_t(std::any_cast<bool>(value.get()) ? 1ll : 0ll); break;
      case opcode_t::integer: out = decimal_t(std::any_cast<integer_t>(value.get())); break;
      case opcode_t::decimal: out = std::any_cast<decimal_t>(value.get()); break;
      default: out = decimal_t(0ll); break;
      }
   }

   inline void get_value(const value_t& value, bool& out) noexcept
   {
      switch (value.type())
      {
      case opcode_t::boolean: out = std::any_cast<bool>(value.get()); break;
      case opcode_t::integer: out = std::any_cast<integer_t>(value.get()) == 0 ? false : true; break;
      case opcode_t::decimal: out = std::any_cast<decimal_t>(value.get()) == decimal_t() ? false : true; break;
      default: out = false; break;
      }
   }

   template <typename T>
   inline T get_value(const value_t& value) noexcept
   {
      T temp;
      get_value(value, temp);
      return temp;
   }

} // namespace tucan