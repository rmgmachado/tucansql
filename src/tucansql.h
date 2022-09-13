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

#include <map>

#include "memdb.h"
#include "sqlparser.h"

namespace tucan {

   namespace sql {
      size_t npos = -1;
   }

   using sqlid_t = size_t;


   inline bool execute_tree(ptree_t* tree) noexcept;

   class sql_t
   {
      database_t db_;
      std::map<sqlid_t, parser_t> parsers_;
      int error_;
      text_t errmsg_;
      sqlid_t id_;

   public:
      sql_t() noexcept
         : db_()
         , parsers_()
         , error_(status::ok)
         , errmsg_("")
         , id_(0)
      {}

      ~sql_t() = default;
      sql_t(const sql_t&) = delete;
      sql_t(sql_t&&) = default;
      sql_t& operator=(const sql_t&) = delete;
      sql_t& operator=(sql_t&&) = default;

      void set_error(int errcode, const text_t& errmsg) noexcept
      {
         error_ = errcode;
         errmsg_ = errmsg;
      }

      int get_error() const noexcept
      {
         return error_;
      }

      text_t get_error_message() const noexcept
      {
         return errmsg_;
      }

      database_t& database() noexcept
      {
         return db_;
      }

      sqlid_t prepare(const std::string& stmt) noexcept
      {
         error_ = 0;
         errmsg_ = "No errors detected";
         const auto [it, success] = parsers_.insert({id_, parser_t()});
         if (success)
         {
            sqlid_t id = id_++;
            if (parsers_[id].run(&db_, stmt)) return id;
            set_error(parsers_[id].get_error_code(), parsers_[id].get_error_message());
         }
         return sql::npos;
      }

      status_t execute(const sqlid_t& id) noexcept
      {
         if (id != sql::npos)
         {
            if (execute_tree(parsers_[id].get_tree())) return status::ok;
            return parsers_[id].get_error_code();
         }
         return status::invalid_handle;
      }

      status_t next(const sqlid_t& id) noexcept
      {
         return status::ok;
      }

      status_t reset(const sqlid_t& id) noexcept
      {
         return status::ok;
      }

      status_t finalize(const sqlid_t& id) noexcept
      {
         auto it = parsers_.find(id);
         if (it != parsers_.end())
         {
            parsers_.erase(it);
            return status::ok;
         }
         return status::invalid_handle;
      }

      count_t rows_afftected() const noexcept
      {
         return 0;
      }

      count_t column_count() const noexcept
      {
         return 0;
      }

      colid_t column_index(const name_t& column_name) const noexcept
      {
         return memdb::npos;
      }

      name_t column_name(colid_t id) const noexcept
      {
         return "";
      }

      type_t column_type(colid_t id) const noexcept
      {
         return type_t::null;
      }

      bool is_column_null(colid_t id) const noexcept
      {
         return true;
      }

      value_t& column_value(colid_t) const noexcept
      {
         static value_t val;
         return val;
      }

      std::string column_value_as_string(colid_t id) const noexcept
      {
         return "";
      }

      count_t column_width(colid_t id) const noexcept
      {
         return 0;
      }
   };

   namespace runtime
   {
      parser_t& parser(ptree_t* tree) noexcept
      {
         return *tree->parser();
      }

      stack_t& stack(ptree_t* tree) noexcept
      {
         return parser(tree).stack();
      }

      database_t& database(ptree_t* tree) noexcept
      {
         return parser(tree).database();
      }

      inline bool execute_field_def(ptree_t* tree) noexcept
      {
         stack(tree).push_back(value_t(tree->token().text()));
         stack(tree).push_back(tree->value());
         return true;
      }

      inline bool execute_create_table(ptree_t* tree) noexcept
      {
         text_t tblname = tree->token().text();
         status_t status = database(tree).create_table(tblname);
         if (status == status_t::ok)
         {
            table_t& tbl = database(tree).get_table(tblname);
            while (!stack(tree).empty())
            {
               text_t colname = get_value<text_t>(stack(tree).pop());
               value_t coltype = stack(tree).pop();

               status = tbl.add_column(colname, coltype.type());
               if (status != status_t::ok)
               {
                  parser(tree).set_error(status::table_create_error, std::string("error adding field: " + colname).c_str());
                  return false;
               }
            }
         }
         if (status == status_t::invalid_name)
         {
            parser(tree).set_error(status::table_create_error, std::string("invalid table name: " + tblname).c_str());
            return false;
         }
         if (status == status_t::duplicate)
         {
            parser(tree).set_error(status::table_create_error, std::string("table already created: " + tblname).c_str());
            return false;
         }
         return true;
      }

      inline static std::array<std::function<bool(ptree_t*)>, 40> execute_dispatch_table =
      {
         /* noop 				*/   [](ptree_t* tree) -> bool { return true; }
         /* push_field 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* push_table 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* push_literal 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* minus 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* plus 				*/ , [](ptree_t* tree) -> bool { return true; }
         /* negate 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* multiply 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* divide 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* add 				*/ , [](ptree_t* tree) -> bool { return true; }
         /* subtract 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* equal 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* not_equal 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* less 				*/ , [](ptree_t* tree) -> bool { return true; }
         /* less_equal 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* greater 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* greater_equal 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* is_null 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* is_not_null 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* logical_or 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* logical_and 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* expr 				*/ , [](ptree_t* tree) -> bool { return true; }
         /* where 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* where_true 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* assign_list 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* assign 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* field_def 		*/ , [](ptree_t* tree) -> bool { return execute_field_def(tree); }
         /* field_name 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* create_table 	*/ , [](ptree_t* tree) -> bool { return execute_create_table(tree); }
         /* insert 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* insert_names	*/ , [](ptree_t* tree) -> bool { return true; }
         /* insert_values 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* update 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* update_set 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* drop_table 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* delete_row 		*/ , [](ptree_t* tree) -> bool { return true; }
         /* select 			*/ , [](ptree_t* tree) -> bool { return true; }
         /* select_where 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* select_from 	*/ , [](ptree_t* tree) -> bool { return true; }
         /* field_all 		*/ , [](ptree_t* tree) -> bool { return true; }
      };

      inline bool execute(ptree_t* tree) noexcept
      {
         if (!tree) return true;
         if (execute(tree->left()) && execute(tree->right()))
         {
            return runtime::execute_dispatch_table[tree->opcode()](tree);
         }
         return false;
      }

   } // namespace runtime

   inline bool execute_tree(ptree_t* tree) noexcept
   {
      if (!tree) return false;
      if (!tree->parser()) return false;
      tree->parser()->clear_execution();
      return runtime::execute(tree);
   }



} // namespace tucan
