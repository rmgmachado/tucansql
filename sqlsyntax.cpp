
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton implementation for Bison's Yacc-like parsers in C
   
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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "2.4.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1

/* Using locations.  */
#define YYLSP_NEEDED 0

/* "%code top" blocks.  */


#include "sqlparser.h"
using namespace tucan;



/* Substitute the variable and function names.  */
#define yyparse         sql_parse
#define yylex           sql_lex
#define yyerror         sql_error
#define yylval          sql_lval
#define yychar          sql_char
#define yydebug         sql_debug
#define yynerrs         sql_nerrs


/* Copy the first part of user declarations.  */



/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Enabling the token table.  */
#ifndef YYTOKEN_TABLE
# define YYTOKEN_TABLE 0
#endif


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
     DELETE_ = 266,
     TABLE = 267,
     INSERT = 268,
     INTO = 269,
     VALUES = 270,
     UPDATE = 271,
     SET = 272,
     WHERE = 273,
     SELECT = 274,
     FROM = 275,
     NOT = 276,
     NULL_ = 277,
     OR = 278,
     AND = 279,
     AS = 280,
     IS = 281,
     IDENTIFIER = 282,
     NAME = 283,
     BOOLEAN_LITERAL = 284,
     INTEGER_LITERAL = 285,
     DECIMAL_LITERAL = 286,
     DATETIME_LITERAL = 287,
     TEXT_LITERAL = 288,
     BINARY_LITERAL = 289,
     NE = 290,
     LE = 291,
     GE = 292,
     SQL_UMINUS = 293
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


/* Copy the second part of user declarations.  */


/* Unqualified %code blocks.  */


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



parser_t* get_parser(void* handle);
int sql_lex(YYSTYPE *lvalp, void* handle);
void sql_error(void* handle, const char* s);




#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#elif (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
typedef signed char yytype_int8;
#else
typedef short int yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(e) ((void) (e))
#else
# define YYUSE(e) /* empty */
#endif

/* Identity function, used to suppress warnings about constant conditions.  */
#ifndef lint
# define YYID(n) (n)
#else
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static int
YYID (int yyi)
#else
static int
YYID (yyi)
    int yyi;
#endif
{
  return yyi;
}
#endif

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#     ifndef _STDLIB_H
#      define _STDLIB_H 1
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (YYID (0))
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined _STDLIB_H \
       && ! ((defined YYMALLOC || defined malloc) \
	     && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef _STDLIB_H
#    define _STDLIB_H 1
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined _STDLIB_H && (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
	 || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  YYSIZE_T yyi;				\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (YYID (0))
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)				\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack_alloc, Stack, yysize);			\
	Stack = &yyptr->Stack_alloc;					\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (YYID (0))

#endif

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  41
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   138

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  75
/* YYNRULES -- Number of states.  */
#define YYNSTATES  132

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   293

#define YYTRANSLATE(YYX)						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      41,    42,    45,    44,    39,    43,    38,    46,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    40,
      48,    47,    49,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    50
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const yytype_uint8 yyprhs[] =
{
       0,     0,     3,     5,     7,    11,    18,    27,    33,    37,
      42,    45,    51,    53,    55,    57,    61,    63,    67,    71,
      73,    77,    80,    82,    84,    86,    88,    90,    92,    93,
      97,    99,   103,   105,   109,   113,   114,   116,   119,   121,
     125,   127,   129,   133,   135,   139,   141,   145,   149,   153,
     157,   161,   165,   169,   174,   176,   180,   184,   186,   190,
     194,   196,   199,   202,   205,   207,   209,   213,   215,   217,
     219,   221,   223,   225,   227,   229
};

/* YYRHS -- A `-1'-separated list of the rules' RHS.  */
static const yytype_int8 yyrhs[] =
{
      52,     0,    -1,    53,    -1,    54,    -1,    53,    40,    54,
      -1,     9,    12,    27,    41,    58,    42,    -1,    13,    14,
      27,    61,    15,    41,    67,    42,    -1,    16,    27,    17,
      63,    65,    -1,    10,    12,    27,    -1,    11,    20,    27,
      65,    -1,    19,    56,    -1,    19,    55,    20,    27,    65,
      -1,    45,    -1,    56,    -1,    57,    -1,    56,    39,    57,
      -1,    68,    -1,    68,    25,    27,    -1,    68,    25,    28,
      -1,    59,    -1,    58,    39,    59,    -1,    27,    60,    -1,
       3,    -1,     4,    -1,     5,    -1,     6,    -1,     7,    -1,
       8,    -1,    -1,    41,    62,    42,    -1,    27,    -1,    62,
      39,    27,    -1,    64,    -1,    63,    39,    64,    -1,    27,
      47,    68,    -1,    -1,    66,    -1,    18,    68,    -1,    68,
      -1,    67,    39,    68,    -1,    69,    -1,    70,    -1,    69,
      23,    70,    -1,    71,    -1,    71,    24,    71,    -1,    72,
      -1,    71,    47,    72,    -1,    71,    35,    72,    -1,    71,
      48,    72,    -1,    71,    36,    72,    -1,    71,    49,    72,
      -1,    71,    37,    72,    -1,    71,    26,    22,    -1,    71,
      26,    21,    22,    -1,    73,    -1,    72,    44,    73,    -1,
      72,    43,    73,    -1,    74,    -1,    73,    45,    74,    -1,
      73,    46,    74,    -1,    75,    -1,    44,    75,    -1,    43,
      75,    -1,    21,    75,    -1,    76,    -1,    77,    -1,    41,
      68,    42,    -1,    29,    -1,    30,    -1,    31,    -1,    32,
      -1,    33,    -1,    34,    -1,    22,    -1,    27,    -1,    27,
      38,    27,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   121,   121,   128,   132,   140,   144,   149,   154,   158,
     162,   166,   175,   179,   186,   190,   198,   203,   208,   216,
     220,   228,   236,   240,   244,   248,   252,   256,   264,   267,
     274,   278,   285,   289,   296,   305,   308,   315,   322,   326,
     334,   341,   345,   352,   356,   363,   367,   371,   375,   379,
     383,   387,   391,   395,   402,   406,   410,   417,   421,   425,
     432,   436,   440,   444,   451,   455,   459,   466,   470,   474,
     478,   482,   486,   490,   497,   501
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || YYTOKEN_TABLE
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "BOOLEAN_", "INTEGER", "DECIMAL",
  "DATETIME", "TEXT", "BINARY", "CREATE", "DROP", "DELETE_", "TABLE",
  "INSERT", "INTO", "VALUES", "UPDATE", "SET", "WHERE", "SELECT", "FROM",
  "NOT", "NULL_", "OR", "AND", "AS", "IS", "IDENTIFIER", "NAME",
  "BOOLEAN_LITERAL", "INTEGER_LITERAL", "DECIMAL_LITERAL",
  "DATETIME_LITERAL", "TEXT_LITERAL", "BINARY_LITERAL", "NE", "LE", "GE",
  "'.'", "','", "';'", "'('", "')'", "'-'", "'+'", "'*'", "'/'", "'='",
  "'<'", "'>'", "SQL_UMINUS", "$accept", "tucansql", "sql_commands",
  "sql_command", "sql_select_expression_list_or_star",
  "sql_select_expression_list", "sql_select_expression",
  "sql_column_definition_list", "sql_column_definition", "sql_column_type",
  "sql_insert_column_name_list_opt", "sql_column_name_list",
  "sql_column_assign_list", "sql_column_assign", "sql_where_clause_opt",
  "sql_where_clause", "sql_expression_list", "sql_expression",
  "sql_or_expression", "sql_and_expression", "sql_relational_expression",
  "sql_add_expression", "sql_mult_expression", "sql_unary_expression",
  "sql_primary_expression", "sql_literal", "sql_identifier", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,    46,    44,
      59,    40,    41,    45,    43,    42,    47,    61,    60,    62,
     293
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    51,    52,    53,    53,    54,    54,    54,    54,    54,
      54,    54,    55,    55,    56,    56,    57,    57,    57,    58,
      58,    59,    60,    60,    60,    60,    60,    60,    61,    61,
      62,    62,    63,    63,    64,    65,    65,    66,    67,    67,
      68,    69,    69,    70,    70,    71,    71,    71,    71,    71,
      71,    71,    71,    71,    72,    72,    72,    73,    73,    73,
      74,    74,    74,    74,    75,    75,    75,    76,    76,    76,
      76,    76,    76,    76,    77,    77
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     3,     6,     8,     5,     3,     4,
       2,     5,     1,     1,     1,     3,     1,     3,     3,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     0,     3,
       1,     3,     1,     3,     3,     0,     1,     2,     1,     3,
       1,     1,     3,     1,     3,     1,     3,     3,     3,     3,
       3,     3,     3,     4,     1,     3,     3,     1,     3,     3,
       1,     2,     2,     2,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,     0,     0,     2,     3,
       0,     0,     0,     0,     0,     0,    73,    74,    67,    68,
      69,    70,    71,    72,     0,     0,     0,    12,     0,    10,
      14,    16,    40,    41,    43,    45,    54,    57,    60,    64,
      65,     1,     0,     0,     8,    35,    28,     0,    63,     0,
       0,    62,    61,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     4,
       0,     0,     9,    36,     0,     0,     0,    35,    32,    75,
      66,    35,    15,    17,    18,    42,    44,     0,    52,    47,
      49,    51,    46,    48,    50,    56,    55,    58,    59,     0,
       0,    19,    37,    30,     0,     0,     0,     0,     7,    11,
      53,    22,    23,    24,    25,    26,    27,    21,     0,     5,
       0,    29,     0,    34,    33,    20,    31,     0,    38,     0,
       6,    39
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     7,     8,     9,    28,    29,    30,   100,   101,   117,
      75,   104,    77,    78,    72,    73,   127,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -74
static const yytype_int8 yypact[] =
{
      64,    -5,     4,    15,    14,    27,   -12,    42,    18,   -74,
      34,    38,    45,    49,    62,    37,   -74,    72,   -74,   -74,
     -74,   -74,   -74,   -74,    19,    37,    37,   -74,    61,    -9,
     -74,    88,    91,   -74,   -23,   -38,    56,   -74,   -74,   -74,
     -74,   -74,    64,    74,   -74,    98,    77,    90,   -74,    92,
      78,   -74,   -74,    94,    19,    76,    19,    19,    85,    19,
      19,    19,    19,    19,    19,    19,    19,    19,    19,   -74,
      95,    19,   -74,   -74,    96,   109,    79,   -16,   -74,   -74,
     -74,    98,   -74,   -74,   -74,   -74,     8,   103,   -74,   -38,
     -38,   -38,   -38,   -38,   -38,    56,    56,   -74,   -74,    81,
      -3,   -74,   -74,   -74,    57,    86,    19,    90,   -74,   -74,
     -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,    95,   -74,
     101,   -74,    19,   -74,   -74,   -74,   -74,    58,   -74,    19,
     -74,   -74
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -74,   -74,   -74,    87,   -74,   -74,    80,   -74,    13,   -74,
     -74,   -74,   -74,    23,   -73,   -74,   -74,   -24,   -74,    82,
      75,    31,    43,    44,    12,   -74,   -74
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -14
static const yytype_int16 yytable[] =
{
      50,    57,    71,    58,   108,    65,    66,    10,   109,    15,
      16,   -13,    59,    60,    61,    17,    11,    18,    19,    20,
      21,    22,    23,   107,    62,    63,    64,    48,    13,    24,
      54,    25,    26,    27,    58,    12,   118,    51,    52,   119,
      15,    16,    41,    59,    60,    61,    17,   102,    18,    19,
      20,    21,    22,    23,    14,    62,    63,    64,    42,    16,
      24,    43,    25,    26,    17,    44,    18,    19,    20,    21,
      22,    23,    45,     1,     2,     3,    46,     4,    24,    47,
       5,    53,   123,     6,   111,   112,   113,   114,   115,   116,
      89,    90,    91,    92,    93,    94,   120,   129,   128,   121,
     130,    67,    68,    83,    84,   131,    87,    88,    95,    96,
      49,    97,    98,    55,    56,    70,    71,    76,    74,    79,
      80,    81,    99,   103,   105,   110,   106,   122,   126,    69,
     124,   125,    86,     0,    82,     0,     0,     0,    85
};

static const yytype_int16 yycheck[] =
{
      24,    24,    18,    26,    77,    43,    44,    12,    81,    21,
      22,    20,    35,    36,    37,    27,    12,    29,    30,    31,
      32,    33,    34,    39,    47,    48,    49,    15,    14,    41,
      39,    43,    44,    45,    26,    20,    39,    25,    26,    42,
      21,    22,     0,    35,    36,    37,    27,    71,    29,    30,
      31,    32,    33,    34,    27,    47,    48,    49,    40,    22,
      41,    27,    43,    44,    27,    27,    29,    30,    31,    32,
      33,    34,    27,     9,    10,    11,    27,    13,    41,    17,
      16,    20,   106,    19,     3,     4,     5,     6,     7,     8,
      59,    60,    61,    62,    63,    64,    39,    39,   122,    42,
      42,    45,    46,    27,    28,   129,    21,    22,    65,    66,
      38,    67,    68,    25,    23,    41,    18,    27,    41,    27,
      42,    27,    27,    27,    15,    22,    47,    41,    27,    42,
     107,   118,    57,    -1,    54,    -1,    -1,    -1,    56
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     9,    10,    11,    13,    16,    19,    52,    53,    54,
      12,    12,    20,    14,    27,    21,    22,    27,    29,    30,
      31,    32,    33,    34,    41,    43,    44,    45,    55,    56,
      57,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      77,     0,    40,    27,    27,    27,    27,    17,    75,    38,
      68,    75,    75,    20,    39,    25,    23,    24,    26,    35,
      36,    37,    47,    48,    49,    43,    44,    45,    46,    54,
      41,    18,    65,    66,    41,    61,    27,    63,    64,    27,
      42,    27,    57,    27,    28,    70,    71,    21,    22,    72,
      72,    72,    72,    72,    72,    73,    73,    74,    74,    27,
      58,    59,    68,    27,    62,    15,    47,    39,    65,    65,
      22,     3,     4,     5,     6,     7,     8,    60,    39,    42,
      39,    42,    41,    68,    64,    59,    27,    67,    68,    39,
      42,    68
};

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK (1);						\
      goto yybackup;						\
    }								\
  else								\
    {								\
      yyerror (handle, YY_("syntax error: cannot back up")); \
      YYERROR;							\
    }								\
while (YYID (0))


#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)				\
    do									\
      if (YYID (N))                                                    \
	{								\
	  (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;	\
	  (Current).first_column = YYRHSLOC (Rhs, 1).first_column;	\
	  (Current).last_line    = YYRHSLOC (Rhs, N).last_line;		\
	  (Current).last_column  = YYRHSLOC (Rhs, N).last_column;	\
	}								\
      else								\
	{								\
	  (Current).first_line   = (Current).last_line   =		\
	    YYRHSLOC (Rhs, 0).last_line;				\
	  (Current).first_column = (Current).last_column =		\
	    YYRHSLOC (Rhs, 0).last_column;				\
	}								\
    while (YYID (0))
#endif


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if YYLTYPE_IS_TRIVIAL
#  define YY_LOCATION_PRINT(File, Loc)			\
     fprintf (File, "%d.%d-%d.%d",			\
	      (Loc).first_line, (Loc).first_column,	\
	      (Loc).last_line,  (Loc).last_column)
# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (&yylval, YYLEX_PARAM)
#else
# define YYLEX yylex (&yylval, handle)
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (YYID (0))

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)			  \
do {									  \
  if (yydebug)								  \
    {									  \
      YYFPRINTF (stderr, "%s ", Title);					  \
      yy_symbol_print (stderr,						  \
		  Type, Value, handle); \
      YYFPRINTF (stderr, "\n");						  \
    }									  \
} while (YYID (0))


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void* handle)
#else
static void
yy_symbol_value_print (yyoutput, yytype, yyvaluep, handle)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    void* handle;
#endif
{
  if (!yyvaluep)
    return;
  YYUSE (handle);
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# else
  YYUSE (yyoutput);
# endif
  switch (yytype)
    {
      default:
	break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, void* handle)
#else
static void
yy_symbol_print (yyoutput, yytype, yyvaluep, handle)
    FILE *yyoutput;
    int yytype;
    YYSTYPE const * const yyvaluep;
    void* handle;
#endif
{
  if (yytype < YYNTOKENS)
    YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep, handle);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
#else
static void
yy_stack_print (yybottom, yytop)
    yytype_int16 *yybottom;
    yytype_int16 *yytop;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (YYID (0))


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yy_reduce_print (YYSTYPE *yyvsp, int yyrule, void* handle)
#else
static void
yy_reduce_print (yyvsp, yyrule, handle)
    YYSTYPE *yyvsp;
    int yyrule;
    void* handle;
#endif
{
  int yynrhs = yyr2[yyrule];
  int yyi;
  unsigned long int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
	     yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr, yyrhs[yyprhs[yyrule] + yyi],
		       &(yyvsp[(yyi + 1) - (yynrhs)])
		       		       , handle);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (yyvsp, Rule, handle); \
} while (YYID (0))

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static YYSIZE_T
yystrlen (const char *yystr)
#else
static YYSIZE_T
yystrlen (yystr)
    const char *yystr;
#endif
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static char *
yystpcpy (char *yydest, const char *yysrc)
#else
static char *
yystpcpy (yydest, yysrc)
    char *yydest;
    const char *yysrc;
#endif
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
	switch (*++yyp)
	  {
	  case '\'':
	  case ',':
	    goto do_not_strip_quotes;

	  case '\\':
	    if (*++yyp != '\\')
	      goto do_not_strip_quotes;
	    /* Fall through.  */
	  default:
	    if (yyres)
	      yyres[yyn] = *yyp;
	    yyn++;
	    break;

	  case '"':
	    if (yyres)
	      yyres[yyn] = '\0';
	    return yyn;
	  }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into YYRESULT an error message about the unexpected token
   YYCHAR while in state YYSTATE.  Return the number of bytes copied,
   including the terminating null byte.  If YYRESULT is null, do not
   copy anything; just return the number of bytes that would be
   copied.  As a special case, return 0 if an ordinary "syntax error"
   message will do.  Return YYSIZE_MAXIMUM if overflow occurs during
   size calculation.  */
static YYSIZE_T
yysyntax_error (char *yyresult, int yystate, int yychar)
{
  int yyn = yypact[yystate];

  if (! (YYPACT_NINF < yyn && yyn <= YYLAST))
    return 0;
  else
    {
      int yytype = YYTRANSLATE (yychar);
      YYSIZE_T yysize0 = yytnamerr (0, yytname[yytype]);
      YYSIZE_T yysize = yysize0;
      YYSIZE_T yysize1;
      int yysize_overflow = 0;
      enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
      char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
      int yyx;

# if 0
      /* This is so xgettext sees the translatable formats that are
	 constructed on the fly.  */
      YY_("syntax error, unexpected %s");
      YY_("syntax error, unexpected %s, expecting %s");
      YY_("syntax error, unexpected %s, expecting %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s");
      YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s");
# endif
      char *yyfmt;
      char const *yyf;
      static char const yyunexpected[] = "syntax error, unexpected %s";
      static char const yyexpecting[] = ", expecting %s";
      static char const yyor[] = " or %s";
      char yyformat[sizeof yyunexpected
		    + sizeof yyexpecting - 1
		    + ((YYERROR_VERBOSE_ARGS_MAXIMUM - 2)
		       * (sizeof yyor - 1))];
      char const *yyprefix = yyexpecting;

      /* Start YYX at -YYN if negative to avoid negative indexes in
	 YYCHECK.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;

      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yycount = 1;

      yyarg[0] = yytname[yytype];
      yyfmt = yystpcpy (yyformat, yyunexpected);

      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	  {
	    if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
	      {
		yycount = 1;
		yysize = yysize0;
		yyformat[sizeof yyunexpected - 1] = '\0';
		break;
	      }
	    yyarg[yycount++] = yytname[yyx];
	    yysize1 = yysize + yytnamerr (0, yytname[yyx]);
	    yysize_overflow |= (yysize1 < yysize);
	    yysize = yysize1;
	    yyfmt = yystpcpy (yyfmt, yyprefix);
	    yyprefix = yyor;
	  }

      yyf = YY_(yyformat);
      yysize1 = yysize + yystrlen (yyf);
      yysize_overflow |= (yysize1 < yysize);
      yysize = yysize1;

      if (yysize_overflow)
	return YYSIZE_MAXIMUM;

      if (yyresult)
	{
	  /* Avoid sprintf, as that infringes on the user's name space.
	     Don't have undefined behavior even if the translation
	     produced a string with the wrong number of "%s"s.  */
	  char *yyp = yyresult;
	  int yyi = 0;
	  while ((*yyp = *yyf) != '\0')
	    {
	      if (*yyp == '%' && yyf[1] == 's' && yyi < yycount)
		{
		  yyp += yytnamerr (yyp, yyarg[yyi++]);
		  yyf += 2;
		}
	      else
		{
		  yyp++;
		  yyf++;
		}
	    }
	}
      return yysize;
    }
}
#endif /* YYERROR_VERBOSE */


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

/*ARGSUSED*/
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, void* handle)
#else
static void
yydestruct (yymsg, yytype, yyvaluep, handle)
    const char *yymsg;
    int yytype;
    YYSTYPE *yyvaluep;
    void* handle;
#endif
{
  YYUSE (yyvaluep);
  YYUSE (handle);

  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  switch (yytype)
    {

      default:
	break;
    }
}

/* Prevent warnings from -Wmissing-prototypes.  */
#ifdef YYPARSE_PARAM
#if defined __STDC__ || defined __cplusplus
int yyparse (void *YYPARSE_PARAM);
#else
int yyparse ();
#endif
#else /* ! YYPARSE_PARAM */
#if defined __STDC__ || defined __cplusplus
int yyparse (void* handle);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */





/*-------------------------.
| yyparse or yypush_parse.  |
`-------------------------*/

#ifdef YYPARSE_PARAM
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void *YYPARSE_PARAM)
#else
int
yyparse (YYPARSE_PARAM)
    void *YYPARSE_PARAM;
#endif
#else /* ! YYPARSE_PARAM */
#if (defined __STDC__ || defined __C99__FUNC__ \
     || defined __cplusplus || defined _MSC_VER)
int
yyparse (void* handle)
#else
int
yyparse (handle)
    void* handle;
#endif
#endif
{
/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       `yyss': related to states.
       `yyvs': related to semantic values.

       Refer to the stacks thru separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yytoken = 0;
  yyss = yyssa;
  yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */
  yyssp = yyss;
  yyvsp = yyvs;

  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack.  Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	yytype_int16 *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow (YY_("memory exhausted"),
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	yytype_int16 *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyexhaustedlab;
	YYSTACK_RELOCATE (yyss_alloc, yyss);
	YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  *++yyvsp = yylval;

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:

    {
			get_parser(handle)->set_tree((yyvsp[(1) - (1)].ytree));
	  ;}
    break;

  case 3:

    {
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 4:

    {
			(yyvsp[(3) - (3)].ytree)->right((yyvsp[(1) - (3)].ytree));
			(yyval.ytree) = (yyvsp[(3) - (3)].ytree);
	  ;}
    break;

  case 5:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::create_table, (yyvsp[(3) - (6)].ytoken), make_text_value((yyvsp[(3) - (6)].ytoken)->text()), (yyvsp[(5) - (6)].ytree));
	  ;}
    break;

  case 6:

    {
			ptree_t* left = make_ptree(get_parser(handle), ptree::insert_values, (yyvsp[(5) - (8)].ytoken), value_t(), (yyvsp[(4) - (8)].ytree), (yyvsp[(7) - (8)].ytree));
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::insert, (yyvsp[(3) - (8)].ytoken), make_text_value((yyvsp[(3) - (8)].ytoken)->text()), left);
	  ;}
    break;

  case 7:

    {
			ptree_t* left = make_ptree(get_parser(handle), ptree::update_set, (yyvsp[(3) - (5)].ytoken), value_t(), (yyvsp[(5) - (5)].ytree), (yyvsp[(4) - (5)].ytree));
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::update, (yyvsp[(2) - (5)].ytoken), make_text_value((yyvsp[(2) - (5)].ytoken)->text()), left);
	  ;}
    break;

  case 8:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::drop_table, (yyvsp[(3) - (3)].ytoken), make_text_value((yyvsp[(3) - (3)].ytoken)->text()));
	  ;}
    break;

  case 9:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::delete_row, (yyvsp[(3) - (4)].ytoken), make_text_value((yyvsp[(3) - (4)].ytoken)->text()), (yyvsp[(4) - (4)].ytree));
	  ;}
    break;

  case 10:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::select, (yyvsp[(1) - (2)].ytoken), value_t(), (yyvsp[(2) - (2)].ytree));
	  ;}
    break;

  case 11:

    {
			ptree_t* where = make_ptree(get_parser(handle), ptree::select_where, nullptr, value_t(), (yyvsp[(5) - (5)].ytree), (yyvsp[(2) - (5)].ytree));
			ptree_t* from = make_ptree(get_parser(handle), ptree::select_from, (yyvsp[(4) - (5)].ytoken), value_t(), nullptr, where);
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::select, (yyvsp[(1) - (5)].ytoken), value_t(), from);
	  ;}
    break;

  case 12:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::field_all, (yyvsp[(1) - (1)].ytoken), value_t());
	  ;}
    break;

  case 13:

    {
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 14:

    {
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 15:

    {
			(yyvsp[(3) - (3)].ytree)->right((yyvsp[(1) - (3)].ytree));
			(yyval.ytree) = (yyvsp[(3) - (3)].ytree);
	  ;}
    break;

  case 16:

    {
			(yyvsp[(1) - (1)].ytree)->token(token_t());
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 17:

    {
			(yyvsp[(1) - (3)].ytree)->token(*(yyvsp[(3) - (3)].ytoken));
			(yyval.ytree) = (yyvsp[(1) - (3)].ytree);
	  ;}
    break;

  case 18:

    {
			(yyvsp[(1) - (3)].ytree)->token(*(yyvsp[(3) - (3)].ytoken));
			(yyval.ytree) = (yyvsp[(1) - (3)].ytree);
	  ;}
    break;

  case 19:

    {
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 20:

    {
			(yyvsp[(3) - (3)].ytree)->right((yyvsp[(1) - (3)].ytree));
			(yyval.ytree) = (yyvsp[(3) - (3)].ytree);
	  ;}
    break;

  case 21:

    {
			(yyvsp[(2) - (2)].ytree)->token(*(yyvsp[(1) - (2)].ytoken));
			(yyval.ytree) = (yyvsp[(2) - (2)].ytree);
	  ;}
    break;

  case 22:

    {
			(yyval.ytree) =  make_ptree(get_parser(handle), ptree::field_def, (yyvsp[(1) - (1)].ytoken), value_t(false));
	  ;}
    break;

  case 23:

    {
			(yyval.ytree) =  make_ptree(get_parser(handle), ptree::field_def, (yyvsp[(1) - (1)].ytoken), value_t(0ll));
	  ;}
    break;

  case 24:

    {
			(yyval.ytree) =  make_ptree(get_parser(handle), ptree::field_def, (yyvsp[(1) - (1)].ytoken), value_t(decimal_t()));
	  ;}
    break;

  case 25:

    {
			(yyval.ytree) =  make_ptree(get_parser(handle), ptree::field_def, (yyvsp[(1) - (1)].ytoken), value_t(datetime_t()));
	  ;}
    break;

  case 26:

    {
			(yyval.ytree) =  make_ptree(get_parser(handle), ptree::field_def, (yyvsp[(1) - (1)].ytoken), value_t(text_t()));
	  ;}
    break;

  case 27:

    {
			(yyval.ytree) =  make_ptree(get_parser(handle), ptree::field_def, (yyvsp[(1) - (1)].ytoken), value_t(binary_t()));
	  ;}
    break;

  case 28:

    {
			(yyval.ytree) = nullptr;
	  ;}
    break;

  case 29:

    {
			(yyval.ytree) = (yyvsp[(2) - (3)].ytree);
	  ;}
    break;

  case 30:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::field_name, (yyvsp[(1) - (1)].ytoken), value_t());
	  ;}
    break;

  case 31:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::field_name, (yyvsp[(3) - (3)].ytoken), value_t(), nullptr, (yyvsp[(1) - (3)].ytree));
	  ;}
    break;

  case 32:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::assign_list, token_t(), value_t(), (yyvsp[(1) - (1)].ytree))
	  ;}
    break;

  case 33:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::assign_list, token_t(), value_t(), (yyvsp[(3) - (3)].ytree), (yyvsp[(1) - (3)].ytree));
	  ;}
    break;

  case 34:

    {
			ptree_t* right = make_ptree(get_parser(handle), ptree::field_name, (yyvsp[(1) - (3)].ytoken), value_t());
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::assign, (yyvsp[(2) - (3)].ytoken), value_t(), (yyvsp[(3) - (3)].ytree), right);
	  ;}
    break;

  case 35:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::where_true, nullptr, value_t(true));
	  ;}
    break;

  case 36:

    {
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 37:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::where, (yyvsp[(1) - (2)].ytoken), value_t(false), (yyvsp[(2) - (2)].ytree));
	  ;}
    break;

  case 38:

    {
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 39:

    {
			(yyvsp[(3) - (3)].ytree)->right((yyvsp[(1) - (3)].ytree));
			(yyval.ytree) = (yyvsp[(3) - (3)].ytree);
	  ;}
    break;

  case 40:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::expr, nullptr, value_t(), (yyvsp[(1) - (1)].ytree));
	  ;}
    break;

  case 41:

    {
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 42:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::logical_or, (yyvsp[(2) - (3)].ytoken), value_t(false), (yyvsp[(1) - (3)].ytree), (yyvsp[(3) - (3)].ytree));
	  ;}
    break;

  case 43:

    {
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 44:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::logical_and, (yyvsp[(2) - (3)].ytoken), value_t(false), (yyvsp[(1) - (3)].ytree), (yyvsp[(3) - (3)].ytree));
	  ;}
    break;

  case 45:

    {
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 46:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::equal, (yyvsp[(2) - (3)].ytoken), value_t(false), (yyvsp[(1) - (3)].ytree), (yyvsp[(3) - (3)].ytree));
	  ;}
    break;

  case 47:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::not_equal, (yyvsp[(2) - (3)].ytoken), value_t(false), (yyvsp[(1) - (3)].ytree), (yyvsp[(3) - (3)].ytree));
	  ;}
    break;

  case 48:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::less, (yyvsp[(2) - (3)].ytoken), value_t(false), (yyvsp[(1) - (3)].ytree), (yyvsp[(3) - (3)].ytree));
	  ;}
    break;

  case 49:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::less_equal, (yyvsp[(2) - (3)].ytoken), value_t(false), (yyvsp[(1) - (3)].ytree), (yyvsp[(3) - (3)].ytree));
	  ;}
    break;

  case 50:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::greater, (yyvsp[(2) - (3)].ytoken), value_t(false), (yyvsp[(1) - (3)].ytree), (yyvsp[(3) - (3)].ytree));
	  ;}
    break;

  case 51:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::greater_equal, (yyvsp[(2) - (3)].ytoken), value_t(false), (yyvsp[(1) - (3)].ytree), (yyvsp[(3) - (3)].ytree));
	  ;}
    break;

  case 52:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::is_null, (yyvsp[(2) - (3)].ytoken), value_t(false), (yyvsp[(1) - (3)].ytree));
	  ;}
    break;

  case 53:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::is_not_null, (yyvsp[(2) - (4)].ytoken), value_t(false), (yyvsp[(1) - (4)].ytree));
	  ;}
    break;

  case 54:

    {
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 55:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::add, (yyvsp[(2) - (3)].ytoken), value_t(decimal_t()), (yyvsp[(1) - (3)].ytree), (yyvsp[(3) - (3)].ytree));
	  ;}
    break;

  case 56:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::subtract, (yyvsp[(2) - (3)].ytoken), value_t(decimal_t()), (yyvsp[(1) - (3)].ytree), (yyvsp[(3) - (3)].ytree));
	  ;}
    break;

  case 57:

    {
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 58:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::multiply, (yyvsp[(2) - (3)].ytoken), value_t(decimal_t()), (yyvsp[(1) - (3)].ytree), (yyvsp[(3) - (3)].ytree));
	  ;}
    break;

  case 59:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::divide, (yyvsp[(2) - (3)].ytoken), value_t(decimal_t()), (yyvsp[(1) - (3)].ytree), (yyvsp[(3) - (3)].ytree));
	  ;}
    break;

  case 60:

    {
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 61:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::plus, (yyvsp[(1) - (2)].ytoken), value_t(decimal_t()), (yyvsp[(2) - (2)].ytree));(yyvsp[(2) - (2)].ytree);
	  ;}
    break;

  case 62:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::minus, (yyvsp[(1) - (2)].ytoken), value_t(decimal_t()), (yyvsp[(2) - (2)].ytree));
	  ;}
    break;

  case 63:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::negate, (yyvsp[(1) - (2)].ytoken), value_t(decimal_t()), (yyvsp[(2) - (2)].ytree));
	  ;}
    break;

  case 64:

    {
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 65:

    {
			(yyval.ytree) = (yyvsp[(1) - (1)].ytree);
	  ;}
    break;

  case 66:

    {
			(yyval.ytree) = (yyvsp[(2) - (3)].ytree);
	  ;}
    break;

  case 67:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::push_literal, (yyvsp[(1) - (1)].ytoken), make_boolean_value((yyvsp[(1) - (1)].ytoken)->text()));
	  ;}
    break;

  case 68:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::push_literal, (yyvsp[(1) - (1)].ytoken), make_integer_value((yyvsp[(1) - (1)].ytoken)->text()));
	  ;}
    break;

  case 69:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::push_literal, (yyvsp[(1) - (1)].ytoken), make_decimal_value((yyvsp[(1) - (1)].ytoken)->text()));
	  ;}
    break;

  case 70:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::push_literal, (yyvsp[(1) - (1)].ytoken), make_datetime_value((yyvsp[(1) - (1)].ytoken)->text()));
	  ;}
    break;

  case 71:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::push_literal, (yyvsp[(1) - (1)].ytoken), make_text_value((yyvsp[(1) - (1)].ytoken)->text()));
	  ;}
    break;

  case 72:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::push_literal, (yyvsp[(1) - (1)].ytoken), make_binary_value((yyvsp[(1) - (1)].ytoken)->text()));
	  ;}
    break;

  case 73:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::push_literal, (yyvsp[(1) - (1)].ytoken), value_t());
	  ;}
    break;

  case 74:

    {
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::push_field, (yyvsp[(1) - (1)].ytoken), value_t());
	  ;}
    break;

  case 75:

    {
			ptree_t* left = make_ptree(get_parser(handle), ptree::push_table, (yyvsp[(1) - (3)].ytoken), value_t());
			(yyval.ytree) = make_ptree(get_parser(handle), ptree::push_field, (yyvsp[(3) - (3)].ytoken), value_t(), left);
	  ;}
    break;



      default: break;
    }
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (handle, YY_("syntax error"));
#else
      {
	YYSIZE_T yysize = yysyntax_error (0, yystate, yychar);
	if (yymsg_alloc < yysize && yymsg_alloc < YYSTACK_ALLOC_MAXIMUM)
	  {
	    YYSIZE_T yyalloc = 2 * yysize;
	    if (! (yysize <= yyalloc && yyalloc <= YYSTACK_ALLOC_MAXIMUM))
	      yyalloc = YYSTACK_ALLOC_MAXIMUM;
	    if (yymsg != yymsgbuf)
	      YYSTACK_FREE (yymsg);
	    yymsg = (char *) YYSTACK_ALLOC (yyalloc);
	    if (yymsg)
	      yymsg_alloc = yyalloc;
	    else
	      {
		yymsg = yymsgbuf;
		yymsg_alloc = sizeof yymsgbuf;
	      }
	  }

	if (0 < yysize && yysize <= yymsg_alloc)
	  {
	    (void) yysyntax_error (yymsg, yystate, yychar);
	    yyerror (handle, yymsg);
	  }
	else
	  {
	    yyerror (handle, YY_("syntax error"));
	    if (yysize != 0)
	      goto yyexhaustedlab;
	  }
      }
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
	{
	  /* Return failure if at end of input.  */
	  if (yychar == YYEOF)
	    YYABORT;
	}
      else
	{
	  yydestruct ("Error: discarding",
		      yytoken, &yylval, handle);
	  yychar = YYEMPTY;
	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule which action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;


      yydestruct ("Error: popping",
		  yystos[yystate], yyvsp, handle);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  *++yyvsp = yylval;


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined(yyoverflow) || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (handle, YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
     yydestruct ("Cleanup: discarding lookahead",
		 yytoken, &yylval, handle);
  /* Do not reclaim the symbols of the rule which action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
		  yystos[*yyssp], yyvsp, handle);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  /* Make sure YYID is used.  */
  return YYID (yyresult);
}




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

