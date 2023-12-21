/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_LIMBAJ_TAB_H_INCLUDED
# define YY_YY_LIMBAJ_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 93 "limbaj.y"

    #include <vector>
    #include <string>
    using namespace std;
    class VarInfo;
    class FunctionInfo;

#line 57 "limbaj.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    INT = 258,                     /* INT  */
    FLOAT = 259,                   /* FLOAT  */
    CHAR = 260,                    /* CHAR  */
    STRING = 261,                  /* STRING  */
    BOOL = 262,                    /* BOOL  */
    ID = 263,                      /* ID  */
    TYPE = 264,                    /* TYPE  */
    SPECIAL_FUNCTION = 265,        /* SPECIAL_FUNCTION  */
    IF = 266,                      /* IF  */
    WHILE = 267,                   /* WHILE  */
    FOR = 268,                     /* FOR  */
    END_USR_TYPES = 269,           /* END_USR_TYPES  */
    END_USR_TYPE_VARS = 270,       /* END_USR_TYPE_VARS  */
    END_GLOBAL_VARS = 271,         /* END_GLOBAL_VARS  */
    END_GLOBAL_FUNCS = 272,        /* END_GLOBAL_FUNCS  */
    CONST = 273,                   /* CONST  */
    USR_TYPE = 274,                /* USR_TYPE  */
    NOT = 275,                     /* NOT  */
    EQ = 276,                      /* EQ  */
    NEQ = 277,                     /* NEQ  */
    LT = 278,                      /* LT  */
    LE = 279,                      /* LE  */
    GT = 280,                      /* GT  */
    GE = 281,                      /* GE  */
    ASSIGN = 282,                  /* ASSIGN  */
    PLUS = 283,                    /* PLUS  */
    MINUS = 284,                   /* MINUS  */
    MUL = 285,                     /* MUL  */
    DIV = 286,                     /* DIV  */
    MOD = 287,                     /* MOD  */
    AND = 288,                     /* AND  */
    OR = 289,                      /* OR  */
    GEQ = 290,                     /* GEQ  */
    LEQ = 291                      /* LEQ  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 101 "limbaj.y"

    int intValue;
    float floatValue;
    char charValue;
    bool boolValue;
    char* string;
    std::vector<VarInfo>* vars;
    std::vector<FunctionInfo>* funcs;
    std::vector<VarInfo>* func_params;
    VarInfo* var;
    FunctionInfo* func;


#line 124 "limbaj.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_LIMBAJ_TAB_H_INCLUDED  */
