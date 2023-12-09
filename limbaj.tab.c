/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "limbaj.y"

#include <iostream>
#include <string>
#include <vector>
using namespace std;
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);

// void globalFunction(int param);


#line 86 "limbaj.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "limbaj.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* DIV  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_CHAR = 5,                       /* CHAR  */
  YYSYMBOL_STRING = 6,                     /* STRING  */
  YYSYMBOL_BOOL = 7,                       /* BOOL  */
  YYSYMBOL_ID = 8,                         /* ID  */
  YYSYMBOL_TYPE = 9,                       /* TYPE  */
  YYSYMBOL_IF = 10,                        /* IF  */
  YYSYMBOL_ELSE = 11,                      /* ELSE  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_SPECIAL_FUNCTION = 14,          /* SPECIAL_FUNCTION  */
  YYSYMBOL_END_USR_TYPES = 15,             /* END_USR_TYPES  */
  YYSYMBOL_END_GLOBAL_VARS = 16,           /* END_GLOBAL_VARS  */
  YYSYMBOL_END_GLOBAL_FUNCS = 17,          /* END_GLOBAL_FUNCS  */
  YYSYMBOL_CONST = 18,                     /* CONST  */
  YYSYMBOL_USR_TYPE = 19,                  /* USR_TYPE  */
  YYSYMBOL_NOT = 20,                       /* NOT  */
  YYSYMBOL_EQ = 21,                        /* EQ  */
  YYSYMBOL_NEQ = 22,                       /* NEQ  */
  YYSYMBOL_LT = 23,                        /* LT  */
  YYSYMBOL_LE = 24,                        /* LE  */
  YYSYMBOL_GT = 25,                        /* GT  */
  YYSYMBOL_GE = 26,                        /* GE  */
  YYSYMBOL_ASSIGN = 27,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 28,                      /* PLUS  */
  YYSYMBOL_MINUS = 29,                     /* MINUS  */
  YYSYMBOL_MUL = 30,                       /* MUL  */
  YYSYMBOL_MOD = 31,                       /* MOD  */
  YYSYMBOL_AND = 32,                       /* AND  */
  YYSYMBOL_OR = 33,                        /* OR  */
  YYSYMBOL_34_ = 34,                       /* '{'  */
  YYSYMBOL_35_ = 35,                       /* '}'  */
  YYSYMBOL_36_ = 36,                       /* ';'  */
  YYSYMBOL_37_ = 37,                       /* '('  */
  YYSYMBOL_38_ = 38,                       /* ')'  */
  YYSYMBOL_39_ = 39,                       /* '='  */
  YYSYMBOL_40_ = 40,                       /* '['  */
  YYSYMBOL_41_ = 41,                       /* ']'  */
  YYSYMBOL_42_ = 42,                       /* ','  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_program = 44,                   /* program  */
  YYSYMBOL_user_defined_types = 45,        /* user_defined_types  */
  YYSYMBOL_user_defined_type = 46,         /* user_defined_type  */
  YYSYMBOL_usr_type_body = 47,             /* usr_type_body  */
  YYSYMBOL_member = 48,                    /* member  */
  YYSYMBOL_declarations = 49,              /* declarations  */
  YYSYMBOL_decl = 50,                      /* decl  */
  YYSYMBOL_CONST_VAL = 51,                 /* CONST_VAL  */
  YYSYMBOL_global_function_definitions = 52, /* global_function_definitions  */
  YYSYMBOL_global_function_definition = 53, /* global_function_definition  */
  YYSYMBOL_list_param = 54,                /* list_param  */
  YYSYMBOL_param = 55,                     /* param  */
  YYSYMBOL_statements = 56,                /* statements  */
  YYSYMBOL_statement = 57,                 /* statement  */
  YYSYMBOL_assignment_statement = 58,      /* assignment_statement  */
  YYSYMBOL_left_value = 59,                /* left_value  */
  YYSYMBOL_array_element_access = 60,      /* array_element_access  */
  YYSYMBOL_control_statement = 61,         /* control_statement  */
  YYSYMBOL_if_statement = 62,              /* if_statement  */
  YYSYMBOL_for_statement = 63,             /* for_statement  */
  YYSYMBOL_while_statement = 64,           /* while_statement  */
  YYSYMBOL_function_call_statement = 65,   /* function_call_statement  */
  YYSYMBOL_function_call = 66,             /* function_call  */
  YYSYMBOL_arguments = 67,                 /* arguments  */
  YYSYMBOL_arguments_list = 68,            /* arguments_list  */
  YYSYMBOL_expr = 69,                      /* expr  */
  YYSYMBOL_T = 70,                         /* T  */
  YYSYMBOL_F = 71,                         /* F  */
  YYSYMBOL_G = 72,                         /* G  */
  YYSYMBOL_H = 73,                         /* H  */
  YYSYMBOL_I = 74,                         /* I  */
  YYSYMBOL_J = 75,                         /* J  */
  YYSYMBOL_special_function = 76           /* special_function  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

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
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
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
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  8
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   149

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  34
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  151

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   288


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      37,    38,     2,     2,    42,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    36,
       2,    39,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    40,     2,    41,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    34,     2,    35,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    40,    40,    43,    44,    48,    54,    55,    58,    59,
      63,    64,    67,    73,    79,    80,    81,    82,    83,    87,
      88,    91,    97,    98,   101,   109,   110,   113,   114,   115,
     118,   123,   124,   127,   129,   130,   131,   134,   139,   144,
     149,   151,   153,   154,   157,   158,   161,   162,   164,   165,
     166,   168,   169,   170,   171,   172,   174,   175,   176,   178,
     179,   180,   181,   183,   184,   185,   188,   189,   190,   191,
     195
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "DIV", "error", "\"invalid token\"", "INT", "FLOAT", "CHAR", "STRING",
  "BOOL", "ID", "TYPE", "IF", "ELSE", "WHILE", "FOR", "SPECIAL_FUNCTION",
  "END_USR_TYPES", "END_GLOBAL_VARS", "END_GLOBAL_FUNCS", "CONST",
  "USR_TYPE", "NOT", "EQ", "NEQ", "LT", "LE", "GT", "GE", "ASSIGN", "PLUS",
  "MINUS", "MUL", "MOD", "AND", "OR", "'{'", "'}'", "';'", "'('", "')'",
  "'='", "'['", "']'", "','", "$accept", "program", "user_defined_types",
  "user_defined_type", "usr_type_body", "member", "declarations", "decl",
  "CONST_VAL", "global_function_definitions", "global_function_definition",
  "list_param", "param", "statements", "statement", "assignment_statement",
  "left_value", "array_element_access", "control_statement",
  "if_statement", "for_statement", "while_statement",
  "function_call_statement", "function_call", "arguments",
  "arguments_list", "expr", "T", "F", "G", "H", "I", "J",
  "special_function", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-75)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      14,    18,    31,    37,    68,    20,   -75,    50,   -75,   -75,
      30,   -75,    32,    28,   -75,    88,   -75,    56,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,     3,    39,    75,    71,   -75,
     -75,    59,    74,   -75,     7,   -75,    49,   100,   -75,   -75,
       0,    84,    25,   111,    86,   -75,   -75,   -75,   -75,   -75,
     -75,     9,     1,    17,    -6,    85,    87,    89,   -75,   -75,
     -75,    94,   -75,   -75,   -75,   -75,   -75,   -75,    91,    95,
     -75,     4,     4,     4,     4,   115,     4,   -75,   -75,   -75,
     -75,   -75,    11,     4,    90,    83,   -75,    24,    76,    78,
       5,    77,   -75,    92,    93,    96,    97,    99,   102,    41,
      24,    98,   -75,     4,    11,    11,    11,    11,    11,    11,
      11,    11,    11,    11,    11,    11,    11,   -75,   105,   106,
       4,   -75,   -75,   -75,   -75,    76,    76,    78,    78,    78,
      78,     5,     5,    77,    77,    77,   -75,   -75,   -75,   -75,
     107,    47,    55,   115,   -75,   -75,   103,   108,   -75,    62,
     -75
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     0,     0,     0,    12,     0,     1,     3,
       0,    10,     0,     0,    11,     0,    19,     0,     4,    14,
      15,    16,    17,    18,    13,     0,     0,     0,     0,    20,
       6,     0,     0,     2,     0,    22,     0,     0,     5,     7,
       0,     0,     0,     0,     0,    23,    25,     8,    22,    24,
      25,     0,     0,     0,    31,     0,     0,     0,    70,    26,
      27,     0,    32,    28,    34,    35,    36,    29,     0,     0,
      21,    42,     0,     0,     0,     0,     0,    40,    25,    66,
      67,    68,     0,     0,     0,    43,    44,    47,    50,    55,
      58,    62,    65,     0,     0,     0,    31,     0,     0,     0,
      46,     0,    41,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    33,     0,     0,
       0,    30,     9,    69,    45,    48,    49,    51,    52,    53,
      54,    56,    57,    60,    59,    61,    63,    64,    25,    25,
       0,     0,     0,     0,    37,    39,     0,     0,    25,     0,
      38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -75,   -75,   -75,   -75,   -75,   -75,   -75,   126,   -75,   -75,
     -75,   101,   -75,   -50,   -75,   -74,   -75,   -75,   -75,   -75,
     -75,   -75,   -75,   -75,   -75,   -75,   -70,    63,     8,   -28,
       6,    -9,    -1,   -75
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,    13,    18,    34,    39,     4,     5,    24,    25,
      29,    40,    45,    51,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    84,    85,    86,    87,    88,    89,
      90,    91,    92,    33
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      53,    97,    93,    94,    95,   112,    98,    79,    80,    43,
      43,    81,    27,   101,    79,    80,    37,    54,    81,    55,
      28,    56,    57,     1,    82,    54,     6,    55,    99,    56,
      57,    71,     2,   124,    72,   113,   114,     8,    44,    69,
       7,    83,    38,    16,    58,   104,   105,    17,    83,    54,
     140,    55,    70,    56,    57,    54,    11,    55,    12,    56,
      57,    47,    48,    54,    26,    55,    14,    56,    57,   146,
      54,    15,    55,    30,    56,    57,   122,     1,   127,   128,
     129,   130,   144,    31,     9,    32,     2,    41,   141,   142,
     145,    19,    20,    21,    22,    23,    35,   150,   149,   106,
     107,   108,   109,   133,   134,   135,   110,   111,    42,   115,
     116,    36,   125,   126,   136,   137,   131,   132,    46,    49,
      50,    76,    73,    96,    74,   103,    75,    77,   102,    78,
      10,   118,     0,   117,   119,   120,   123,    72,   121,   138,
     139,   147,   148,   143,     0,   100,     0,     0,     0,    52
};

static const yytype_int16 yycheck[] =
{
      50,    75,    72,    73,    74,     0,    76,     3,     4,     9,
       9,     7,     9,    83,     3,     4,     9,     8,     7,    10,
      17,    12,    13,     9,    20,     8,     8,    10,    78,    12,
      13,    37,    18,   103,    40,    30,    31,     0,    38,    38,
       9,    37,    35,    15,    35,    21,    22,    19,    37,     8,
     120,    10,    35,    12,    13,     8,    36,    10,     8,    12,
      13,    36,    37,     8,     8,    10,    36,    12,    13,   143,
       8,    39,    10,    34,    12,    13,    35,     9,   106,   107,
     108,   109,    35,     8,    16,    14,    18,    38,   138,   139,
      35,     3,     4,     5,     6,     7,    37,    35,   148,    23,
      24,    25,    26,   112,   113,   114,    28,    29,     8,    32,
      33,    37,   104,   105,   115,   116,   110,   111,    34,     8,
      34,    27,    37,     8,    37,    42,    37,    36,    38,    34,
       4,    38,    -1,    41,    38,    36,    38,    40,    36,    34,
      34,    38,    34,    36,    -1,    82,    -1,    -1,    -1,    48
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    18,    44,    49,    50,     8,     9,     0,    16,
      50,    36,     8,    45,    36,    39,    15,    19,    46,     3,
       4,     5,     6,     7,    51,    52,     8,     9,    17,    53,
      34,     8,    14,    76,    47,    37,    37,     9,    35,    48,
      54,    38,     8,     9,    38,    55,    34,    36,    37,     8,
      34,    56,    54,    56,     8,    10,    12,    13,    35,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    38,
      35,    37,    40,    37,    37,    37,    27,    36,    34,     3,
       4,     7,    20,    37,    67,    68,    69,    70,    71,    72,
      73,    74,    75,    69,    69,    69,     8,    58,    69,    56,
      70,    69,    38,    42,    21,    22,    23,    24,    25,    26,
      28,    29,     0,    30,    31,    32,    33,    41,    38,    38,
      36,    36,    35,    38,    69,    71,    71,    72,    72,    72,
      72,    73,    73,    74,    74,    74,    75,    75,    34,    34,
      69,    56,    56,    36,    35,    35,    58,    38,    34,    56,
      35
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    45,    45,    46,    47,    47,    48,    48,
      49,    49,    50,    50,    51,    51,    51,    51,    51,    52,
      52,    53,    54,    54,    55,    56,    56,    57,    57,    57,
      58,    59,    59,    60,    61,    61,    61,    62,    63,    64,
      65,    66,    67,    67,    68,    68,    69,    69,    70,    70,
      70,    71,    71,    71,    71,    71,    72,    72,    72,    73,
      73,    73,    73,    74,    74,    74,    75,    75,    75,    75,
      76
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     7,     0,     2,     5,     0,     2,     3,     8,
       2,     3,     2,     5,     1,     1,     1,     1,     1,     0,
       2,     8,     0,     2,     2,     0,     2,     1,     1,     1,
       4,     1,     1,     4,     1,     1,     1,     7,    11,     7,
       2,     4,     0,     1,     1,     3,     2,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       3,     3,     1,     3,     3,     1,     1,     1,     1,     3,
       6
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


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
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= DIV)
    {
      yychar = DIV;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
      if (yytable_value_is_error (yyn))
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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
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
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: declarations END_GLOBAL_VARS user_defined_types END_USR_TYPES global_function_definitions END_GLOBAL_FUNCS special_function  */
#line 40 "limbaj.y"
                                                                                                                                     {printf("The programme is correct!\n");}
#line 1250 "limbaj.tab.c"
    break;

  case 5: /* user_defined_type: USR_TYPE ID '{' usr_type_body '}'  */
#line 48 "limbaj.y"
                                                     {
    printf("User-defined type: %s\n", (yyvsp[-3].string));
    // Code to handle user-defined types
    // You can store the type information in a symbol table or generate C++ code for the type
}
#line 1260 "limbaj.tab.c"
    break;

  case 12: /* decl: TYPE ID  */
#line 67 "limbaj.y"
              {
    printf("Variable: %s, name: %s\n", (yyvsp[-1].string), (yyvsp[0].string));
    // Code to handle global variable declarations
    // You can store the variable information in a symbol table or generate C++ code for the variable
    // Access the variable using $$ = $2;
    }
#line 1271 "limbaj.tab.c"
    break;

  case 13: /* decl: CONST TYPE ID '=' CONST_VAL  */
#line 73 "limbaj.y"
                                      {
            // Code to handle global constant declarations
            // You can store the constant information in a symbol table or generate C++ code for the constant
            // Access the constant using $$ = $4;
        }
#line 1281 "limbaj.tab.c"
    break;

  case 21: /* global_function_definition: TYPE ID '(' list_param ')' '{' statements '}'  */
#line 91 "limbaj.y"
                                                                          {
    // Code to handle function definitions
    // You can store the function information in a symbol table or generate C++ code for the function
    // Access the function using $$ = $2;
}
#line 1291 "limbaj.tab.c"
    break;

  case 24: /* param: TYPE ID  */
#line 101 "limbaj.y"
               {
    // Code to handle function parameters
    // You can store the parameter information in a symbol table or generate C++ code for the parameter
}
#line 1300 "limbaj.tab.c"
    break;

  case 30: /* assignment_statement: left_value ASSIGN expr ';'  */
#line 118 "limbaj.y"
                                                 {
    // Code to handle assignment statements
    // You can generate C++ code for the assignment
}
#line 1309 "limbaj.tab.c"
    break;

  case 37: /* if_statement: IF '(' expr ')' '{' statements '}'  */
#line 134 "limbaj.y"
                                                 {
    // Code to handle if statements
    // You can generate C++ code for the if statement
}
#line 1318 "limbaj.tab.c"
    break;

  case 38: /* for_statement: FOR '(' assignment_statement ';' expr ';' assignment_statement ')' '{' statements '}'  */
#line 139 "limbaj.y"
                                                                                                     {
    // Code to handle for statements
    // You can generate C++ code for the for statement
}
#line 1327 "limbaj.tab.c"
    break;

  case 39: /* while_statement: WHILE '(' expr ')' '{' statements '}'  */
#line 144 "limbaj.y"
                                                       {
    // Code to handle while statements
    // You can generate C++ code for the while statement
}
#line 1336 "limbaj.tab.c"
    break;

  case 44: /* arguments_list: expr  */
#line 157 "limbaj.y"
                     {cout << "Expression value: " << (yyvsp[0].floatValue) << endl;}
#line 1342 "limbaj.tab.c"
    break;

  case 45: /* arguments_list: arguments_list ',' expr  */
#line 158 "limbaj.y"
                                          { cout << "Expression value: " << (yyvsp[0].floatValue) << endl;}
#line 1348 "limbaj.tab.c"
    break;

  case 46: /* expr: NOT T  */
#line 161 "limbaj.y"
            { (yyval.floatValue) = !((yyvsp[0].floatValue)); cout << "!" << endl; }
#line 1354 "limbaj.tab.c"
    break;

  case 47: /* expr: T  */
#line 162 "limbaj.y"
        { (yyval.floatValue) = (yyvsp[0].floatValue);}
#line 1360 "limbaj.tab.c"
    break;

  case 48: /* T: T EQ F  */
#line 164 "limbaj.y"
           { (yyval.floatValue) = ((yyvsp[-2].floatValue) == (yyvsp[0].floatValue)); cout << "e == e" << ": " <<(yyval.floatValue) <<endl; }
#line 1366 "limbaj.tab.c"
    break;

  case 49: /* T: T NEQ F  */
#line 165 "limbaj.y"
              { (yyval.floatValue) = ((yyvsp[-2].floatValue) != (yyvsp[0].floatValue)); cout << "e != e" << ": " <<(yyval.floatValue) <<endl; }
#line 1372 "limbaj.tab.c"
    break;

  case 50: /* T: F  */
#line 166 "limbaj.y"
        { (yyval.floatValue) = (yyvsp[0].floatValue);}
#line 1378 "limbaj.tab.c"
    break;

  case 51: /* F: F LT G  */
#line 168 "limbaj.y"
           { (yyval.floatValue) = ((yyvsp[-2].floatValue) < (yyvsp[0].floatValue)); cout << "e < e" << ": " <<(yyval.floatValue) <<endl; }
#line 1384 "limbaj.tab.c"
    break;

  case 52: /* F: F LE G  */
#line 169 "limbaj.y"
             { (yyval.floatValue) = ((yyvsp[-2].floatValue) <= (yyvsp[0].floatValue)); cout << "e <= e" << ": " <<(yyval.floatValue) <<endl; }
#line 1390 "limbaj.tab.c"
    break;

  case 53: /* F: F GT G  */
#line 170 "limbaj.y"
             { (yyval.floatValue) = ((yyvsp[-2].floatValue) > (yyvsp[0].floatValue)); cout << "e > e" << ": " <<(yyval.floatValue) <<endl; }
#line 1396 "limbaj.tab.c"
    break;

  case 54: /* F: F GE G  */
#line 171 "limbaj.y"
             { (yyval.floatValue) = ((yyvsp[-2].floatValue) >= (yyvsp[0].floatValue)); cout << "e >= e" << ": " <<(yyval.floatValue) <<endl; }
#line 1402 "limbaj.tab.c"
    break;

  case 55: /* F: G  */
#line 172 "limbaj.y"
        { (yyval.floatValue) = (yyvsp[0].floatValue);}
#line 1408 "limbaj.tab.c"
    break;

  case 56: /* G: G PLUS H  */
#line 174 "limbaj.y"
             { (yyval.floatValue) = ((yyvsp[-2].floatValue) + (yyvsp[0].floatValue)); cout << "e + e" << " : " <<(yyval.floatValue) <<endl; }
#line 1414 "limbaj.tab.c"
    break;

  case 57: /* G: G MINUS H  */
#line 175 "limbaj.y"
                { (yyval.floatValue) = ((yyvsp[-2].floatValue) - (yyvsp[0].floatValue)); cout << "e - e" << " : " <<(yyval.floatValue) <<endl; }
#line 1420 "limbaj.tab.c"
    break;

  case 58: /* G: H  */
#line 176 "limbaj.y"
        { (yyval.floatValue) = (yyvsp[0].floatValue);}
#line 1426 "limbaj.tab.c"
    break;

  case 59: /* H: H MUL I  */
#line 178 "limbaj.y"
            { (yyval.floatValue) = ((yyvsp[-2].floatValue) * (yyvsp[0].floatValue)); cout << "e * e" << " : " <<(yyval.floatValue) <<endl; }
#line 1432 "limbaj.tab.c"
    break;

  case 60: /* H: H DIV I  */
#line 179 "limbaj.y"
              { (yyval.floatValue) = ((yyvsp[-2].floatValue) / (yyvsp[0].floatValue)); cout << "e / e" << " : " <<(yyval.floatValue) <<endl; }
#line 1438 "limbaj.tab.c"
    break;

  case 61: /* H: H MOD I  */
#line 180 "limbaj.y"
              { (yyval.floatValue) = (float)((int)(yyvsp[-2].floatValue) % (int)(yyvsp[0].floatValue)); cout << "e % e" << " : " <<(yyval.floatValue) <<endl; }
#line 1444 "limbaj.tab.c"
    break;

  case 62: /* H: I  */
#line 181 "limbaj.y"
        { (yyval.floatValue) = (yyvsp[0].floatValue);}
#line 1450 "limbaj.tab.c"
    break;

  case 63: /* I: I AND J  */
#line 183 "limbaj.y"
            { (yyval.floatValue) = ((yyvsp[-2].floatValue) && (yyvsp[0].floatValue)); cout << "e && e" << " : " <<(yyval.floatValue) <<endl; }
#line 1456 "limbaj.tab.c"
    break;

  case 64: /* I: I OR J  */
#line 184 "limbaj.y"
             { (yyval.floatValue) = ((yyvsp[-2].floatValue) || (yyvsp[0].floatValue)); cout << "e || e" << " : " <<(yyval.floatValue) <<endl; }
#line 1462 "limbaj.tab.c"
    break;

  case 65: /* I: J  */
#line 185 "limbaj.y"
        { (yyval.floatValue) = (yyvsp[0].floatValue);}
#line 1468 "limbaj.tab.c"
    break;

  case 66: /* J: INT  */
#line 188 "limbaj.y"
         { (yyval.floatValue) = (yyvsp[0].intValue); cout << "e->" <<(yyvsp[0].intValue)<< " : " <<(yyval.floatValue) <<endl; }
#line 1474 "limbaj.tab.c"
    break;

  case 67: /* J: FLOAT  */
#line 189 "limbaj.y"
            { (yyval.floatValue) = (yyvsp[0].floatValue); cout << "e->" <<(yyvsp[0].floatValue)<< " : " <<(yyval.floatValue) <<endl; }
#line 1480 "limbaj.tab.c"
    break;

  case 68: /* J: BOOL  */
#line 190 "limbaj.y"
           { (yyval.floatValue) = (yyvsp[0].boolValue); cout << "e->" <<(yyvsp[0].boolValue)<< " : " <<(yyval.floatValue) <<endl; }
#line 1486 "limbaj.tab.c"
    break;

  case 69: /* J: '(' expr ')'  */
#line 191 "limbaj.y"
                   { (yyval.floatValue) = (yyvsp[-1].floatValue); cout << "e->(e)" <<(yyvsp[-1].floatValue)<< " : " <<(yyval.floatValue) <<endl; }
#line 1492 "limbaj.tab.c"
    break;


#line 1496 "limbaj.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= DIV)
        {
          /* Return failure if at end of input.  */
          if (yychar == DIV)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
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
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 196 "limbaj.y"


// // Function to evaluate expressions
// void Eval(arg) {
//     // Code to evaluate expressions
//     // You can generate C++ code for evaluating the expression
// }

// // Function to get the type of an expression
// void TypeOf(arg) {
//     // Code to get the type of an expression
//     // You can generate C++ code for getting the type
// }

// // Function to handle global function calls
// void globalFunction(int param) {
//     // Code to handle global function calls
//     // You can generate C++ code for the function call
// }

void yyerror(const char * s){
    printf("error: %s at line:%d\n",s,yylineno);
}

int main(int argc, char** argv){
     yyin=fopen(argv[1],"r");
     yyparse();
    
} 
