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

#include <stack>

#include "value.h"

namespace tucan {

   class stack_t
   {
      std::stack<value_t> stack_;

   public:
      stack_t() = default;
      ~stack_t() = default;
      stack_t(const stack_t&) = default;
      stack_t(stack_t&&) = default;
      stack_t& operator=(const stack_t&) = default;
      stack_t& operator=(stack_t&&) = default;

      void push(const value_t& value) noexcept
      {
         stack_.push(value);
      }

      value_t top() const noexcept
      {
         if (!stack_.empty())
         {
            return stack_.top();
         }
         return value_t();
      }

      value_t pop() noexcept
      {
         if (!stack_.empty())
         {
            value_t value = stack_.top();
            stack_.pop();
            return value;
         }
         return value_t();
      }

      bool empty() const noexcept
      {
         return stack_.empty();
      }

      size_t size() const noexcept
      {
         return stack_.size();
      }

      void clear() noexcept
      {
         while (!stack_.empty())
         {
            stack_.pop();
         }
      }
   };

} // namespace tucan