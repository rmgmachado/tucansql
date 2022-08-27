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

      void id(token::id_t i)
      {
         id_ = i;
      }

      std::string token() const noexcept
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

   class scanner_t
   {
      std::vector<token_t> tokens_;
      std::vector<token_t>::iterator current_;
      std::string text_;
      unsigned int line_;
      unsigned int column_;
      std::string::const_iterator pos_;


   public:
      ~scanner_t() = default;
      scanner_t(const scanner_t&) = delete;
      scanner_t(scanner_t&&) = delete;
      scanner_t& operator=(const scanner_t&) = delete;
      scanner_t& operator=(scanner_t&&) = delete;

      scanner_t() noexcept
         : text_()
         , tokens_()
         , line_(1)
         , column_(1)
      {
         current_ = tokens_.begin();
         pos_ = text_.cbegin();
      }

      scanner_t(const std::string& text) noexcept
         : text_(text)
         , tokens_()
         , line_(1)
         , column_(1)
      {
         pos_ = text_.cbegin();
         scan();
         current_ = tokens_.begin();
      }

      int next(token_t& token) noexcept
      {
         if (current_ != tokens_.end())
         {
            token = *current_++;
            return token.id();
         }
         return token::id_t::eof;
      }

      void rewind() noexcept
      {
         current_ = tokens_.begin();
      }

   private:
      void scan() noexcept
      {
         while (peek() != token::eof)
         {
            // the order of processing is important, please don't change
            skip_spaces();
            if (is_text()) continue;
            if (is_name()) continue;
            if (is_identifier()) continue;
            if (is_datetime()) continue;
            if (is_decimal()) continue;
            scan_symbol();
         }
      }

      bool is_identifier() noexcept
      {
         if (std::isalpha(*pos_) || *pos_ == '_')
         {
            return add_token("([a-zA-Z_][a-zA-Z0-9_]*)[\\s\\S]*", token::identifier);
         }

         return false;
      }

      bool is_decimal() noexcept
      {
         if (std::isdigit(*pos_))
         {
            return add_token("([0-9]+(\\.[0-9]+)?)[\\s\\S]*", token::decimal);
         }
         return false;
      }

      bool is_datetime() noexcept
      {
         if (std::isdigit(*pos_))
         {
            return add_token("((\\d{4})-(\\d{2})-(\\d{2})([ T](\\d{2})(:(\\d{2})(:(\\d{2})(\\.(\\d{1,6}))?)?)?)?)[\\s\\S]*", token::datetime);
         }
      }

      bool is_text() noexcept
      {
         if (*pos_ == '\'')
         {
            return is_text_or_name(*pos_);
         }
         return false;
      }

      bool is_name() noexcept
      {
         if (*pos_ == '"')
         {
            return is_text_or_name(*pos_);
         }
         return false;
      }

      bool is_text_or_name(char quote) noexcept
      {
         if (quote == '\'' || quote == '"')
         {
            std::string matched;
            unsigned int col = column_;
            int id = quote == '"' ? token::name : token::text;
            if (match_quoted(quote, matched))
            {
               tokens_.push_back(token_t(matched, id, line_, col));
               return true;
            }
         }
         return false;
      }

      bool scan_symbol() noexcept
      {
         std::string matched = "";
         unsigned int col = column_;
         char ch = get();
         int id = ch;

         matched += ch;
         if (ch == '<' && peek() == '>')
         {
            matched += get();
            id = token::ne;
         }
         else if (ch == '<' && peek() == '=')
         {
            matched += get();
            id = token::le;
         }
         else if (ch == '>' && peek() == '=')
         {
            matched += get();
            id = token::ge;
         }
         tokens_.push_back(token_t(matched, id, line_, col));
         return true;
      }

      bool add_token(const std::string& expr, token::id_t id) noexcept
      {
         std::string matched;
         if (match(expr, matched))
         {
            tokens_.push_back(token_t(matched, id, line_, column_));
            column_ += static_cast<unsigned int>(matched.length());
            pos_ += matched.length();
            return true;
         }
         return false;
      }

      bool match(const std::string& expr, std::string& matched)
      {
         std::smatch sm;
         std::regex reg(expr);
         try
         {
            matched = "";
            if (std::regex_match(pos_, text_.cend(), sm, reg))
            {
               if (sm.size() > 0)
               {
                  matched = sm[1];
               }
               return true;
            }
         }
         catch (std::regex_error&)
         {
            return false;
         }
         return false;
      }

      bool match_quoted(char quote, std::string& matched)
      {
         matched = "";
         auto saved = pos_;
         char ch = peek();

         if (ch == quote)
         {
            get();
            while (true)
            {
               ch = get();
               if (ch == quote && peek() == quote)
               {
                  get();
                  matched += quote;
                  continue;
               }
               if (ch == quote) return true;
               matched += ch;
            }
            pos_ = saved;
         }
         return false;
      }

      void skip_spaces() noexcept
      {
         while (std::isspace(peek()))
         {
            get();
         }
      }

      char peek() noexcept
      {
         char ch = '\0';
         if (pos_ != text_.cend())
         {
            ch = *pos_;
         }
         return ch;
      }

      char get() noexcept
      {
         char ch = '\0';
         if (pos_ != text_.cend())
         {
            ch = *pos_;
            ++pos_;
            ++column_;
            if (ch == '\n')
            {
               ++line_;
               column_ = 1;
            }
         }
         return ch;
      }

   };

} // namespace tucan

