%code {
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

/*****************************************************************************\
* 
*   Generate kmipparse.cpp file with the following bison statement:
*
*   bison -d --no-lines -o sqlsyntax.cpp -p sql_ sqlsyntax.y 
*
\*****************************************************************************/
}

%define api.pure
%parse-param {void* handle}
%lex-param {void* handle}
%start tucansql
%verbose 

%code top {
#include "sqlparser.h"
using namespace tucan;
}


/* value type of Yacc structures and rules */
%union {
   ptree_t* ytree;
   token_t* ytoken;
}

%code {
parser_t* get_parser(void* handle);
int sql_lex(YYSTYPE *lvalp, void* handle);
void sql_error(void* handle, const char* s);
}

/*****************************************************************************\
*	Reserved words
\*****************************************************************************/
%token	<ytoken>	BOOLEAN_ INTEGER DECIMAL DATETIME TEXT BINARY  
%token	<ytoken>	CREATE DROP DELETE_ TABLE INSERT INTO VALUES
%token	<ytoken>	UPDATE SET WHERE SELECT FROM
%token	<ytoken>	NOT NULL_ OR AND AS IS

/*****************************************************************************\
*	Identifiers
\*****************************************************************************/
%token	<ytoken> IDENTIFIER NAME

/*****************************************************************************\
*	Literals
\*****************************************************************************/
%token	<ytoken>	BOOLEAN_LITERAL INTEGER_LITERAL DECIMAL_LITERAL 
%token	<ytoken> DATETIME_LITERAL TEXT_LITERAL BINARY_LITERAL  

/*****************************************************************************\
*	Relational operators
*	NE '<>' LE '<=' GE '>='
\*****************************************************************************/
%token	<ytoken>	NE LE GE 

/*****************************************************************************\
*	token types
\*****************************************************************************/
%type		<ytoken>	'.' ',' ';' '(' ')' '-' '+' '*' '/' '=' '<' '>'

/*****************************************************************************\
*	Production types
\*****************************************************************************/
%type		<ytree>	sql_commands sql_command 
%type		<ytree>	sql_column_definition_list sql_column_definition 
%type		<ytree>	 sql_column_assign_list sql_column_assign
%type		<ytree>	sql_where_clause_opt sql_where_clause
%type		<ytree>	sql_column_name_list sql_expression_list sql_expression 
%type		<ytree>	sql_or_expression sql_and_expression sql_relational_expression
%type		<ytree>	sql_add_expression sql_mult_expression sql_unary_expression 
%type		<ytree>	sql_primary_expression sql_literal sql_identifier
%type		<ytree>	sql_select_expression_list sql_select_expression
%type		<ytree>	sql_insert_column_name_list_opt
%type		<ytree>	sql_select_expression_list_or_star

/*****************************************************************************\
*	Precedence rules
\*****************************************************************************/
%left '+' '-'
%left '*' '/'
%left SQL_UMINUS


/*****************************************************************************\
*	SQL Syntax definitions
\*****************************************************************************/
%%

tucansql
	: sql_commands
	  {
			get_parser(handle)->set_tree($1);
	  }
	;

sql_commands
	: sql_command
	  {
			$$ = $1;
	  }
	| sql_commands ';' sql_command
	  {
			$3->right($1);
			$$ = $3;
	  }
	;
	
sql_command
	: CREATE TABLE IDENTIFIER '(' sql_column_definition_list ')'
	  {
			ptree_t* create_table = make_ptree(get_parser(handle), ptree::create_table, $3, make_text_value($3->text()), $5);
			$$ = create_table;
	  }
	| INSERT INTO IDENTIFIER sql_insert_column_name_list_opt VALUES '(' sql_expression_list ')'
	  {
			ptree_t* left = make_ptree(get_parser(handle), ptree::insert_values, $5, value_t(), $4, $7);
			$$ = make_ptree(get_parser(handle), ptree::insert, $3, make_text_value($3->text()), left);
	  }
	| UPDATE IDENTIFIER SET sql_column_assign_list sql_where_clause_opt
	  {
			ptree_t* left = make_ptree(get_parser(handle), ptree::update_set, $3, value_t(), $5, $4);
			$$ = make_ptree(get_parser(handle), ptree::update, $2, make_text_value($2->text()), left);
	  }
	| DROP TABLE IDENTIFIER
	  {
			$$ = make_ptree(get_parser(handle), ptree::drop_table, $3, make_text_value($3->text()));
	  }
	| DELETE_ FROM IDENTIFIER sql_where_clause_opt
	  {
			$$ = make_ptree(get_parser(handle), ptree::delete_row, $3, make_text_value($3->text()), $4);
	  }
	| SELECT sql_select_expression_list
	  {
			$$ = make_ptree(get_parser(handle), ptree::select, $1, value_t(), $2);
	  }
	| SELECT sql_select_expression_list_or_star FROM IDENTIFIER sql_where_clause_opt
	  {
			ptree_t* where = make_ptree(get_parser(handle), ptree::select_where, nullptr, value_t(), $5, $2);
			ptree_t* from = make_ptree(get_parser(handle), ptree::select_from, $4, value_t(), nullptr, where);
			$$ = make_ptree(get_parser(handle), ptree::select, $1, value_t(), from);
	  }
	;
	
sql_select_expression_list_or_star
	: '*'
	  {
			$$ = make_ptree(get_parser(handle), ptree::field_all, $1, value_t());
	  }
	| sql_select_expression_list
	  {
			$$ = $1;
	  }
	;

sql_select_expression_list
	: sql_select_expression
	  {
			$$ = $1;
	  }
	| sql_select_expression_list ',' sql_select_expression
	  {
			$3->right($1);
			$$ = $3;
	  }
	;

sql_select_expression
	: sql_expression
	  {
			$1->token(token_t());
			$$ = $1;
	  }
	| sql_expression AS IDENTIFIER
	  {
			$1->token(*$3);
			$$ = $1;
	  }
	| sql_expression AS NAME
	  {
			$1->token(*$3);
			$$ = $1;
	  }
	;
	
sql_column_definition_list
	: sql_column_definition
	  {
			ptree_t* coldef = make_ptree(get_parser(handle), ptree::field_def_list, token_t(), value_t(), $1);
			$$ = coldef;
	  }
	| sql_column_definition_list ',' sql_column_definition
	  {
			ptree_t* coldef_list = make_ptree(get_parser(handle), ptree::field_def_list, token_t(), value_t(), $3, $1);
			$$ = coldef_list;
	  }
	;
	
sql_column_definition
	: IDENTIFIER BOOLEAN_
	  {
			ptree_t* field_def = make_ptree(get_parser(handle), ptree::field_def, $1, value_t(false));
			$$ = field_def;
	  }
	| IDENTIFIER INTEGER
	  {
			ptree_t* field_def = make_ptree(get_parser(handle), ptree::field_def, $1, value_t(0ll));
			$$ = field_def;
	  }
	| IDENTIFIER DECIMAL
	  {
			ptree_t* field_def = make_ptree(get_parser(handle), ptree::field_def, $1, value_t(decimal_t()));
			$$ = field_def;
	  }
	| IDENTIFIER DATETIME
	  {
			ptree_t* field_def = make_ptree(get_parser(handle), ptree::field_def, $1, value_t(datetime_t()));
			$$ = field_def;
	  }
	| IDENTIFIER TEXT
	  {
			ptree_t* field_def = make_ptree(get_parser(handle), ptree::field_def, $1, value_t(text_t()));
			$$ = field_def;
	  }
	| IDENTIFIER BINARY
	  {
			ptree_t* field_def = make_ptree(get_parser(handle), ptree::field_def, $1, value_t(binary_t()));
			$$ = field_def;
	  }
	;
	
sql_insert_column_name_list_opt
	:
	  {
			$$ = 0;
	  }
	| '(' sql_column_name_list ')'
	  {
			$$ = $2;
	  }
   ;

sql_column_name_list
	: IDENTIFIER
	  {
			$$ = make_ptree(get_parser(handle), ptree::field_name, $1, value_t());
	  }
	| sql_column_name_list ',' IDENTIFIER
	  {
			$$ = make_ptree(get_parser(handle), ptree::field_name, $3, value_t(), 0, $1);
	  }
	;
	
sql_column_assign_list 
	: sql_column_assign
	  {
			$$ = make_ptree(get_parser(handle), ptree::assign_list, token_t(), value_t(), $1)
	  }
	| sql_column_assign_list ',' sql_column_assign
	  {
			$$ = make_ptree(get_parser(handle), ptree::assign_list, token_t(), value_t(), $3, $1);
	  }
	;
	
sql_column_assign
	: IDENTIFIER '=' sql_expression
	  {
			ptree_t* right = make_ptree(get_parser(handle), ptree::field_name, $1, value_t());
			$$ = make_ptree(get_parser(handle), ptree::assign, $2, value_t(), $3, right);
	  }
	;

sql_where_clause_opt
	:
	  {
			$$ = make_ptree(get_parser(handle), ptree::where_true, 0, value_t(true));
	  }
	| sql_where_clause
	  {
			$$ = $1;
	  }
	;
	
sql_where_clause
	: WHERE sql_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::where, $1, value_t(false), $2);
	  }
	;
	
sql_expression_list
	: sql_expression
	  {
			$$ = $1;
	  }	  
	| sql_expression_list ',' sql_expression
	  {
			$3->right($1);
			$$ = $3;
	  }
	;
	
sql_expression
	: sql_or_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::expr, nullptr, value_t(), $1);
	  }
	;
	
sql_or_expression
	: sql_and_expression
	  {
			$$ = $1;
	  }
	| sql_or_expression OR sql_and_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::logical_or, $2, value_t(false), $1, $3);
	  }
	;
	
sql_and_expression
	: sql_relational_expression
	  {
			$$ = $1;
	  }
	| sql_relational_expression AND sql_relational_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::logical_and, $2, value_t(false), $1, $3);
	  }
	;
	
sql_relational_expression
	: sql_add_expression
	  {
			$$ = $1;
	  }
	| sql_relational_expression '=' sql_add_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::equal, $2, value_t(false), $1, $3);
	  }
	| sql_relational_expression NE sql_add_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::not_equal, $2, value_t(false), $1, $3);
	  }
	| sql_relational_expression '<' sql_add_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::less, $2, value_t(false), $1, $3);
	  }
	| sql_relational_expression LE sql_add_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::less_equal, $2, value_t(false), $1, $3);
	  }
	| sql_relational_expression '>' sql_add_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::greater, $2, value_t(false), $1, $3);
	  }
	| sql_relational_expression GE sql_add_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::greater_equal, $2, value_t(false), $1, $3);
	  }
	| sql_relational_expression IS NULL_
	  {
			$$ = make_ptree(get_parser(handle), ptree::is_null, $2, value_t(false), $1);
	  }
	| sql_relational_expression IS NOT NULL_
	  {
			$$ = make_ptree(get_parser(handle), ptree::is_not_null, $2, value_t(false), $1);
	  }
	;

sql_add_expression
	: sql_mult_expression
	  {
			$$ = $1;
	  }
	| sql_add_expression '+' sql_mult_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::add, $2, value_t(decimal_t()), $1, $3);
	  }
	| sql_add_expression '-' sql_mult_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::subtract, $2, value_t(decimal_t()), $1, $3);
	  }
	;		
	
sql_mult_expression
	: sql_unary_expression
	  {
			$$ = $1;
	  }
	| sql_mult_expression '*' sql_unary_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::multiply, $2, value_t(decimal_t()), $1, $3);
	  }
	| sql_mult_expression '/' sql_unary_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::divide, $2, value_t(decimal_t()), $1, $3);
	  }
	;
	
sql_unary_expression
	: sql_primary_expression
	  {
			$$ = $1;
	  }
	| '+' sql_primary_expression %prec SQL_UMINUS
	  {
			$$ = make_ptree(get_parser(handle), ptree::plus, $1, value_t(decimal_t()), $2);
	  }
	| '-' sql_primary_expression %prec SQL_UMINUS
	  {
			$$ = make_ptree(get_parser(handle), ptree::minus, $1, value_t(decimal_t()), $2);
	  }
	| NOT sql_primary_expression
	  {
			$$ = make_ptree(get_parser(handle), ptree::negate, $1, value_t(decimal_t()), $2);
	  }
	;
	
sql_primary_expression
	: sql_literal
	  {
			$$ = $1;
	  }
	| sql_identifier
	  {
			$$ = $1;
	  }
	| '(' sql_expression ')'
	  {
			$$ = $2;
	  }
	;
	
sql_literal
	: BOOLEAN_LITERAL 
	  {
			$$ = make_ptree(get_parser(handle), ptree::push_literal, $1, make_boolean_value($1->text()));
	  }
	| INTEGER_LITERAL 
	  {
			$$ = make_ptree(get_parser(handle), ptree::push_literal, $1, make_integer_value($1->text()));
	  }
	| DECIMAL_LITERAL  
	  {
			$$ = make_ptree(get_parser(handle), ptree::push_literal, $1, make_decimal_value($1->text()));
	  }
	| DATETIME_LITERAL 
	  {
			$$ = make_ptree(get_parser(handle), ptree::push_literal, $1, make_datetime_value($1->text()));
	  }
	| TEXT_LITERAL 
	  {
			$$ = make_ptree(get_parser(handle), ptree::push_literal, $1, make_text_value($1->text()));
	  }
	| BINARY_LITERAL  
	  {
			$$ = make_ptree(get_parser(handle), ptree::push_literal, $1, make_binary_value($1->text()));
	  }
	| NULL_
	  {
			$$ = make_ptree(get_parser(handle), ptree::push_literal, $1, value_t());
	  }
	;
	
sql_identifier
	: IDENTIFIER
	  {
			$$ = make_ptree(get_parser(handle), ptree::push_field, $1, value_t());
	  }
	| IDENTIFIER '.' IDENTIFIER
	  {
			ptree_t* left = make_ptree(get_parser(handle), ptree::push_table, $1, value_t());
			$$ = make_ptree(get_parser(handle), ptree::push_field, $3, value_t(), left);
	  }
	;
	
%%
/*****************************************************************************\
*	Supporting parser code
\*****************************************************************************/

parser_t* get_parser(void* handle)
{
   return (parser_t*)handle;
}

void sql_error(void* handle, const char* s) 
{
   parser_t* parser = get_parser(handle);
   if (parser)
   {
      parser->set_error(parser::syntax_error, s);
   }
}

void sql_set_error(void* handle, const char* s, int code)
{
   parser_t* parser = get_parser(handle);
   if (parser)
   {
      parser->set_error(code, s);
   }
}

int LookupReservedWord(token_t* token, int id)
{
   struct reserved_t
   {
      const char* text;
      int id;
   };

	static reserved_t reserved[]
	{
        {"AND"       , AND       }
		, {"AS"        , AS        }
		, {"BINARY"    , BINARY    }
		, {"BOOLEAN"   , BOOLEAN_  }
		, {"CREATE"    , CREATE    }
		, {"DATETIME"  , DATETIME  }
		, {"DECIMAL"   , DECIMAL   }
		, {"DELETE"    , DELETE_   }
		, {"DROP"      , DROP      }
		, {"FROM"      , FROM      }
		, {"INSERT"    , INSERT    }
		, {"INTEGER"   , INTEGER   }
		, {"INTO"      , INTO      }
		, {"IS"        , IS        }
		, {"NOT"       , NOT       }
		, {"NULL"      , NULL_     }
		, {"OR"        , OR        }
		, {"SELECT"    , SELECT    }
		, {"SET"       , SET       }
		, {"TABLE"     , TABLE     }
		, {"TEXT"      , TEXT      }
		, {"UPDATE"    , UPDATE    }
		, {"VALUES"    , VALUES    }
		, {"WHERE"     , WHERE     }
	};

	for ( auto& item : reserved )
	{
		if (compare(item.text, token->text()))
		{
			return item.id;
		}
	}
	return id;
}

int sql_lex(YYSTYPE *lvalp, void* handle) 
{
	if (handle)
	{
		token_t* ptr = get_parser(handle)->scanner().next();
		if (ptr)
		{
			int id = ptr->id();
			if (id == token::eof) return id;
			switch (id)
			{
				case token::identifier: ptr->id(LookupReservedWord(ptr, IDENTIFIER)); break;
				case token::decimal: ptr->id(DECIMAL_LITERAL); break;
				case token::datetime: ptr->id(DATETIME_LITERAL); break;
				case token::text: ptr->id(TEXT_LITERAL); break;
				case token::name: ptr->id(NAME); break;
				case token::ne: ptr->id(NE); break;
				case token::le: ptr->id(LE); break;
				case token::ge: ptr->id(GE); break;
				default:
				{
					std::string str("Unknown or invalid token: ");
					str += ptr->text();
					sql_set_error(handle, str.c_str(), parser::syntax_error);
					break;
				}
			}
			lvalp->ytoken = ptr;
			return ptr->id();
		}
	}
	return 0;
}

int sql_parser(void* pt)
{
	return yyparse(pt);
}
