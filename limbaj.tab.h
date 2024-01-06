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
#line 253 "limbaj.y"

    #include <vector>
    #include <string>
    using namespace std;
    class VarInfo;
    class FunctionInfo;
    class ASTNode;

#line 58 "limbaj.tab.h"

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
    USR_TYPE = 266,                /* USR_TYPE  */
    IF = 267,                      /* IF  */
    WHILE = 268,                   /* WHILE  */
    FOR = 269,                     /* FOR  */
    END_USR_TYPES = 270,           /* END_USR_TYPES  */
    END_USR_TYPE_VARS = 271,       /* END_USR_TYPE_VARS  */
    END_GLOBAL_VARS = 272,         /* END_GLOBAL_VARS  */
    END_GLOBAL_FUNCS = 273,        /* END_GLOBAL_FUNCS  */
    CONST = 274,                   /* CONST  */
    EVAL = 275,                    /* EVAL  */
    TYPEOF = 276,                  /* TYPEOF  */
    RETURN = 277,                  /* RETURN  */
    NOT = 278,                     /* NOT  */
    EQ = 279,                      /* EQ  */
    NEQ = 280,                     /* NEQ  */
    LT = 281,                      /* LT  */
    LE = 282,                      /* LE  */
    GT = 283,                      /* GT  */
    GE = 284,                      /* GE  */
    ASSIGN = 285,                  /* ASSIGN  */
    PLUS = 286,                    /* PLUS  */
    MINUS = 287,                   /* MINUS  */
    MUL = 288,                     /* MUL  */
    DIV = 289,                     /* DIV  */
    MOD = 290,                     /* MOD  */
    AND = 291,                     /* AND  */
    OR = 292,                      /* OR  */
    GEQ = 293,                     /* GEQ  */
    LEQ = 294                      /* LEQ  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 262 "limbaj.y"

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
    ASTNode* node;
    std::vector<ASTNode*>* nodes;

#line 129 "limbaj.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_LIMBAJ_TAB_H_INCLUDED  */
