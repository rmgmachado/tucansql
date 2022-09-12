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
#include "status.h"

namespace tucan {

	using name_t = std::string;
	using rowid_t = unsigned int;
	using colid_t = unsigned int;
	using tableid_t = unsigned int;
	using row_t = std::vector<value_t>;

	namespace memdb {
		constexpr unsigned int npos = 0xffffffff;
	}

	struct column_t
	{
		name_t name;
		type_t type;
		count_t width;

		column_t(const name_t& n = "", type_t t = type_t::boolean)
			: name(n)
			, type(t)
			, width(n.length())
		{}

		~column_t() = default;
	};

	class record_t
	{
		std::vector<column_t> columns_;
		std::vector<row_t> rows_;
		column_t temp_column_;

	public:
		record_t() = default;
		~record_t() = default;
		record_t(const record_t&) = default;
		record_t(record_t&&) = default;
		record_t& operator=(const record_t&) = default;
		record_t& operator=(record_t&&) = default;

		void clear() noexcept
		{
			columns_.clear();
			rows_.clear();
		}

		count_t column_count() const noexcept
		{
			return columns_.size();
		}

		count_t row_count() const noexcept
		{
			return rows_.size();
		}

		colid_t find_column(const name_t& name) const noexcept
		{
			colid_t colid = 0;
			for (auto& column : columns_)
			{
				if (compare(name, column.name))
				{
					return colid;
				}
				++colid;
			}
			return memdb::npos;
		}

		column_t& get_column(colid_t colid) noexcept
		{
			return (colid < column_count()) ? columns_[colid] : temp_column_;
		}

		column_t& get_column(const name_t& name) noexcept
		{
			return get_column(find_column(name));
		}

		status_t add_column(const name_t& name, type_t type) noexcept
		{
			if (!validate(name, "[a-zA-Z][a-zA-Z0-9_]*")) return status::invalid_name;
			if (find_column(name) != memdb::npos) return status::duplicate;
			columns_.push_back(column_t(name, type));
			if (row_count() > 0)
			{
				for (auto& row : rows_)
				{
					row.push_back(value_t());
				}
			}
			return status::ok;
		}

		status_t delete_column(colid_t colid) noexcept
		{
			if (colid >= column_count()) return status::not_found;
			auto cptr = columns_.begin();
			std::advance(cptr, colid);
			columns_.erase(cptr);
			if (row_count() > 0)
			{
				for (auto& row : rows_)
				{
					row_t::iterator rptr = row.begin();
					std::advance(rptr, colid);
					row.erase(rptr);
				}
			}
			return status::ok;
		}

		status_t get_row(rowid_t rowid, row_t& row) const noexcept
		{
			if (rowid >= row_count()) return status::not_found;
			row = rows_[rowid];
			return status::ok;
		}

		rowid_t add_row() noexcept
		{
			if (column_count() == 0) return memdb::npos;
			rows_.push_back(row_t(row_t::size_type(column_count())));
			return rowid_t(row_count() - 1);
		}

		status_t delete_row(rowid_t rowid) noexcept
		{
			if (row_count() == 0) return status::empty;
			if (rowid >= row_count()) return status::not_found;
			auto ptr = rows_.begin();
			std::advance(ptr, rowid);
			rows_.erase(ptr);
			return status::ok;
		}

		bool is_column_null(rowid_t rowid, colid_t colid) const noexcept
		{
			if (rowid >= row_count() || colid >= column_count()) return true;
			return rows_[rowid][colid].is_null();
		}

		value_t read_column(rowid_t rowid, colid_t colid) const noexcept
		{
			if (rowid >= row_count() || colid >= column_count()) return value_t();
			return rows_[rowid][colid];
		}

		text_t read_column_as_string(rowid_t rowid, colid_t colid) const noexcept
		{
			if (rowid >= row_count() || colid >= column_count()) return "";
			return get_value<std::string>(rows_[rowid][colid]);
		}


		status_t write_column_integer(rowid_t rowid, colid_t colid, const value_t& value) noexcept
		{
			if (value.type() == type_t::integer)
			{
				rows_[rowid][colid] = value;
				return status::ok;
			}
			if (value.type() == type_t::decimal)
			{
				rows_[rowid][colid] = value_t(get_value<integer_t>(value));
				return status::ok;
			}
			return status::invalid_type;
		}

		status_t write_column_decimal(rowid_t rowid, colid_t colid, const value_t& value) noexcept
		{
			if (value.type() == type_t::decimal)
			{
				rows_[rowid][colid] = value;
				return status::ok;
			}
			if (value.type() == type_t::integer)
			{
				rows_[rowid][colid] = value_t(get_value<decimal_t>(value));
				return status::ok;
			}
			return status::invalid_type;
		}

		status_t write_column(rowid_t rowid, colid_t colid, const value_t& value) noexcept
		{
			if (rowid >= row_count() || colid >= column_count()) return status::not_found;
			if (!value.is_null())
			{
				type_t type = get_column(colid).type;
				if (type == type_t::integer) return write_column_integer(rowid, colid, value);
				if (type == type_t::decimal) return write_column_decimal(rowid, colid, value);
				if (type != value.type())  return status::invalid_type;
			}
			rows_[rowid][colid] = value;
			return status::ok;
		}

		status_t calculate_width() noexcept
		{
			for (colid_t colid = 0; colid < column_count(); ++colid)
			{
				column_t& column(get_column(colid));
				column.width = column.name.length();
				for (rowid_t rowid = 0; rowid < row_count(); ++rowid)
				{
					count_t width = read_column_as_string(rowid, colid).length();
					column.width = (width > column.width) ? width : column.width;
				}
			}
			return status::ok;
		}

	};

	class cursor_t
	{
		record_t& record_;
		rowid_t rowid_;

	public:
		cursor_t() = delete;
		~cursor_t() = default;
		cursor_t(const cursor_t&) = delete;
		cursor_t(cursor_t&&) = default;
		cursor_t& operator=(const cursor_t&) = delete;
		cursor_t& operator=(cursor_t&&) = default;

		explicit cursor_t(record_t& record) noexcept
			: record_(record)
			, rowid_(0)
		{}

		void clear()
		{
			rowid_ = 0;
			record_.clear();
		}

		rowid_t rowid() const noexcept
		{
			return rowid_;
		}

		count_t column_count() const noexcept
		{
			return record_.column_count();
		}

		type_t get_column_type(colid_t colid) const noexcept
		{
			return record_.get_column(colid).type;
		}

		name_t get_column_name(colid_t colid) const noexcept
		{
			return record_.get_column(colid).name;
		}

		count_t row_count() const noexcept
		{
			return record_.row_count();
		}

		colid_t find_column(const name_t& name) const noexcept
		{
			return record_.find_column(name);
		}

		column_t& get_column(const name_t& name) noexcept
		{
			return record_.get_column(name);
		}

		column_t& get_column(colid_t colid) noexcept
		{
			return record_.get_column(colid);
		}

		status_t add_column(const name_t& name, type_t type) noexcept
		{
			return record_.add_column(name, type);
		}

		status_t delete_column(colid_t colid) noexcept
		{
			return record_.delete_column(colid);
		}

		status_t read_row(row_t& row) const noexcept
		{
			return record_.get_row(rowid_, row);
		}

		rowid_t add_row() noexcept
		{
			return record_.add_row();
		}

		status_t delete_row()
		{
			status_t res = record_.delete_row(rowid_);
			if (res == status::ok)
			{
				rowid_ = static_cast<rowid_t>((rowid_ >= row_count()) ? (row_count() - 1) : rowid_);
			}
			return res;
		}

		value_t read_column(colid_t colid) const noexcept
		{
			return record_.read_column(rowid_, colid);
		}

		bool is_column_null(colid_t colid) const noexcept
		{
			return record_.is_column_null(rowid_, colid);
		}

		text_t read_column_as_string(colid_t colid) const noexcept
		{
			return record_.read_column_as_string(rowid_, colid);
		}

		status_t write_column(colid_t colid, const value_t& value) noexcept
		{
			return record_.write_column(rowid_, colid, value);
		}

		status_t goto_row(rowid_t rowid) noexcept
		{
			if (rowid >= row_count()) return status::not_found;
			rowid_ = rowid;
			return status::ok;
		}

		status_t first_row() noexcept
		{
			rowid_ = 0;
			return ((rowid_ < row_count()) ? status::ok : status::not_found);

		}

		status_t last_row() noexcept
		{
			rowid_ = 0;
			if (row_count() == 0) return status::not_found;
			rowid_ = rowid_t(row_count() - 1);
			return status::ok;
		}

		status_t next_row() noexcept
		{
			if ((rowid_ + 1) >= row_count()) return status::not_found;
			++rowid_;
			return status::ok;
		}

		status_t prior_row() noexcept
		{
			if (rowid_ == 0 || row_count() == 0 || rowid_ >= row_count()) return status::not_found;
			--rowid_;
			return status::ok;
		}
	};

	class table_t
	{
		name_t name_;
		record_t record_;

	public:
		table_t() = default;
		~table_t() = default;
		table_t(const table_t&) = delete;
		table_t(table_t&&) = default;
		table_t& operator=(const table_t&) = delete;
		table_t& operator=(table_t&&) = default;

		explicit table_t(const name_t& name)
			: name_(name)
			, record_()
		{}

		name_t name() const noexcept
		{
			return name_;
		}

		void name(const name_t& name) noexcept
		{
			name_ = name;
		}

		cursor_t get_cursor() noexcept
		{
			return cursor_t(record_);
		}

		count_t column_count() const noexcept
		{
			return record_.column_count();
		}

		count_t row_count() const noexcept
		{
			return record_.row_count();
		}

		status_t add_column(const name_t& name, type_t type) noexcept
		{
			return record_.add_column(name, type);
		}

		void clear() noexcept
		{
			name_ = "";
			record_.clear();
		}
	};

	class database_t
	{
		std::vector<std::pair<name_t, table_t>> tables_;
		table_t temp_table_;

	public:
		database_t() = default;
		~database_t() = default;
		database_t(const database_t&) = delete;
		database_t(database_t&&) = default;
		database_t& operator=(const database_t&) = delete;
		database_t& operator=(database_t&&) = default;

		count_t table_count() const noexcept
		{
			return tables_.size();
		}

		status_t create_table(const name_t& name) noexcept
		{
			if (!validate(name, "[a-zA-Z][a-zA-Z0-9_]*")) return status::invalid_name;
			for (auto& table : tables_)
			{
				if (compare(name, table.first)) return status::duplicate;
			}
			tables_.push_back(std::make_pair(name, table_t(name)));
			return status::ok;
		}

		status_t drop_table(const name_t& name) noexcept
		{
			for (auto ptr = tables_.begin(); ptr != tables_.end(); ++ptr)
			{
				if (compare(name, ptr->first))
				{
					tables_.erase(ptr);
					return status::ok;
				}
			}
			return status::not_found;
		}

		status_t table_exists(const name_t& name) const noexcept
		{
			for (auto& table : tables_)
			{
				if (compare(name, table.first)) return status::ok;
			}
			return status::not_found;
		}

		table_t& get_table(const name_t& name) noexcept
		{
			for (auto& table : tables_)
			{
				if (compare(name, table.first)) return table.second;
			}
			return temp_table_;
		}

	};

} //namespace tucan
