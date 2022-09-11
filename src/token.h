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

#include <regex>
#include <algorithm>
#include <string>
#include <memory>
#include <cctype>

#include "system.h"
#include "utility.h"


namespace tucan {

   namespace token {
      enum id_t : int { eof = 0, unknown = 256, identifier, decimal, datetime, text, name, ne, le, ge };
   }

   class token_t
   {
      int id_;
      std::string token_;
      unsigned int line_;
      unsigned int column_;

   public:
      ~token_t() = default;
      token_t(const token_t&) = default;
      token_t(token_t&&) = default;
      token_t& operator=(const token_t&) = default;
      token_t& operator=(token_t&&) = default;

      token_t()
         : id_(0)
         , token_()
         , line_(0)
         , column_(0)
      {}

      token_t(const std::string& token, int id, unsigned int line = 0, unsigned int column = 0) noexcept
         : id_(id)
         , token_(token)
         , line_(line)
         , column_(column)
      {}

      int id() const noexcept
      {
         return id_;
      }

      void id(int i)
      {
         id_ = i;
      }

      std::string text() const noexcept
      {
         return token_;
      }

      unsigned int line() const noexcept
      {
         return line_;
      }

      unsigned int column() const noexcept
      {
         return column_;
      }
   };

} // namespace tucan

