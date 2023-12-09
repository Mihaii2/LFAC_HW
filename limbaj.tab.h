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
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    _int = 258,                    /* _int  */
    _float = 259,                  /* _float  */
    _char = 260,                   /* _char  */
    _string = 261,                 /* _string  */
    _bool = 262,                   /* _bool  */
    _id = 263,                     /* _id  */
    _type = 264,                   /* _type  */
    _if = 265,                     /* _if  */
    _while = 266,                  /* _while  */
    _for = 267,                    /* _for  */
    _special_function = 268,       /* _special_function  */
    _end_usr_types = 269,          /* _end_usr_types  */
    _end_global_vars = 270,        /* _end_global_vars  */
    _end_global_funcs = 271,       /* _end_global_funcs  */
    _const = 272,                  /* _const  */
    _usr_type = 273,               /* _usr_type  */
    _not = 274,                    /* _not  */
    _eq = 275,                     /* _eq  */
    _neq = 276,                    /* _neq  */
    _lt = 277,                     /* _lt  */
    _le = 278,                     /* _le  */
    _gt = 279,                     /* _gt  */
    _ge = 280,                     /* _ge  */
    _assign = 281,                 /* _assign  */
    _plus = 282,                   /* _plus  */
    _minus = 283,                  /* _minus  */
    _mul = 284,                    /* _mul  */
    _div = 285,                    /* _div  */
    _mod = 286,                    /* _mod  */
    _and = 287,                    /* _and  */
    _or = 288,                     /* _or  */
    _geq = 289,                    /* _geq  */
    _leq = 290                     /* _leq  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 16 "limbaj.y"

    int intValue;
    float floatValue;
    char charValue;
    bool boolValue;
    char* string;

#line 107 "limbaj.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_LIMBAJ_TAB_H_INCLUDED  */
