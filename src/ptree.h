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

#include "value.h"
#include "scanner.h"

namespace tucan {

   namespace ptree {
      enum opcode_t : int {
           noop = 0     // no operation
         , push_field
         , push_table
         , push_literal
         , minus        // eg -1
         , plus         // eg +1
         , negate       // eg NOT true
         , multiply
         , divide
         , add
         , subtract
         , equal
         , not_equal
         , less
         , less_equal
         , greater
         , greater_equal
         , is_null
         , is_not_null
         , logical_or
         , logical_and
         , expr
         , where
         , where_true
         , assign_list
         , assign
         , field_def
         , field_def_list
         , field_name
         , create_table
         , insert
         , insert_values
         , update
         , update_set
         , drop_table
         , delete_row
         , select
         , select_where
         , select_from
         , field_all
      };
   }

   class parser_t;

   class ptree_t
   {
   public:
      int opcode_;
      token_t token_;
      value_t value_;
      parser_t* parser_;
      ptree_t* left_;
      ptree_t* right_;

      ~ptree_t() = default;
      ptree_t(const ptree_t&) = default;
      ptree_t(ptree_t&&) = default;
      ptree_t& operator=(const ptree_t&) = default;
      ptree_t& operator=(ptree_t&&) = default;

      ptree_t()
         : opcode_(ptree::noop)
         , token_()
         , value_()
         , parser_(nullptr)
         , left_(nullptr)
         , right_(nullptr)
      {}

      ptree_t(parser_t* parser, int opcode, const token_t& token, const value_t& value, ptree_t* left, ptree_t* right)
         : opcode_(opcode)
         , token_(token)
         , value_(value)
         , parser_(parser)
         , left_(left)
         , right_(right)
      {}

      int opcode() const noexcept
      {
         return opcode_;
      }

      token_t token() const noexcept
      {
         return token_;
      }

      void token(const token_t& tok) noexcept
      {
         token_ = tok;
      }

      value_t value() const noexcept
      {
         return value_;
      }

      void value(const value_t& val) noexcept
      {
         value_ = val;
      }

      parser_t* parser() noexcept
      {
         return parser_;
      }

      ptree_t* left() noexcept
      {
         return left_;
      }

      void left(ptree_t* l) noexcept
      {
         left_ = l;
      }

      ptree_t* right() noexcept
      {
         return right_;
      }

      void right(ptree_t* r) noexcept
      {
         right_ = r;
      }
   };

} // namespace tucan
