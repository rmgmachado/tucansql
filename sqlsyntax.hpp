
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     BOOLEAN_ = 258,
     INTEGER = 259,
     DECIMAL = 260,
     DATETIME = 261,
     TEXT = 262,
     BINARY = 263,
     CREATE = 264,
     DROP = 265,
     TABLE = 266,
     INSERT = 267,
     INTO = 268,
     VALUES = 269,
     UPDATE = 270,
     SET = 271,
     WHERE = 272,
     SELECT = 273,
     FROM = 274,
     NOT = 275,
     NULL_ = 276,
     OR = 277,
     AND = 278,
     AS = 279,
     IS = 280,
     IDENTIFIER = 281,
     NAME = 282,
     BOOLEAN_LITERAL = 283,
     INTEGER_LITERAL = 284,
     DECIMAL_LITERAL = 285,
     DATETIME_LITERAL = 286,
     TEXT_LITERAL = 287,
     BINARY_LITERAL = 288,
     NE = 289,
     LE = 290,
     GE = 291,
     SQL_UMINUS = 292
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{


   ptree_t* ytree;
   token_t* ytoken;



} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif




