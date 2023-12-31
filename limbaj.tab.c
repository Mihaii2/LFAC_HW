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
#include <unistd.h>
#include <fcntl.h>
#include <string>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <cmath>
#include <variant>
using namespace std;
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);

class ASTNode;

class VarInfo {
private:
    string type;
    string name;
    bool isConst = false;
    int size = 0;
    void* memoryLocation = nullptr;

public:

    VarInfo() {}
    VarInfo(string type, string name, bool is_const = false, int arraySize = 1, void* value = nullptr);
    string getName() const { return name; }
    string getType() const { return type; }
    void setValue(void* value);
    void setSize(int size); 
    int getSize() const { return this->size; }
    void* getValueCopy();
    void assign_expr(ASTNode* expr);
    void write_to_string(string &str) const;
    void printMembers();

};
class FunctionInfo {
private:
    string type;
    string name;
    vector<VarInfo> params;
public:
    FunctionInfo() {}
    FunctionInfo(string type, string name, vector<VarInfo> params);
    string getName() const { return name; }
    string getType() const { return type; }
    void write_to_string(string &str) const;
};

class UserType {
private:
    string name;
    vector<VarInfo> vars;
    vector<FunctionInfo> methods;
public:

    UserType() {}
    UserType(string name, vector<VarInfo> vars, vector<FunctionInfo> methods);
    void addVar(const char* type, const char* name, const char* scope);
    void addMethod(const char* type, const char* name, const char* scope);
    void printMembers();
    string getName() const { return name; }
    vector<VarInfo> getVars() const { return vars; }
};


class SymbolTable {
private:
    unordered_map<string, unordered_map<string, VarInfo>> variables;
    unordered_map<string, unordered_map<string, FunctionInfo>> functions;
    vector<string> current_scope;

public:
    void enterScope(const std::string& scopeName);
    void exitScope();
    string getCurrentScope();
    void addVariable(VarInfo var);
    void addFunction(FunctionInfo func);
    bool variableExists(const string& name);
    bool functionExists(const string& name);
    VarInfo getVariable(const string& name);
    FunctionInfo getFunction(const string& name);
    void printTable();
    void saveInFile();
};

#include <variant>
#include <tuple>

enum class ExprType {
    FLOAT,
    INT,
    BOOLEAN,
    STRING,
    CHAR,
    FUNCTION,
};

class ASTNode {
public:
    using ReturnValue = variant<int, float, bool>;

    virtual ~ASTNode() {}
    virtual ReturnValue evaluate() const = 0;
    virtual ExprType type() const = 0;

    virtual bool isLeaf() const { return false; }
    virtual void* getLeafValueCopy() const { return nullptr; }
};


class FloatNode : public ASTNode {
private:
    float value;

public:
    FloatNode(float val) : value(val) {}
    ReturnValue evaluate() const override { return ReturnValue(value); }
    ExprType type() const override { return ExprType::FLOAT; }
};

class IntNode : public ASTNode {
private:
    int value;

public:
    IntNode(int val) : value(val) {}
    ReturnValue evaluate() const override { return ReturnValue(value); }
    ExprType type() const override { return ExprType::INT; }
};

class BoolNode : public ASTNode {
private:
    bool value;

public:
    BoolNode(bool val) : value(val) {}
    ReturnValue evaluate() const override { return ReturnValue(value); }
    ExprType type() const override { return ExprType::BOOLEAN; }
};

class CharNode : public ASTNode {
private:
    char value;
public:
    CharNode(char val) : value(val) {}

    bool isLeaf() const override { return true; }
    void* getLeafValueCopy() const override { return new char(value); }

    ReturnValue evaluate() const override { return ReturnValue(0); }
    ExprType type() const override { return ExprType::CHAR; }
};

class StringNode : public ASTNode {
private:
    char* value;
public:
    StringNode(char* val) : value(val) {}

    bool isLeaf() const override { return true; }
    void* getLeafValueCopy() const override {
        char* copy = new char[strlen(value) + 1];
        strcpy(copy, value);
        return copy;
    }

    ReturnValue evaluate() const override { return ReturnValue(0); }

    ExprType type() const override { return ExprType::STRING; }
};

class IdentifierNode : public ASTNode {
private:
    std::string name;

public:
    IdentifierNode(const std::string& id) : name(id) {}

    ReturnValue evaluate() const override {
        // Implement logic to get the value of the identifier
        // and return it
        return ReturnValue(0.0f); // Placeholder value, replace with actual logic
    }

    ExprType type() const override {
        // Implement logic to get the type of the identifier
        // and return it
        return ExprType::FLOAT; // Placeholder value, replace with actual logic
    }
};

class FunctionCallNode : public ASTNode {
private:

public:
    FunctionCallNode() {}

    ReturnValue evaluate() const override {
        return ReturnValue(0);
    }

    ExprType type() const override {
        // implement logic to get return type of the function
        return ExprType::INT; // Placeholder value, replace with actual logic
    }
};

class VectorElementNode : public ASTNode {
private:
    const ASTNode* vector;
    const ASTNode* index;

public:
    VectorElementNode(const ASTNode* vec, const ASTNode* idx)
        : vector(vec), index(idx) {}

    ReturnValue evaluate() const override {
        // Implement logic to get the value of the vector element
        // and return it
        return variant<int, float, bool>(0.0f); // Placeholder value, replace with actual logic
    }

    ExprType type() const override {
        // Implement logic to get the type of the vector element
        // and return it
        return ExprType::FLOAT; // Placeholder value, replace with actual logic
    }
};

class BinaryOpNode : public ASTNode {
private:
    char op;
    const ASTNode* left;
    const ASTNode* right;

public:
    BinaryOpNode(char oper, const ASTNode* l, const ASTNode* r)
        : op(oper), left(l), right(r) {}

    ReturnValue evaluate() const override;

    ExprType type() const override;
};

SymbolTable symbolTable;
vector<UserType> userTypes;
unsigned long long ifCounter = 0;
unsigned long long forCounter = 0;
unsigned long long whileCounter = 0;

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


#line 341 "limbaj.tab.c"

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
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_INT = 3,                        /* INT  */
  YYSYMBOL_FLOAT = 4,                      /* FLOAT  */
  YYSYMBOL_CHAR = 5,                       /* CHAR  */
  YYSYMBOL_STRING = 6,                     /* STRING  */
  YYSYMBOL_BOOL = 7,                       /* BOOL  */
  YYSYMBOL_ID = 8,                         /* ID  */
  YYSYMBOL_TYPE = 9,                       /* TYPE  */
  YYSYMBOL_SPECIAL_FUNCTION = 10,          /* SPECIAL_FUNCTION  */
  YYSYMBOL_IF = 11,                        /* IF  */
  YYSYMBOL_WHILE = 12,                     /* WHILE  */
  YYSYMBOL_FOR = 13,                       /* FOR  */
  YYSYMBOL_END_USR_TYPES = 14,             /* END_USR_TYPES  */
  YYSYMBOL_END_USR_TYPE_VARS = 15,         /* END_USR_TYPE_VARS  */
  YYSYMBOL_END_GLOBAL_VARS = 16,           /* END_GLOBAL_VARS  */
  YYSYMBOL_END_GLOBAL_FUNCS = 17,          /* END_GLOBAL_FUNCS  */
  YYSYMBOL_CONST = 18,                     /* CONST  */
  YYSYMBOL_USR_TYPE = 19,                  /* USR_TYPE  */
  YYSYMBOL_EVAL = 20,                      /* EVAL  */
  YYSYMBOL_TYPEOF = 21,                    /* TYPEOF  */
  YYSYMBOL_NOT = 22,                       /* NOT  */
  YYSYMBOL_EQ = 23,                        /* EQ  */
  YYSYMBOL_NEQ = 24,                       /* NEQ  */
  YYSYMBOL_LT = 25,                        /* LT  */
  YYSYMBOL_LE = 26,                        /* LE  */
  YYSYMBOL_GT = 27,                        /* GT  */
  YYSYMBOL_GE = 28,                        /* GE  */
  YYSYMBOL_ASSIGN = 29,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 30,                      /* PLUS  */
  YYSYMBOL_MINUS = 31,                     /* MINUS  */
  YYSYMBOL_MUL = 32,                       /* MUL  */
  YYSYMBOL_DIV = 33,                       /* DIV  */
  YYSYMBOL_MOD = 34,                       /* MOD  */
  YYSYMBOL_AND = 35,                       /* AND  */
  YYSYMBOL_OR = 36,                        /* OR  */
  YYSYMBOL_GEQ = 37,                       /* GEQ  */
  YYSYMBOL_LEQ = 38,                       /* LEQ  */
  YYSYMBOL_39_ = 39,                       /* '{'  */
  YYSYMBOL_40_ = 40,                       /* '}'  */
  YYSYMBOL_41_ = 41,                       /* ';'  */
  YYSYMBOL_42_ = 42,                       /* '('  */
  YYSYMBOL_43_ = 43,                       /* ')'  */
  YYSYMBOL_44_ = 44,                       /* '['  */
  YYSYMBOL_45_ = 45,                       /* ']'  */
  YYSYMBOL_46_ = 46,                       /* ','  */
  YYSYMBOL_YYACCEPT = 47,                  /* $accept  */
  YYSYMBOL_program = 48,                   /* program  */
  YYSYMBOL_user_defined_types = 49,        /* user_defined_types  */
  YYSYMBOL_user_defined_type = 50,         /* user_defined_type  */
  YYSYMBOL_51_1 = 51,                      /* $@1  */
  YYSYMBOL_52_2 = 52,                      /* $@2  */
  YYSYMBOL_usr_type_vars = 53,             /* usr_type_vars  */
  YYSYMBOL_usr_type_var = 54,              /* usr_type_var  */
  YYSYMBOL_usr_type_methods = 55,          /* usr_type_methods  */
  YYSYMBOL_usr_type_method = 56,           /* usr_type_method  */
  YYSYMBOL_57_3 = 57,                      /* $@3  */
  YYSYMBOL_58_4 = 58,                      /* $@4  */
  YYSYMBOL_declarations = 59,              /* declarations  */
  YYSYMBOL_decl = 60,                      /* decl  */
  YYSYMBOL_global_function_definitions = 61, /* global_function_definitions  */
  YYSYMBOL_global_function_definition = 62, /* global_function_definition  */
  YYSYMBOL_63_5 = 63,                      /* $@5  */
  YYSYMBOL_64_6 = 64,                      /* $@6  */
  YYSYMBOL_func_param = 65,                /* func_param  */
  YYSYMBOL_list_param = 66,                /* list_param  */
  YYSYMBOL_param = 67,                     /* param  */
  YYSYMBOL_statements = 68,                /* statements  */
  YYSYMBOL_statement = 69,                 /* statement  */
  YYSYMBOL_assignment_statement = 70,      /* assignment_statement  */
  YYSYMBOL_left_value = 71,                /* left_value  */
  YYSYMBOL_array_element_access = 72,      /* array_element_access  */
  YYSYMBOL_control_statement = 73,         /* control_statement  */
  YYSYMBOL_if_statement = 74,              /* if_statement  */
  YYSYMBOL_75_7 = 75,                      /* $@7  */
  YYSYMBOL_for_statement = 76,             /* for_statement  */
  YYSYMBOL_77_8 = 77,                      /* $@8  */
  YYSYMBOL_while_statement = 78,           /* while_statement  */
  YYSYMBOL_79_9 = 79,                      /* $@9  */
  YYSYMBOL_function_call = 80,             /* function_call  */
  YYSYMBOL_arguments = 81,                 /* arguments  */
  YYSYMBOL_arg_list = 82,                  /* arg_list  */
  YYSYMBOL_expressions = 83,               /* expressions  */
  YYSYMBOL_eval_statement = 84,            /* eval_statement  */
  YYSYMBOL_type_of_statement = 85,         /* type_of_statement  */
  YYSYMBOL_expr = 86,                      /* expr  */
  YYSYMBOL_e_bool = 87,                    /* e_bool  */
  YYSYMBOL_special_function = 88,          /* special_function  */
  YYSYMBOL_89_10 = 89                      /* $@10  */
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

#if 1

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
#endif /* 1 */

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   302

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  47
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  43
/* YYNRULES -- Number of rules.  */
#define YYNRULES  88
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  196

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   293


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
      42,    43,     2,     2,    46,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    41,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    45,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,    40,     2,     2,     2,     2,
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
      35,    36,    37,    38
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   327,   327,   329,   330,   333,   333,   333,   339,   342,
     349,   355,   358,   365,   365,   365,   371,   372,   375,   380,
     385,   402,   409,   415,   431,   432,   435,   435,   435,   442,
     445,   450,   455,   462,   468,   469,   472,   473,   474,   475,
     476,   477,   480,   482,   483,   486,   489,   490,   491,   494,
     494,   496,   499,   499,   502,   502,   505,   508,   509,   512,
     513,   514,   517,   518,   521,   544,   573,   574,   575,   576,
     577,   578,   579,   580,   581,   582,   583,   585,   588,   589,
     590,   591,   592,   593,   594,   595,   596,   599,   599
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "INT", "FLOAT", "CHAR",
  "STRING", "BOOL", "ID", "TYPE", "SPECIAL_FUNCTION", "IF", "WHILE", "FOR",
  "END_USR_TYPES", "END_USR_TYPE_VARS", "END_GLOBAL_VARS",
  "END_GLOBAL_FUNCS", "CONST", "USR_TYPE", "EVAL", "TYPEOF", "NOT", "EQ",
  "NEQ", "LT", "LE", "GT", "GE", "ASSIGN", "PLUS", "MINUS", "MUL", "DIV",
  "MOD", "AND", "OR", "GEQ", "LEQ", "'{'", "'}'", "';'", "'('", "')'",
  "'['", "']'", "','", "$accept", "program", "user_defined_types",
  "user_defined_type", "$@1", "$@2", "usr_type_vars", "usr_type_var",
  "usr_type_methods", "usr_type_method", "$@3", "$@4", "declarations",
  "decl", "global_function_definitions", "global_function_definition",
  "$@5", "$@6", "func_param", "list_param", "param", "statements",
  "statement", "assignment_statement", "left_value",
  "array_element_access", "control_statement", "if_statement", "$@7",
  "for_statement", "$@8", "while_statement", "$@9", "function_call",
  "arguments", "arg_list", "expressions", "eval_statement",
  "type_of_statement", "expr", "e_bool", "special_function", "$@10", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-116)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -116,    39,    -5,  -116,    -8,    41,  -116,    55,    57,     2,
      52,    31,    18,    98,  -116,    53,  -116,  -116,     0,   104,
      82,    42,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,
       0,   266,    77,     0,   116,   115,  -116,     4,    83,     0,
       0,     0,     0,     0,   114,   266,    91,   102,  -116,   137,
    -116,   106,  -116,    86,    86,  -116,  -116,  -116,   113,   147,
     118,  -116,     8,  -116,     0,   149,   121,   112,  -116,   120,
     157,  -116,  -116,    35,   266,  -116,   133,   147,  -116,   131,
    -116,  -116,     0,  -116,  -116,  -116,   147,   266,  -116,    32,
     132,    65,    40,   135,   144,   145,   146,   152,  -116,   148,
    -116,  -116,   162,  -116,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,   156,  -116,    23,     0,    29,     0,   166,     0,     0,
    -116,     0,  -116,  -116,   160,  -116,   161,   159,   266,    24,
      29,   190,    44,   216,   163,   169,   230,   235,    58,  -116,
     170,     0,  -116,   211,    99,     0,     0,     0,     0,     0,
       0,   164,    29,    29,   180,   186,     0,   185,   189,  -116,
     128,  -116,   266,  -116,   266,   266,   266,   266,   266,   266,
    -116,   256,  -116,  -116,  -116,  -116,   261,  -116,  -116,  -116,
    -116,   142,  -116,   166,  -116,   158,  -116,   172,   184,  -116,
    -116,   192,  -116,  -116,   188,  -116
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,     4,     0,     0,     0,
       0,     0,    18,     0,    24,     0,    16,     5,     0,     0,
      19,     0,    17,     8,    72,    73,    74,    76,    75,    71,
       0,    20,     0,     0,     0,     0,    25,     0,     0,     0,
       0,     0,     0,     0,    22,    21,     0,     0,     2,     0,
      11,     0,    77,    66,    67,    68,    69,    70,     0,    29,
       0,    10,     0,     9,     0,     0,     0,    30,    31,     0,
       0,     6,    12,     0,    62,    33,     0,     0,    87,     0,
       7,    23,     0,    26,    32,    34,    29,    63,    34,     0,
       0,     0,    43,     0,     0,     0,     0,     0,    88,     0,
      35,    36,     0,    44,    38,    46,    47,    48,    39,    40,
      41,     0,    27,    57,     0,     0,     0,     0,     0,     0,
      37,     0,    13,    28,    71,    60,     0,    58,    59,     0,
       0,     0,     0,     0,    43,     0,     0,     0,     0,    34,
       0,     0,    45,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    42,
       0,    56,    61,    86,    78,    79,    80,    81,    82,    83,
      49,     0,    84,    85,    34,    54,     0,    64,    65,    14,
      34,     0,    34,     0,    15,     0,    51,     0,     0,    50,
      55,     0,    52,    34,     0,    53
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,  -116,   100,  -116,  -116,  -116,  -116,   143,  -116,
     155,   -72,  -116,  -115,  -116,  -116,  -116,  -116,  -116,  -116,
    -116,  -116,  -116,   127,  -116,  -116,  -116,  -116,  -116,   -18,
     -92,  -116,  -116
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     6,    23,    80,    37,    51,    62,    72,
     139,   184,     9,    99,    21,    36,    88,   123,    66,    67,
      68,    89,   100,   101,   102,   103,   104,   105,   180,   106,
     193,   107,   182,   108,   126,   127,    73,   109,   110,   171,
     132,    48,    85
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      31,     7,   135,    24,    25,    26,    27,    28,    29,     4,
       8,     7,    38,    49,     5,    45,    91,    70,    14,    50,
       8,    53,    54,    55,    56,    57,    24,    25,    26,    27,
      28,   124,    24,    25,    26,    27,    28,    29,   144,     3,
      92,     7,    30,    93,    94,    95,    74,    18,    71,    11,
       8,    34,    96,    97,    39,    40,    41,    42,    43,    35,
     172,   173,    19,    12,    87,    30,    13,   160,   188,   142,
      17,   130,    98,    92,     7,    81,    93,    94,    95,   152,
     153,    82,   113,     8,   114,    96,    97,   154,    39,    40,
      41,    42,    43,    16,    22,   128,   129,   131,   133,   159,
     136,   137,   181,   138,    10,   112,    20,    32,   185,    15,
     187,    33,   143,    39,    40,    41,    42,    43,    41,    42,
      43,   194,    44,   162,    46,    47,    52,   164,   165,   166,
     167,   168,   169,    59,   152,   153,    92,     7,   176,    93,
      94,    95,   163,    58,    60,    61,     8,    63,    96,    97,
      92,     7,    64,    93,    94,    95,    65,    75,    77,    78,
       8,    69,    96,    97,    76,    79,    92,     7,   179,    93,
      94,    95,    83,    86,   134,   111,     8,   115,    96,    97,
      92,     7,   186,    93,    94,    95,   116,   117,   118,   120,
       8,   121,    96,    97,   119,   122,    92,     7,   189,    93,
      94,    95,   113,   170,   140,   141,     8,   114,    96,    97,
     156,   161,   190,   145,   146,   147,   148,   149,   150,   174,
      39,    40,    41,    42,    43,   175,   177,   191,   195,    90,
     178,   192,    84,   151,   145,   146,   147,   148,   149,   150,
     125,    39,    40,    41,    42,    43,    39,    40,    41,    42,
      43,     0,     0,     0,    52,     0,     0,     0,     0,   155,
      39,    40,    41,    42,    43,    39,    40,    41,    42,    43,
       0,     0,     0,   157,     0,     0,     0,     0,   158,   145,
     146,   147,   148,   149,   150,     0,    39,    40,    41,    42,
      43,    39,    40,    41,    42,    43,    39,    40,    41,    42,
      43,     0,   183
};

static const yytype_int16 yycheck[] =
{
      18,     9,   117,     3,     4,     5,     6,     7,     8,    14,
      18,     9,    30,     9,    19,    33,    88,     9,    16,    15,
      18,    39,    40,    41,    42,    43,     3,     4,     5,     6,
       7,     8,     3,     4,     5,     6,     7,     8,   130,     0,
       8,     9,    42,    11,    12,    13,    64,    29,    40,     8,
      18,     9,    20,    21,    30,    31,    32,    33,    34,    17,
     152,   153,    44,     8,    82,    42,     9,   139,   183,    45,
      39,    42,    40,     8,     9,    40,    11,    12,    13,    35,
      36,    46,    42,    18,    44,    20,    21,    43,    30,    31,
      32,    33,    34,    41,    41,   113,   114,   115,   116,    41,
     118,   119,   174,   121,     4,    40,     8,     3,   180,     9,
     182,    29,   130,    30,    31,    32,    33,    34,    32,    33,
      34,   193,    45,   141,     8,    10,    43,   145,   146,   147,
     148,   149,   150,    42,    35,    36,     8,     9,   156,    11,
      12,    13,    43,    29,    42,     8,    18,    41,    20,    21,
       8,     9,    39,    11,    12,    13,     9,     8,    46,    39,
      18,    43,    20,    21,    43,     8,     8,     9,    40,    11,
      12,    13,    39,    42,     8,    43,    18,    42,    20,    21,
       8,     9,    40,    11,    12,    13,    42,    42,    42,    41,
      18,    29,    20,    21,    42,    39,     8,     9,    40,    11,
      12,    13,    42,    39,    43,    46,    18,    44,    20,    21,
      41,    41,    40,    23,    24,    25,    26,    27,    28,    39,
      30,    31,    32,    33,    34,    39,    41,    43,    40,    86,
      41,    39,    77,    43,    23,    24,    25,    26,    27,    28,
     113,    30,    31,    32,    33,    34,    30,    31,    32,    33,
      34,    -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    43,
      30,    31,    32,    33,    34,    30,    31,    32,    33,    34,
      -1,    -1,    -1,    43,    -1,    -1,    -1,    -1,    43,    23,
      24,    25,    26,    27,    28,    -1,    30,    31,    32,    33,
      34,    30,    31,    32,    33,    34,    30,    31,    32,    33,
      34,    -1,    41
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    48,    49,     0,    14,    19,    50,     9,    18,    59,
      60,     8,     8,     9,    16,    60,    41,    39,    29,    44,
       8,    61,    41,    51,     3,     4,     5,     6,     7,     8,
      42,    86,     3,    29,     9,    17,    62,    53,    86,    30,
      31,    32,    33,    34,    45,    86,     8,    10,    88,     9,
      15,    54,    43,    86,    86,    86,    86,    86,    29,    42,
      42,     8,    55,    41,    39,     9,    65,    66,    67,    43,
       9,    40,    56,    83,    86,     8,    43,    46,    39,     8,
      52,    40,    46,    39,    67,    89,    42,    86,    63,    68,
      65,    68,     8,    11,    12,    13,    20,    21,    40,    60,
      69,    70,    71,    72,    73,    74,    76,    78,    80,    84,
      85,    43,    40,    42,    44,    42,    42,    42,    42,    42,
      41,    29,    39,    64,     8,    80,    81,    82,    86,    86,
      42,    86,    87,    86,     8,    70,    86,    86,    86,    57,
      43,    46,    45,    86,    87,    23,    24,    25,    26,    27,
      28,    43,    35,    36,    43,    43,    41,    43,    43,    41,
      68,    41,    86,    43,    86,    86,    86,    86,    86,    86,
      39,    86,    87,    87,    39,    39,    86,    41,    41,    40,
      75,    68,    79,    41,    58,    68,    40,    68,    70,    40,
      40,    43,    39,    77,    68,    40
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    47,    48,    49,    49,    51,    52,    50,    53,    53,
      54,    55,    55,    57,    58,    56,    59,    59,    60,    60,
      60,    60,    60,    60,    61,    61,    63,    64,    62,    65,
      65,    66,    66,    67,    68,    68,    69,    69,    69,    69,
      69,    69,    70,    71,    71,    72,    73,    73,    73,    75,
      74,    74,    77,    76,    79,    78,    80,    81,    81,    82,
      82,    82,    83,    83,    84,    85,    86,    86,    86,    86,
      86,    86,    86,    86,    86,    86,    86,    86,    87,    87,
      87,    87,    87,    87,    87,    87,    87,    89,    88
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     7,     0,     2,     0,     0,     9,     0,     3,
       2,     0,     2,     0,     0,    10,     2,     3,     2,     3,
       4,     5,     5,     9,     0,     2,     0,     0,    10,     0,
       1,     1,     3,     2,     0,     2,     1,     2,     1,     1,
       1,     1,     4,     1,     1,     4,     1,     1,     1,     0,
       8,     7,     0,    12,     0,     8,     5,     0,     1,     1,
       1,     3,     1,     3,     5,     5,     3,     3,     3,     3,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     7
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


/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  int yyn = yypact[+*yyctx->yyssp];
  if (!yypact_value_is_default (yyn))
    {
      /* Start YYX at -YYN if negative to avoid negative indexes in
         YYCHECK.  In other words, skip the first -YYN actions for
         this state because they are default actions.  */
      int yyxbegin = yyn < 0 ? -yyn : 0;
      /* Stay within bounds of both yycheck and yytname.  */
      int yychecklim = YYLAST - yyn + 1;
      int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
      int yyx;
      for (yyx = yyxbegin; yyx < yyxend; ++yyx)
        if (yycheck[yyx + yyn] == yyx && yyx != YYSYMBOL_YYerror
            && !yytable_value_is_error (yytable[yyx + yyn]))
          {
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = YY_CAST (yysymbol_kind_t, yyx);
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


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

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

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

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
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
  case 2: /* program: user_defined_types END_USR_TYPES declarations END_GLOBAL_VARS global_function_definitions END_GLOBAL_FUNCS special_function  */
#line 327 "limbaj.y"
                                                                                                                                     {printf("The programm is correct!\n");}
#line 1840 "limbaj.tab.c"
    break;

  case 5: /* $@1: %empty  */
#line 333 "limbaj.y"
                                   {symbolTable.enterScope(string((yyvsp[-1].string)));}
#line 1846 "limbaj.tab.c"
    break;

  case 6: /* $@2: %empty  */
#line 333 "limbaj.y"
                                                                                                                              { symbolTable.exitScope();}
#line 1852 "limbaj.tab.c"
    break;

  case 7: /* user_defined_type: USR_TYPE ID '{' $@1 usr_type_vars END_USR_TYPE_VARS usr_type_methods '}' $@2  */
#line 333 "limbaj.y"
                                                                                                                                                          {
                        UserType userType = UserType((yyvsp[-7].string), *(yyvsp[-4].vars), *(yyvsp[-2].funcs));
                        userTypes.push_back(userType);
                    }
#line 1861 "limbaj.tab.c"
    break;

  case 8: /* usr_type_vars: %empty  */
#line 339 "limbaj.y"
                             {
                    (yyval.vars) = new vector<VarInfo>();
                }
#line 1869 "limbaj.tab.c"
    break;

  case 9: /* usr_type_vars: usr_type_vars usr_type_var ';'  */
#line 342 "limbaj.y"
                                                {
                    (yyval.vars) = (yyvsp[-2].vars);
                    (yyval.vars)->push_back(*(yyvsp[-1].var));
                    delete((yyvsp[-1].var));
                }
#line 1879 "limbaj.tab.c"
    break;

  case 10: /* usr_type_var: TYPE ID  */
#line 349 "limbaj.y"
                      {
                    VarInfo* var = new VarInfo((yyvsp[-1].string), (yyvsp[0].string));
                    (yyval.var) = var;
                }
#line 1888 "limbaj.tab.c"
    break;

  case 11: /* usr_type_methods: %empty  */
#line 355 "limbaj.y"
                                {
                    (yyval.funcs) = new vector<FunctionInfo>();
                }
#line 1896 "limbaj.tab.c"
    break;

  case 12: /* usr_type_methods: usr_type_methods usr_type_method  */
#line 358 "limbaj.y"
                                                   {
                    (yyval.funcs) = (yyvsp[-1].funcs);
                    (yyval.funcs)->push_back(*(yyvsp[0].func));
                    delete((yyvsp[0].func));
                }
#line 1906 "limbaj.tab.c"
    break;

  case 13: /* $@3: %empty  */
#line 365 "limbaj.y"
                                                {symbolTable.enterScope(string((yyvsp[-4].string)));}
#line 1912 "limbaj.tab.c"
    break;

  case 14: /* $@4: %empty  */
#line 365 "limbaj.y"
                                                                                                     {symbolTable.exitScope();}
#line 1918 "limbaj.tab.c"
    break;

  case 15: /* usr_type_method: TYPE ID '(' func_param ')' '{' $@3 statements '}' $@4  */
#line 365 "limbaj.y"
                                                                                                                                {
                    FunctionInfo* func = new FunctionInfo((yyvsp[-9].string), (yyvsp[-8].string), *(yyvsp[-6].vars));
                    (yyval.func) = func;
                }
#line 1927 "limbaj.tab.c"
    break;

  case 18: /* decl: TYPE ID  */
#line 375 "limbaj.y"
              {
            VarInfo* var = new VarInfo((yyvsp[-1].string), (yyvsp[0].string));
            (yyval.var) = var;
            symbolTable.addVariable(*var);
    }
#line 1937 "limbaj.tab.c"
    break;

  case 19: /* decl: CONST TYPE ID  */
#line 380 "limbaj.y"
                    {
            VarInfo* var = new VarInfo((yyvsp[-1].string), (yyvsp[0].string), true);
            (yyval.var) = var;
            symbolTable.addVariable(*var);
    }
#line 1947 "limbaj.tab.c"
    break;

  case 20: /* decl: TYPE ID ASSIGN expr  */
#line 385 "limbaj.y"
                          {
            if((yyvsp[0].node)->isLeaf()) {
                char* value = (char*)(yyvsp[0].node)->getLeafValueCopy();
                VarInfo* var = new VarInfo((yyvsp[-3].string), (yyvsp[-2].string), false, strlen(value), value);
                (yyval.var) = var;
                symbolTable.addVariable(*var);
                free(value);
            }
            else {
                VarInfo* var = new VarInfo((yyvsp[-3].string), (yyvsp[-2].string), false);
                var->assign_expr((yyvsp[0].node));
                free((yyvsp[0].node));
                (yyval.var) = var;
                symbolTable.addVariable(*var);
            }
            
    }
#line 1969 "limbaj.tab.c"
    break;

  case 21: /* decl: CONST TYPE ID ASSIGN expr  */
#line 402 "limbaj.y"
                                { 
            VarInfo* var = new VarInfo((yyvsp[-3].string), (yyvsp[-2].string), true);
            var->assign_expr((yyvsp[0].node));
            free((yyvsp[0].node));
            (yyval.var) = var;
            symbolTable.addVariable(*var);
    }
#line 1981 "limbaj.tab.c"
    break;

  case 22: /* decl: TYPE ID '[' INT ']'  */
#line 409 "limbaj.y"
                          {
            VarInfo* var = new VarInfo((yyvsp[-4].string), (yyvsp[-3].string), false, (yyvsp[-1].intValue));
            (yyval.var) = var;
            symbolTable.addVariable(*var);

    }
#line 1992 "limbaj.tab.c"
    break;

  case 23: /* decl: TYPE ID '[' INT ']' ASSIGN '{' expressions '}'  */
#line 415 "limbaj.y"
                                                     {
            VarInfo* var = new VarInfo((yyvsp[-8].string), (yyvsp[-7].string), false, (yyvsp[-5].intValue));

            (yyval.var) = var;
            symbolTable.addVariable(*var);
    }
#line 2003 "limbaj.tab.c"
    break;

  case 26: /* $@5: %empty  */
#line 435 "limbaj.y"
                                                           {symbolTable.enterScope(string((yyvsp[-4].string)));}
#line 2009 "limbaj.tab.c"
    break;

  case 27: /* $@6: %empty  */
#line 435 "limbaj.y"
                                                                                                                {symbolTable.exitScope();}
#line 2015 "limbaj.tab.c"
    break;

  case 28: /* global_function_definition: TYPE ID '(' func_param ')' '{' $@5 statements '}' $@6  */
#line 435 "limbaj.y"
                                                                                                                                           {
                            FunctionInfo* func = new FunctionInfo((yyvsp[-9].string), (yyvsp[-8].string), *(yyvsp[-6].vars));
                            symbolTable.addFunction(*func);
                        }
#line 2024 "limbaj.tab.c"
    break;

  case 29: /* func_param: %empty  */
#line 442 "limbaj.y"
                          {
                (yyval.vars) = new vector<VarInfo>();
            }
#line 2032 "limbaj.tab.c"
    break;

  case 30: /* func_param: list_param  */
#line 445 "limbaj.y"
                         {
                (yyval.vars) = (yyvsp[0].vars);
            }
#line 2040 "limbaj.tab.c"
    break;

  case 31: /* list_param: param  */
#line 450 "limbaj.y"
                  {
                    (yyval.vars) = new vector<VarInfo>();
                    (yyval.vars)->push_back(*(yyvsp[0].var));
                    delete((yyvsp[0].var));
                }
#line 2050 "limbaj.tab.c"
    break;

  case 32: /* list_param: list_param ',' param  */
#line 455 "limbaj.y"
                                       {
                    (yyval.vars) = (yyvsp[-2].vars);
                    (yyval.vars)->push_back(*(yyvsp[0].var));
                    delete((yyvsp[0].var));
                }
#line 2060 "limbaj.tab.c"
    break;

  case 33: /* param: TYPE ID  */
#line 462 "limbaj.y"
               {
            VarInfo* var = new VarInfo((yyvsp[-1].string), (yyvsp[0].string));
            (yyval.var) = var;
        }
#line 2069 "limbaj.tab.c"
    break;

  case 49: /* $@7: %empty  */
#line 494 "limbaj.y"
                                  {symbolTable.enterScope("if" + std::to_string(ifCounter++));}
#line 2075 "limbaj.tab.c"
    break;

  case 50: /* if_statement: IF '(' expr ')' '{' $@7 statements '}'  */
#line 495 "limbaj.y"
                {symbolTable.exitScope();}
#line 2081 "limbaj.tab.c"
    break;

  case 52: /* $@8: %empty  */
#line 499 "limbaj.y"
                                                                                      { symbolTable.enterScope("for" + std::to_string(forCounter++));}
#line 2087 "limbaj.tab.c"
    break;

  case 53: /* for_statement: FOR '(' assignment_statement ';' expr ';' assignment_statement ')' '{' $@8 statements '}'  */
#line 499 "limbaj.y"
                                                                                                                                                                      {symbolTable.exitScope();}
#line 2093 "limbaj.tab.c"
    break;

  case 54: /* $@9: %empty  */
#line 502 "limbaj.y"
                                        {symbolTable.enterScope("while" + std::to_string(whileCounter++));}
#line 2099 "limbaj.tab.c"
    break;

  case 55: /* while_statement: WHILE '(' expr ')' '{' $@9 statements '}'  */
#line 502 "limbaj.y"
                                                                                                                           {symbolTable.exitScope();}
#line 2105 "limbaj.tab.c"
    break;

  case 64: /* eval_statement: EVAL '(' expr ')' ';'  */
#line 521 "limbaj.y"
                                      { 
    switch((yyvsp[-2].node)->type()) {
        case ExprType::INT:
            printf("Evaluated expression: %d\n", std::get<int>((yyvsp[-2].node)->evaluate()));
            break;
        case ExprType::FLOAT:
            printf("Evaluated expression: %f\n", std::get<float>((yyvsp[-2].node)->evaluate()));
            break;
        case ExprType::BOOLEAN:
            printf("Evaluated expression: %d\n", std::get<bool>((yyvsp[-2].node)->evaluate()));
            break;
        case ExprType::STRING:
        case ExprType::CHAR:
            printf("Evaluated expression: %d\n", 0);
            break;
        default:
            printf("Unknown type\n");
            break;
    }
    free((yyvsp[-2].node)); // free the memory allocated for the expression
 }
#line 2131 "limbaj.tab.c"
    break;

  case 65: /* type_of_statement: TYPEOF '(' expr ')' ';'  */
#line 544 "limbaj.y"
                                           { 
        switch ((yyvsp[-2].node)->type()) {
            case ExprType::INT:
                printf("Type of expression: int\n");
                break;
            case ExprType::FLOAT:
                printf("Type of expression: float\n");
                break;
            case ExprType::BOOLEAN:
                printf("Type of expression: bool\n");
                break;
            case ExprType::STRING:
                printf("Type of expression: string\n");
                break;
            case ExprType::CHAR:
                printf("Type of expression: char\n");
                break;
            case ExprType::FUNCTION:
                printf("Type of expression: function\n");
                break;
            default:
                printf("Type of expression: unknown\n");
                break;
        }
    free((yyvsp[-2].node)); // free the memory allocated for the expression
    }
#line 2162 "limbaj.tab.c"
    break;

  case 66: /* expr: expr PLUS expr  */
#line 573 "limbaj.y"
                     { (yyval.node) = new BinaryOpNode('+', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2168 "limbaj.tab.c"
    break;

  case 67: /* expr: expr MINUS expr  */
#line 574 "limbaj.y"
                      { (yyval.node) = new BinaryOpNode('-', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2174 "limbaj.tab.c"
    break;

  case 68: /* expr: expr MUL expr  */
#line 575 "limbaj.y"
                    { (yyval.node) = new BinaryOpNode('*', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2180 "limbaj.tab.c"
    break;

  case 69: /* expr: expr DIV expr  */
#line 576 "limbaj.y"
                    { (yyval.node) = new BinaryOpNode('/', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2186 "limbaj.tab.c"
    break;

  case 70: /* expr: expr MOD expr  */
#line 577 "limbaj.y"
                    { (yyval.node) = new BinaryOpNode('%', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2192 "limbaj.tab.c"
    break;

  case 71: /* expr: ID  */
#line 578 "limbaj.y"
         { (yyval.node) = new IdentifierNode((yyvsp[0].string)); }
#line 2198 "limbaj.tab.c"
    break;

  case 72: /* expr: INT  */
#line 579 "limbaj.y"
          { (yyval.node) = new IntNode((yyvsp[0].intValue)); }
#line 2204 "limbaj.tab.c"
    break;

  case 73: /* expr: FLOAT  */
#line 580 "limbaj.y"
            { (yyval.node) = new FloatNode((yyvsp[0].floatValue)); }
#line 2210 "limbaj.tab.c"
    break;

  case 74: /* expr: CHAR  */
#line 581 "limbaj.y"
           { (yyval.node) = new CharNode((yyvsp[0].charValue)); }
#line 2216 "limbaj.tab.c"
    break;

  case 75: /* expr: BOOL  */
#line 582 "limbaj.y"
           { (yyval.node) = new BoolNode((yyvsp[0].boolValue)); }
#line 2222 "limbaj.tab.c"
    break;

  case 76: /* expr: STRING  */
#line 583 "limbaj.y"
             { (yyval.node) = new StringNode((yyvsp[0].string)); }
#line 2228 "limbaj.tab.c"
    break;

  case 77: /* expr: '(' expr ')'  */
#line 585 "limbaj.y"
                   { (yyval.node) = (yyvsp[-1].node); }
#line 2234 "limbaj.tab.c"
    break;

  case 87: /* $@10: %empty  */
#line 599 "limbaj.y"
                                               { symbolTable.enterScope("clean_code_executer"); }
#line 2240 "limbaj.tab.c"
    break;

  case 88: /* special_function: SPECIAL_FUNCTION '(' ')' '{' $@10 statements '}'  */
#line 599 "limbaj.y"
                                                                                                                 { symbolTable.exitScope(); }
#line 2246 "limbaj.tab.c"
    break;


#line 2250 "limbaj.tab.c"

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
      {
        yypcontext_t yyctx
          = {yyssp, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          YYNOMEM;
      }
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
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 602 "limbaj.y"

//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////


void yyerror(const char * s){
    printf("error: %s at line:%d\n",s,yylineno);
    exit(1);
}

// SYMBOLTABLE IMPLEMENTATION

void SymbolTable::enterScope(const std::string& scopeName) {
    current_scope.push_back(scopeName);
}

void SymbolTable::exitScope() {
    current_scope.pop_back();
}

string SymbolTable::getCurrentScope() {
    // retrieve current scope from the vector of strings
    string scope = "";
    for (const string& s : current_scope) {
        scope += s;
        scope += "::";
    }
    return scope;
}

void SymbolTable::addVariable(VarInfo var) {
    variables[symbolTable.getCurrentScope()][var.getName()] = var;
}

void SymbolTable::addFunction(FunctionInfo func) {
    functions[symbolTable.getCurrentScope()][func.getName()] = func;
}

bool SymbolTable::variableExists(const string& name) {
    return variables[symbolTable.getCurrentScope()].find(name) != variables[symbolTable.getCurrentScope()].end();
}

bool SymbolTable::functionExists(const string& name) {
    return functions[symbolTable.getCurrentScope()].find(name) != functions[symbolTable.getCurrentScope()].end();
}

VarInfo SymbolTable::getVariable(const string& name) {
    return variables[symbolTable.getCurrentScope()][name];
}

FunctionInfo SymbolTable::getFunction(const string& name) {
    return functions[symbolTable.getCurrentScope()][name];
}

void SymbolTable::saveInFile() {
    int fd;
    if((fd = open("symbolTable.txt", O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1){
        perror("Eroare la open fisier symbolTable.txt\n");
    }
    std::string st_data = "-----------------Variables-----------------\n";
    for (const auto& scope : variables) {
        st_data += "--------Scope: ";
        st_data += scope.first;
        st_data += "\n";
        for (const auto& var : scope.second) {
            var.second.write_to_string(st_data);
        }
    }
    st_data += "-----------------Functions-----------------\n";
    for (const auto& scope : functions) {
        st_data += "--------Scope: ";
        st_data += scope.first;
        st_data += "\n";
        for (const auto& func : scope.second) {
            func.second.write_to_string(st_data);
        }
    }
    if(write(fd, st_data.c_str(), st_data.length()) == -1) perror("Eroare la write in fisier symbolTable.txt\n");
}

// SYMBOLTABLE IMPLEMENTATION ENDS

// USERTYPE IMPLEMENTATION

void UserType::addVar(const char* type, const char* name, const char* scope) {
    VarInfo var = VarInfo(type, name);
    vars.push_back(var);
}

void UserType::addMethod(const char* type, const char* name, const char* scope) {
    FunctionInfo method = FunctionInfo(type, name, vector<VarInfo>());
    methods.push_back(method);
}

void UserType::printMembers() {
    cout << "User type name: " << name << endl;
    cout << "Variables: " << endl;
    for (const VarInfo& v : vars) {
        std::string var_data;
        v.write_to_string(var_data);
        cout << var_data;
    }
    cout << "Methods: " << endl;
    for (const FunctionInfo& m : methods) {
        std::string method_data;
        m.write_to_string(method_data);
        cout << method_data;
    }
}

UserType::UserType(string name, vector<VarInfo> vars, vector<FunctionInfo> methods) {
    this->name = name;
    this->vars = vars;
    this->methods = methods;
}

// USERTYPE IMPLEMENTATION ENDS

// VARINFO IMPLEMENTATION

VarInfo::VarInfo(string type, string name, bool is_const, int arraySize, void* value) {
    this->type = type;
    this->name = name;
    this->isConst = is_const;
    // Deduct the size from the type
    if (type == "int" || type == "float") {
        this->size = 4;
    } 
    else if (type == "char" || type == "bool" || type == "string") {
        this->size = 1;
    }
    else {
        // User defined type
        for (const UserType& userType : userTypes) {
            if (userType.getName() == type) {
                this->size = 0;
                for (const VarInfo& v : userType.getVars()) {
                    this->size += v.size;
                }
                break;
            }
        }
    }
    // Allocate memory for the variable
    this->memoryLocation = malloc(this->size * arraySize);
    if (value != nullptr) {
        memcpy(this->memoryLocation, value, this->size * arraySize);
    }
    this->size = this->size * arraySize;
}

void VarInfo::setSize(int size) {
    free(this->memoryLocation);
    this->memoryLocation = malloc(size);
    this->size = size;
}

void VarInfo::setValue(void* value){
    this->memoryLocation = value;
}

void* VarInfo::getValueCopy(){
    void* copy = malloc(this->size);
    memcpy(copy, this->memoryLocation, this->size);
    return copy;
}

void VarInfo::write_to_string(string& str) const {
    str += "name: ";
    str += name;
    str += "\ntype: ";
    str += type;
    str += "\nconst: ";
    string is_const = std::to_string(this->isConst);
    str += is_const;
    str += "\nsize in bytes: ";
    str += std::to_string(this->size);
    str += "\nvalue: ";
    if(this->type == "int"){
        str += std::to_string(*(int*)this->memoryLocation);
    }
    else if (this->type == "char"){
        str += (char*)this->memoryLocation;
    }
    else if (this->type == "float"){
        str += std::to_string(*(float*)this->memoryLocation);
    }
    else if (this->type == "bool"){
        str += std::to_string(*(bool*)this->memoryLocation);
    }
    else if (this->type == "string"){
        str += (char*)this->memoryLocation;
    }
    str += "\n\n";
}

void VarInfo::printMembers() {
    cout << "Variable name: " << name << endl;
    cout << "Type: " << type << endl;
    cout << "Is const: " << isConst << endl;
    cout << "Size in bytes: " << size << endl;
    cout << "Value: ";
    if (type == "int") {
        cout << *(int*)memoryLocation << endl;
    }
    else if (type == "char") {
        cout << *(char*)memoryLocation << endl;
    }
    else if (type == "float") {
        cout << *(float*)memoryLocation << endl;
    }
    else if (type == "bool") {
        cout << *(bool*)memoryLocation << endl;
    }
    else if (type == "string") {
        cout << (char*)memoryLocation << endl;
    }
    cout << endl;
}

void VarInfo::assign_expr(ASTNode* expr) {
    void* value;
    switch(expr->type()) {
    case ExprType::INT: {
        this->setSize(sizeof(int));
        void* value = malloc(sizeof(int));
        int temp = std::get<int>(expr->evaluate());
        memcpy(value, &temp, sizeof(int));
        this->setValue(value);
        break;
    }
    case ExprType::FLOAT: {
        this->setSize(sizeof(float));
        void* value = malloc(sizeof(float));
        float temp2 = std::get<float>(expr->evaluate());
        memcpy(value, &temp2, sizeof(float));
        this->setValue(value);
        break;
    }
    case ExprType::BOOLEAN: {
        this->setSize(sizeof(bool));
        void* value = malloc(sizeof(bool));
        bool temp3 = std::get<bool>(expr->evaluate());
        memcpy(value, &temp3, sizeof(bool));
        this->setValue(value);
        break;
    }
    case ExprType::STRING: {
        this->setSize(1);
        break;
    }
    case ExprType::CHAR: {
        this->setSize(1);
        break;
    }
    default: {
        printf("Unknown type\n");
        break;
    }
}
}

// VARINFO IMPLEMENTATION ENDS

// FUNCTIONINFO IMPLEMENTATION

FunctionInfo::FunctionInfo(string type, string name, vector<VarInfo> params) {
    this->type = type;
    this->name = name;
    this->params = params;
}

void FunctionInfo::write_to_string(string& str) const {
    str += "name: ";
    str += name;
    str += "\ntype: ";
    str += type;
    str += "\nparams: ";
    if(params.size() != 0) {
        
        for (const VarInfo& v : params) {
            str += v.getType();
            str += " ";
            str += v.getName();
            if(&v != &params.back()) str += ", ";
        }
    }
    str += "\n\n";
}

// FUNCTIONINFO IMPLEMENTATION ENDS

// ASTNODE IMPLEMENTATION

template <typename T>
ASTNode::ReturnValue handleOperation(char op, T leftValue, T rightValue) {
    switch (op) {
        case '+':
            return ASTNode::ReturnValue(leftValue + rightValue);
        case '-':
            return ASTNode::ReturnValue(leftValue - rightValue);
        case '*':
            return ASTNode::ReturnValue(leftValue * rightValue);
        case '/':
            return ASTNode::ReturnValue(leftValue / rightValue);
        case '%':
            if constexpr (std::is_same_v<T, int>) {
                return ASTNode::ReturnValue(leftValue % rightValue);
            } else {
                yyerror("Cannot use modulo on float");
            }
            break;
        default:
            return ASTNode::ReturnValue(0);
    }
    return ASTNode::ReturnValue(0); //safety return
}

ASTNode::ReturnValue BinaryOpNode::evaluate() const {
    // Implement logic to evaluate the binary operation
    // based on the operator and return the result
    if(left->type() != right->type()) {
        yyerror("Incompatible typesss");
    }
    ExprType type = left->type();
    switch (type) {
        case ExprType::INT:
            return handleOperation(op, std::get<int>(left->evaluate()), std::get<int>(right->evaluate()));
        case ExprType::FLOAT:
            return handleOperation(op, std::get<float>(left->evaluate()), std::get<float>(right->evaluate()));
        case ExprType::BOOLEAN:
            return ReturnValue((bool)((bool)std::get<bool>(left->evaluate()) + (bool)std::get<bool>(right->evaluate())));
        case ExprType::STRING:
        case ExprType::CHAR:
            return ReturnValue(0);
        default:
            return ReturnValue(0);
    }
    return ReturnValue(0); //safety return
}

ExprType BinaryOpNode::type() const {
    if(left->type() != right->type()) {
        yyerror("Incompatible typesss");
    }
    return left->type();
}

// ASTNODE IMPLEMENTATION ENDS

int main(int argc, char** argv){
    yyin=fopen(argv[1],"r");
    yyparse();

    // Print user types
    // for (UserType& userType : userTypes) {
    //     userType.printMembers();
    // }

    // Print symbol table in file
    symbolTable.saveInFile();
}
