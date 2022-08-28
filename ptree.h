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
      ptree::opcode_t opcode_;
      token_t token_;
      value_t value_;
      ptree_t* left_;
      ptree_t* right_;
      parser_t* parser_;

      // keep track of all "allocated" ptree_t objects
      inline static std::vector<ptree_t> ptree_;

   public:
      ptree_t() noexcept
         : opcode_(ptree::noop)
         , token_()
         , value_()
         , left_(nullptr)
         , right_(nullptr)
         , parser_(nullptr)
      {
         ptree_.push_back(*this);
      }

      ptree_t(parser_t* parser, ptree::opcode_t opcode, const token_t& token, const value_t& value, ptree_t* left = nullptr, ptree_t* right = nullptr) noexcept
         : opcode_(opcode)
         , token_(token)
         , value_(value)
         , left_(left)
         , right_(right)
         , parser_(parser)
      {
         ptree_.push_back(*this);
      }

      ~ptree_t() = default;
      ptree_t(const ptree_t&) = default;
      ptree_t(ptree_t&&) = default;
      ptree_t& operator=(const ptree_t&) = default;
      ptree_t& operator=(ptree_t&&) = default;

      ptree::opcode_t opcode() const noexcept
      {
         return opcode_;
      }

      void opcode(const ptree::opcode_t& op) noexcept
      {
         opcode_ = op;
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

      type_t type() const noexcept
      {
         return value().type();
      }

      parser_t* parser() noexcept
      {
         return parser_;
      }

      void type(type_t t)
      {
         switch (t)
         {
         case type_t::null: value_ = value_t(); break;
         case type_t::integer: value_ = value_t(0ll); break;
         case type_t::decimal: value_ = value_t(decimal_t()); break;
         case type_t::datetime: value_ = value_t(datetime_t()); break;
         case type_t::text: value_ = value_t(text_t()); break;
         case type_t::binary: value_ = value_t(binary_t()); break;
         default: value_ = value_t(); break;
         }
      }

      ptree_t* left() noexcept
      {
         return left_;
      }

      void left(ptree_t* l)
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

      // return a pointer to the last ptree_t object 
      // used only by make_ptree
      static ptree_t* last() noexcept
      {
         size_t size = ptree_.size();
         if (size > 0)
         {
            return &ptree_[size - 1];
         }
         return nullptr;
      }

      // only call this once to clear all "allocated" ptree_t objects
      // and after the parser is no longer needed
      static void clear() noexcept
      {
         ptree_.clear();
      }
   };

   // alwyas use make_ptree to create pointers to ptree_t object. 
   // avoid using ptree_t constructors directly
   inline ptree_t* make_ptree(parser_t* parser, ptree::opcode_t opcode, const token_t& token, const value_t& value, ptree_t* left = nullptr, ptree_t* right = nullptr) noexcept
   {
      ptree_t pt(parser, opcode, token, value, left, right);
      return ptree_t::last();
   }

   inline ptree_t* make_ptree(parser_t* parser, ptree::opcode_t opcode, const token_t* token, const value_t& value, ptree_t* left = nullptr, ptree_t* right = nullptr) noexcept
   {
      if (token)
      {
         return make_ptree(parser, opcode, *token, value, left, right);
      }
      return nullptr;
   }


} // namespace tucan
