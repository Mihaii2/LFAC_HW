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
void error_variable_exists(const char* name);
void error_function_exists(const char* name);
void error_variable_not_found(const char* name);
void error_function_not_found(const char* name);
void error_different_types(const char* left , const char* right);
void incompatible_types(const char* left , const char* right);


class ASTNode;
class SymbolTable;
class UserType;
class VarInfo;
class FunctionInfo;

class VarInfo {
private:
    string type;
    string name;
    bool isConst = false;
    bool isUserType = false;
    int size = 0;
    void* memoryLocation = nullptr;

public:

    VarInfo() {}
    VarInfo(string type, string name, bool is_const = false, int arraySize = 1, void* value = nullptr, bool isUserType = false);
    string getName() const { return name; }
    string getType() const { return type; }
    void setValue(void* value);
    void setSize(int size); 
    int getSize() const { return this->size; }
    void* getValueReference() const;
    void assign_expr(ASTNode* expr);
    void write_to_string(string &str) const;
    void printMembers() const;

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
    std::vector<VarInfo> getParams() const { return params; }
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
    vector<FunctionInfo> getMethods() const { return methods; }
};

vector<UserType> userTypes;

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
    VarInfo& getVariableReference(const string& name);
    FunctionInfo getFunction(const string& name);
    void printTable();
    void saveInFile();
};

SymbolTable symbolTable;

enum class ExprType {
    FLOAT,
    INT,
    BOOLEAN,
    STRING,
    CHAR,
};


class ASTNode {
public:
    using ReturnValue = variant<int, float, bool, char, char**>;
    virtual ~ASTNode() {}
    virtual ReturnValue evaluate() const = 0;
    virtual ExprType type() const = 0;
    virtual string string_type() const = 0;
};

class FloatNode : public ASTNode {
private:
    float value;

public:
    FloatNode(float val) : value(val) {}
    ReturnValue evaluate() const override { return ReturnValue(value); }
    ExprType type() const override { return ExprType::FLOAT; }
    string string_type() const override { return "float"; }
};

class IntNode : public ASTNode {
private:
    int value;

public:
    IntNode(int val) : value(val) {}
    ReturnValue evaluate() const override { return ReturnValue(value); }
    ExprType type() const override { return ExprType::INT; }
    string string_type() const override { return "int"; }

};

class BoolNode : public ASTNode {
private:
    bool value;

public:
    BoolNode(bool val) : value(val) {}
    ReturnValue evaluate() const override { return ReturnValue(value); }
    ExprType type() const override { return ExprType::BOOLEAN; }
    string string_type() const override { return "bool"; }
};

class CharNode : public ASTNode {
private:
    char value;
public:
    CharNode(char val) : value(val) {}

    ReturnValue evaluate() const override { return ReturnValue(value); }
    ExprType type() const override { return ExprType::CHAR; }
    string string_type() const override { return "char"; }
};

class StringNode : public ASTNode {
private:
    char** value;
public:
    StringNode(char** val);

    ReturnValue evaluate() const override;
    ExprType type() const override { return ExprType::STRING; }
    string string_type() const override { return "string"; }
};

class IdentifierNode : public ASTNode {
private:
    std::string name;
public:
    IdentifierNode(const std::string& id) : name(id) {}
    ReturnValue evaluate() const override;
    ExprType type() const override;
    string string_type() const override;
};

class FunctionCallNode : public ASTNode {
private:
    std::string name;
    std::vector<ASTNode*>* params; //**
public:
    FunctionCallNode(string name, std::vector<ASTNode*>* args);
    ReturnValue evaluate() const override;
    ExprType type() const override;
    string string_type() const override;
};

class VectorElementNode : public ASTNode {
private:
    std::string name;
    const int index;

public:
    VectorElementNode(std::string vname, const int idx)
        : name(vname), index(idx) {}
    ReturnValue evaluate() const override;
    ExprType type() const override;
    string string_type() const override;
};

class BinaryOpNode : public ASTNode {
private:
    char op;
    const ASTNode* left;
    const ASTNode* right;

public:
    BinaryOpNode(char oper, const ASTNode* l, const ASTNode* r);
    ReturnValue evaluate() const override;
    ExprType type() const override;
    string string_type() const override;
};

unsigned long long ifCounter = 0;
unsigned long long forCounter = 0;
unsigned long long whileCounter = 0;
VarInfo DummyVarInfo = VarInfo();
FunctionInfo DummyFunctionInfo = FunctionInfo();

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


#line 320 "limbaj.tab.c"

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
  YYSYMBOL_USR_TYPE = 11,                  /* USR_TYPE  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_WHILE = 13,                     /* WHILE  */
  YYSYMBOL_FOR = 14,                       /* FOR  */
  YYSYMBOL_END_USR_TYPES = 15,             /* END_USR_TYPES  */
  YYSYMBOL_END_USR_TYPE_VARS = 16,         /* END_USR_TYPE_VARS  */
  YYSYMBOL_END_GLOBAL_VARS = 17,           /* END_GLOBAL_VARS  */
  YYSYMBOL_END_GLOBAL_FUNCS = 18,          /* END_GLOBAL_FUNCS  */
  YYSYMBOL_CONST = 19,                     /* CONST  */
  YYSYMBOL_EVAL = 20,                      /* EVAL  */
  YYSYMBOL_TYPEOF = 21,                    /* TYPEOF  */
  YYSYMBOL_RETURN = 22,                    /* RETURN  */
  YYSYMBOL_NOT = 23,                       /* NOT  */
  YYSYMBOL_EQ = 24,                        /* EQ  */
  YYSYMBOL_NEQ = 25,                       /* NEQ  */
  YYSYMBOL_LT = 26,                        /* LT  */
  YYSYMBOL_LE = 27,                        /* LE  */
  YYSYMBOL_GT = 28,                        /* GT  */
  YYSYMBOL_GE = 29,                        /* GE  */
  YYSYMBOL_ASSIGN = 30,                    /* ASSIGN  */
  YYSYMBOL_PLUS = 31,                      /* PLUS  */
  YYSYMBOL_MINUS = 32,                     /* MINUS  */
  YYSYMBOL_MUL = 33,                       /* MUL  */
  YYSYMBOL_DIV = 34,                       /* DIV  */
  YYSYMBOL_MOD = 35,                       /* MOD  */
  YYSYMBOL_AND = 36,                       /* AND  */
  YYSYMBOL_OR = 37,                        /* OR  */
  YYSYMBOL_GEQ = 38,                       /* GEQ  */
  YYSYMBOL_LEQ = 39,                       /* LEQ  */
  YYSYMBOL_40_ = 40,                       /* '{'  */
  YYSYMBOL_41_ = 41,                       /* '}'  */
  YYSYMBOL_42_ = 42,                       /* ';'  */
  YYSYMBOL_43_ = 43,                       /* '('  */
  YYSYMBOL_44_ = 44,                       /* ')'  */
  YYSYMBOL_45_ = 45,                       /* '['  */
  YYSYMBOL_46_ = 46,                       /* ']'  */
  YYSYMBOL_47_ = 47,                       /* ','  */
  YYSYMBOL_48_ = 48,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_user_defined_types = 51,        /* user_defined_types  */
  YYSYMBOL_user_defined_type = 52,         /* user_defined_type  */
  YYSYMBOL_53_1 = 53,                      /* $@1  */
  YYSYMBOL_54_2 = 54,                      /* $@2  */
  YYSYMBOL_usr_type_vars = 55,             /* usr_type_vars  */
  YYSYMBOL_usr_type_var = 56,              /* usr_type_var  */
  YYSYMBOL_usr_type_methods = 57,          /* usr_type_methods  */
  YYSYMBOL_usr_type_method = 58,           /* usr_type_method  */
  YYSYMBOL_59_3 = 59,                      /* $@3  */
  YYSYMBOL_60_4 = 60,                      /* $@4  */
  YYSYMBOL_declarations = 61,              /* declarations  */
  YYSYMBOL_decl = 62,                      /* decl  */
  YYSYMBOL_initializer_list = 63,          /* initializer_list  */
  YYSYMBOL_global_function_definitions = 64, /* global_function_definitions  */
  YYSYMBOL_global_function_definition = 65, /* global_function_definition  */
  YYSYMBOL_66_5 = 66,                      /* $@5  */
  YYSYMBOL_67_6 = 67,                      /* $@6  */
  YYSYMBOL_func_param = 68,                /* func_param  */
  YYSYMBOL_list_param = 69,                /* list_param  */
  YYSYMBOL_param = 70,                     /* param  */
  YYSYMBOL_statements = 71,                /* statements  */
  YYSYMBOL_statement = 72,                 /* statement  */
  YYSYMBOL_return_statement = 73,          /* return_statement  */
  YYSYMBOL_assignment_statement = 74,      /* assignment_statement  */
  YYSYMBOL_control_statement = 75,         /* control_statement  */
  YYSYMBOL_if_statement = 76,              /* if_statement  */
  YYSYMBOL_77_7 = 77,                      /* $@7  */
  YYSYMBOL_for_statement = 78,             /* for_statement  */
  YYSYMBOL_79_8 = 79,                      /* $@8  */
  YYSYMBOL_while_statement = 80,           /* while_statement  */
  YYSYMBOL_81_9 = 81,                      /* $@9  */
  YYSYMBOL_function_call = 82,             /* function_call  */
  YYSYMBOL_arguments = 83,                 /* arguments  */
  YYSYMBOL_arg_list = 84,                  /* arg_list  */
  YYSYMBOL_expressions = 85,               /* expressions  */
  YYSYMBOL_eval_statement = 86,            /* eval_statement  */
  YYSYMBOL_type_of_statement = 87,         /* type_of_statement  */
  YYSYMBOL_expr = 88,                      /* expr  */
  YYSYMBOL_special_function = 89,          /* special_function  */
  YYSYMBOL_90_10 = 90                      /* $@10  */
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
#define YYLAST   446

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  42
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  214

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   294


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
      43,    44,     2,     2,    47,     2,    48,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    42,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    46,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    40,     2,    41,     2,     2,     2,     2,
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
      35,    36,    37,    38,    39
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   305,   305,   307,   308,   311,   311,   311,   317,   320,
     327,   334,   337,   344,   344,   344,   351,   352,   355,   363,
     371,   384,   397,   406,   466,   474,   482,   533,   536,   540,
     546,   547,   550,   550,   550,   557,   560,   565,   570,   577,
     583,   584,   587,   588,   589,   590,   591,   592,   593,   596,
     598,   611,   652,   726,   727,   728,   731,   731,   740,   740,
     743,   743,   746,   755,   759,   762,   767,   774,   779,   786,
     816,   841,   842,   843,   844,   845,   846,   847,   848,   849,
     850,   851,   852,   853,   854,   855,   860,   869,   870,   871,
     872,   873,   874,   875,   930,   932,   932
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
  "STRING", "BOOL", "ID", "TYPE", "SPECIAL_FUNCTION", "USR_TYPE", "IF",
  "WHILE", "FOR", "END_USR_TYPES", "END_USR_TYPE_VARS", "END_GLOBAL_VARS",
  "END_GLOBAL_FUNCS", "CONST", "EVAL", "TYPEOF", "RETURN", "NOT", "EQ",
  "NEQ", "LT", "LE", "GT", "GE", "ASSIGN", "PLUS", "MINUS", "MUL", "DIV",
  "MOD", "AND", "OR", "GEQ", "LEQ", "'{'", "'}'", "';'", "'('", "')'",
  "'['", "']'", "','", "'.'", "$accept", "program", "user_defined_types",
  "user_defined_type", "$@1", "$@2", "usr_type_vars", "usr_type_var",
  "usr_type_methods", "usr_type_method", "$@3", "$@4", "declarations",
  "decl", "initializer_list", "global_function_definitions",
  "global_function_definition", "$@5", "$@6", "func_param", "list_param",
  "param", "statements", "statement", "return_statement",
  "assignment_statement", "control_statement", "if_statement", "$@7",
  "for_statement", "$@8", "while_statement", "$@9", "function_call",
  "arguments", "arg_list", "expressions", "eval_statement",
  "type_of_statement", "expr", "special_function", "$@10", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-157)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -157,     5,    59,  -157,     4,   120,  -157,   -18,    53,    63,
      20,    73,    37,  -157,   -20,    78,    92,    94,  -157,    49,
    -157,  -157,    46,    46,    68,    81,   116,    -2,  -157,    -5,
    -157,  -157,  -157,  -157,  -157,    82,    46,    46,  -157,   392,
     193,    46,    46,  -157,   124,   118,  -157,   125,  -157,   103,
      46,    46,   128,  -157,    31,    46,    46,    46,    46,    46,
      46,    46,    46,    46,    46,    46,    46,    46,   121,   -17,
     392,   392,   107,   109,  -157,  -157,     6,  -157,   114,   106,
     392,   209,  -157,  -157,   411,   411,   411,   411,   411,   411,
      83,    83,  -157,  -157,  -157,   406,   406,   119,  -157,    46,
     152,   122,   154,  -157,  -157,  -157,    46,  -157,    46,   392,
     156,   126,   130,  -157,   138,   132,  -157,   392,    40,   392,
    -157,   145,   152,  -157,   152,  -157,    46,  -157,  -157,  -157,
     146,   392,  -157,    85,   151,   101,   -22,   149,   150,   155,
     163,   164,    46,  -157,   123,  -157,  -157,  -157,  -157,  -157,
    -157,  -157,   166,  -157,  -157,  -157,  -157,    46,    46,   201,
      46,    46,   206,    46,    46,   297,  -157,  -157,  -157,  -157,
     316,   225,   185,   241,   255,   -28,   181,   269,   283,  -157,
     135,  -157,   217,    46,   208,   223,    46,   189,   222,  -157,
      46,   335,  -157,  -157,   354,  -157,  -157,  -157,   373,  -157,
    -157,  -157,   206,  -157,   160,   175,   291,  -157,  -157,   296,
    -157,  -157,   191,  -157
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     1,     0,     0,     4,     0,     0,     0,
       0,     0,     0,     5,    18,     0,     0,     0,    30,     0,
      16,     8,     0,     0,    24,    19,     0,     0,    17,     0,
      87,    88,    89,    91,    90,    85,     0,     0,    92,    20,
       0,    27,     0,    25,     0,     0,    31,     0,    11,     0,
      63,     0,     0,    84,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    22,     0,
      29,    21,     0,     0,     2,    10,     0,     9,     0,    64,
      65,     0,    93,    94,    76,    77,    78,    79,    80,    81,
      71,    72,    73,    74,    75,    82,    83,     0,    26,     0,
      35,     0,     0,     6,    12,    62,     0,    86,     0,    28,
       0,     0,    36,    37,     0,     0,     7,    66,     0,    67,
      39,     0,     0,    95,    35,    23,     0,    32,    38,    40,
       0,    68,    40,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    96,     0,    41,    48,    43,    44,    53,
      54,    55,     0,    46,    47,    13,    33,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    42,    45,    40,    34,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
       0,    50,     0,     0,     0,     0,     0,     0,     0,    14,
       0,     0,    56,    60,     0,    69,    70,    15,     0,    52,
      40,    40,     0,    51,     0,     0,     0,    57,    61,     0,
      58,    40,     0,    59
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -157,  -157,  -157,  -157,  -157,  -157,  -157,  -157,  -157,  -157,
    -157,  -157,  -157,    90,  -157,  -157,  -157,  -157,  -157,   213,
    -157,   216,  -123,  -157,  -157,  -156,  -157,  -157,  -157,  -157,
    -157,  -157,  -157,  -132,  -157,  -157,  -157,  -157,  -157,   -23,
    -157,  -157
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,     6,    21,   116,    29,    49,    76,   104,
     168,   197,    11,   144,    69,    27,    46,   132,   169,   111,
     112,   113,   133,   145,   146,   147,   148,   149,   200,   150,
     211,   151,   201,    38,    78,    79,   118,   153,   154,    39,
      74,   129
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      40,   152,   157,   152,    47,     3,   176,    44,   157,   135,
      22,    48,     7,    53,    54,   102,    45,   158,    70,    71,
     159,    50,    13,   158,    98,    23,   159,    80,    81,    16,
      99,    17,    84,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,   180,   206,   103,   152,    30,
      31,    32,    33,    34,    35,    55,    56,    57,    58,    59,
      60,    14,    61,    62,    63,    64,    65,    66,    67,    36,
       4,    15,   152,   152,     5,    83,   109,   204,   205,    20,
     152,   125,     8,   117,     9,   119,    24,   126,   212,    37,
      18,    28,    10,   136,     8,    12,     9,   137,   138,   139,
      25,    19,    26,   131,    10,   140,   141,   142,    41,   136,
       8,    42,     9,   137,   138,   139,    63,    64,    65,   165,
      10,   140,   141,   142,    43,    50,   143,    51,    73,     8,
      52,     9,    72,    75,   170,   171,    82,   173,   174,    10,
     177,   178,   156,   136,     8,    77,     9,   137,   138,   139,
     100,    97,   101,   106,    10,   140,   141,   142,   105,   108,
     191,   110,   115,   194,   120,   166,   114,   198,   136,     8,
     121,     9,   137,   138,   139,   124,   189,   122,   123,    10,
     140,   141,   142,   136,     8,   127,     9,   137,   138,   139,
     134,   155,   160,   161,    10,   140,   141,   142,   162,   136,
       8,   207,     9,   137,   138,   139,   163,   164,   167,   172,
      10,   140,   141,   142,   175,   183,   208,    55,    56,    57,
      58,    59,    60,   186,    61,    62,    63,    64,    65,    66,
      67,   195,   213,    55,    56,    57,    58,    59,    60,    68,
      61,    62,    63,    64,    65,    66,    67,   190,   192,    55,
      56,    57,    58,    59,    60,   107,    61,    62,    63,    64,
      65,    66,    67,   193,   196,    55,    56,    57,    58,    59,
      60,   182,    61,    62,    63,    64,    65,    66,    67,    55,
      56,    57,    58,    59,    60,   184,    61,    62,    63,    64,
      65,    66,    67,    55,    56,    57,    58,    59,    60,   185,
      61,    62,    63,    64,    65,    66,    67,    55,    56,    57,
      58,    59,    60,   187,    61,    62,    63,    64,    65,    66,
      67,    55,    56,    57,    58,    59,    60,   188,    61,    62,
      63,    64,    65,    66,    67,   209,   210,   130,   128,   179,
      55,    56,    57,    58,    59,    60,     0,    61,    62,    63,
      64,    65,    66,    67,     0,     0,     0,     0,   181,    55,
      56,    57,    58,    59,    60,     0,    61,    62,    63,    64,
      65,    66,    67,     0,     0,     0,     0,   199,    55,    56,
      57,    58,    59,    60,     0,    61,    62,    63,    64,    65,
      66,    67,     0,     0,     0,     0,   202,    55,    56,    57,
      58,    59,    60,     0,    61,    62,    63,    64,    65,    66,
      67,     0,     0,     0,     0,   203,    55,    56,    57,    58,
      59,    60,     0,    61,    62,    63,    64,    65,    66,    67,
      55,    56,    57,    58,    59,    60,     0,    61,    62,    63,
      64,    65,    61,    62,    63,    64,    65
};

static const yytype_int16 yycheck[] =
{
      23,   133,    30,   135,     9,     0,   162,     9,    30,   132,
      30,    16,     8,    36,    37,     9,    18,    45,    41,    42,
      48,    43,    40,    45,    41,    45,    48,    50,    51,     9,
      47,    11,    55,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,   168,   202,    41,   180,     3,
       4,     5,     6,     7,     8,    24,    25,    26,    27,    28,
      29,     8,    31,    32,    33,    34,    35,    36,    37,    23,
      11,     8,   204,   205,    15,    44,    99,   200,   201,    42,
     212,    41,     9,   106,    11,   108,     8,    47,   211,    43,
      17,    42,    19,     8,     9,     5,    11,    12,    13,    14,
       8,    11,     8,   126,    19,    20,    21,    22,    40,     8,
       9,    30,    11,    12,    13,    14,    33,    34,    35,   142,
      19,    20,    21,    22,     8,    43,    41,    45,    10,     9,
      48,    11,     8,     8,   157,   158,     8,   160,   161,    19,
     163,   164,    41,     8,     9,    42,    11,    12,    13,    14,
      43,    30,    43,    47,    19,    20,    21,    22,    44,    40,
     183,     9,     8,   186,     8,    42,    44,   190,     8,     9,
      44,    11,    12,    13,    14,    43,    41,    47,    40,    19,
      20,    21,    22,     8,     9,    40,    11,    12,    13,    14,
      44,    40,    43,    43,    19,    20,    21,    22,    43,     8,
       9,    41,    11,    12,    13,    14,    43,    43,    42,     8,
      19,    20,    21,    22,     8,    30,    41,    24,    25,    26,
      27,    28,    29,    42,    31,    32,    33,    34,    35,    36,
      37,    42,    41,    24,    25,    26,    27,    28,    29,    46,
      31,    32,    33,    34,    35,    36,    37,    30,    40,    24,
      25,    26,    27,    28,    29,    46,    31,    32,    33,    34,
      35,    36,    37,    40,    42,    24,    25,    26,    27,    28,
      29,    46,    31,    32,    33,    34,    35,    36,    37,    24,
      25,    26,    27,    28,    29,    44,    31,    32,    33,    34,
      35,    36,    37,    24,    25,    26,    27,    28,    29,    44,
      31,    32,    33,    34,    35,    36,    37,    24,    25,    26,
      27,    28,    29,    44,    31,    32,    33,    34,    35,    36,
      37,    24,    25,    26,    27,    28,    29,    44,    31,    32,
      33,    34,    35,    36,    37,    44,    40,   124,   122,    42,
      24,    25,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    36,    37,    -1,    -1,    -1,    -1,    42,    24,
      25,    26,    27,    28,    29,    -1,    31,    32,    33,    34,
      35,    36,    37,    -1,    -1,    -1,    -1,    42,    24,    25,
      26,    27,    28,    29,    -1,    31,    32,    33,    34,    35,
      36,    37,    -1,    -1,    -1,    -1,    42,    24,    25,    26,
      27,    28,    29,    -1,    31,    32,    33,    34,    35,    36,
      37,    -1,    -1,    -1,    -1,    42,    24,    25,    26,    27,
      28,    29,    -1,    31,    32,    33,    34,    35,    36,    37,
      24,    25,    26,    27,    28,    29,    -1,    31,    32,    33,
      34,    35,    31,    32,    33,    34,    35
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    50,    51,     0,    11,    15,    52,     8,     9,    11,
      19,    61,    62,    40,     8,     8,     9,    11,    17,    62,
      42,    53,    30,    45,     8,     8,     8,    64,    42,    55,
       3,     4,     5,     6,     7,     8,    23,    43,    82,    88,
      88,    40,    30,     8,     9,    18,    65,     9,    16,    56,
      43,    45,    48,    88,    88,    24,    25,    26,    27,    28,
      29,    31,    32,    33,    34,    35,    36,    37,    46,    63,
      88,    88,     8,    10,    89,     8,    57,    42,    83,    84,
      88,    88,     8,    44,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    30,    41,    47,
      43,    43,     9,    41,    58,    44,    47,    46,    40,    88,
       9,    68,    69,    70,    44,     8,    54,    88,    85,    88,
       8,    44,    47,    40,    43,    41,    47,    40,    70,    90,
      68,    88,    66,    71,    44,    71,     8,    12,    13,    14,
      20,    21,    22,    41,    62,    72,    73,    74,    75,    76,
      78,    80,    82,    86,    87,    40,    41,    30,    45,    48,
      43,    43,    43,    43,    43,    88,    42,    42,    59,    67,
      88,    88,     8,    88,    88,     8,    74,    88,    88,    42,
      71,    42,    46,    30,    44,    44,    42,    44,    44,    41,
      30,    88,    40,    40,    88,    42,    42,    60,    88,    42,
      77,    81,    42,    42,    71,    71,    74,    41,    41,    44,
      40,    79,    71,    41
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    53,    54,    52,    55,    55,
      56,    57,    57,    59,    60,    58,    61,    61,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    63,    63,    63,
      64,    64,    66,    67,    65,    68,    68,    69,    69,    70,
      71,    71,    72,    72,    72,    72,    72,    72,    72,    73,
      74,    74,    74,    75,    75,    75,    77,    76,    79,    78,
      81,    80,    82,    83,    83,    84,    84,    85,    85,    86,
      87,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    90,    89
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     7,     0,     2,     0,     0,     9,     0,     3,
       2,     0,     2,     0,     0,    10,     2,     3,     2,     3,
       4,     5,     5,     9,     3,     4,     6,     0,     3,     1,
       0,     2,     0,     0,    10,     0,     1,     1,     3,     2,
       0,     2,     2,     1,     1,     2,     1,     1,     1,     3,
       4,     7,     6,     1,     1,     1,     0,     8,     0,    12,
       0,     8,     4,     0,     1,     1,     3,     1,     3,     5,
       5,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     1,     4,     1,     1,     1,
       1,     1,     1,     3,     3,     0,     7
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
#line 305 "limbaj.y"
                                                                                                                                     {printf("The programm is correct!\n");}
#line 1857 "limbaj.tab.c"
    break;

  case 5: /* $@1: %empty  */
#line 311 "limbaj.y"
                                   {symbolTable.enterScope(string((yyvsp[-1].string)));}
#line 1863 "limbaj.tab.c"
    break;

  case 6: /* $@2: %empty  */
#line 311 "limbaj.y"
                                                                                                                              { symbolTable.exitScope();}
#line 1869 "limbaj.tab.c"
    break;

  case 7: /* user_defined_type: USR_TYPE ID '{' $@1 usr_type_vars END_USR_TYPE_VARS usr_type_methods '}' $@2  */
#line 311 "limbaj.y"
                                                                                                                                                          {
                        UserType userType = UserType((yyvsp[-7].string), *(yyvsp[-4].vars), *(yyvsp[-2].funcs));
                        userTypes.push_back(userType);
                    }
#line 1878 "limbaj.tab.c"
    break;

  case 8: /* usr_type_vars: %empty  */
#line 317 "limbaj.y"
                             {
                    (yyval.vars) = new vector<VarInfo>();
                }
#line 1886 "limbaj.tab.c"
    break;

  case 9: /* usr_type_vars: usr_type_vars usr_type_var ';'  */
#line 320 "limbaj.y"
                                                {
                    (yyval.vars) = (yyvsp[-2].vars);
                    (yyval.vars)->push_back(*(yyvsp[-1].var));
                    delete((yyvsp[-1].var));
                }
#line 1896 "limbaj.tab.c"
    break;

  case 10: /* usr_type_var: TYPE ID  */
#line 327 "limbaj.y"
                      {
                    VarInfo* var = new VarInfo((yyvsp[-1].string), (yyvsp[0].string));
                    (yyval.var) = var;
                    symbolTable.addVariable(*var);
                }
#line 1906 "limbaj.tab.c"
    break;

  case 11: /* usr_type_methods: %empty  */
#line 334 "limbaj.y"
                                {
                    (yyval.funcs) = new vector<FunctionInfo>();
                }
#line 1914 "limbaj.tab.c"
    break;

  case 12: /* usr_type_methods: usr_type_methods usr_type_method  */
#line 337 "limbaj.y"
                                                   {
                    (yyval.funcs) = (yyvsp[-1].funcs);
                    (yyval.funcs)->push_back(*(yyvsp[0].func));
                    delete((yyvsp[0].func));
                }
#line 1924 "limbaj.tab.c"
    break;

  case 13: /* $@3: %empty  */
#line 344 "limbaj.y"
                                                {symbolTable.enterScope(string((yyvsp[-4].string)));}
#line 1930 "limbaj.tab.c"
    break;

  case 14: /* $@4: %empty  */
#line 344 "limbaj.y"
                                                                                                     {symbolTable.exitScope();}
#line 1936 "limbaj.tab.c"
    break;

  case 15: /* usr_type_method: TYPE ID '(' func_param ')' '{' $@3 statements '}' $@4  */
#line 344 "limbaj.y"
                                                                                                                                {
                    FunctionInfo* func = new FunctionInfo((yyvsp[-9].string), (yyvsp[-8].string), *(yyvsp[-6].vars));
                    (yyval.func) = func;
                    symbolTable.addFunction(*func);
                }
#line 1946 "limbaj.tab.c"
    break;

  case 18: /* decl: TYPE ID  */
#line 355 "limbaj.y"
              {
            if(symbolTable.variableExists((yyvsp[0].string))) {
                error_variable_exists((yyvsp[0].string));
            }
            VarInfo* var = new VarInfo((yyvsp[-1].string), (yyvsp[0].string));
            (yyval.var) = var;
            symbolTable.addVariable(*var);
    }
#line 1959 "limbaj.tab.c"
    break;

  case 19: /* decl: CONST TYPE ID  */
#line 363 "limbaj.y"
                    {
            if(symbolTable.variableExists((yyvsp[0].string))) {
                error_variable_exists((yyvsp[0].string));
            }
            VarInfo* var = new VarInfo((yyvsp[-1].string), (yyvsp[0].string), true);
            (yyval.var) = var;
            symbolTable.addVariable(*var);
    }
#line 1972 "limbaj.tab.c"
    break;

  case 20: /* decl: TYPE ID ASSIGN expr  */
#line 371 "limbaj.y"
                          {
            if(symbolTable.variableExists((yyvsp[-2].string))) {
                error_variable_exists((yyvsp[-2].string));   
            }
            if (strcmp((yyvsp[0].node)->string_type().c_str(), (yyvsp[-3].string)) != 0){                
                error_different_types((yyvsp[-3].string), (yyvsp[0].node)->string_type().c_str());
            }
            VarInfo* var = new VarInfo((yyvsp[-3].string), (yyvsp[-2].string), false);
            var->assign_expr((yyvsp[0].node));
            free((yyvsp[0].node));
            (yyval.var) = var;
            symbolTable.addVariable(*var);
    }
#line 1990 "limbaj.tab.c"
    break;

  case 21: /* decl: CONST TYPE ID ASSIGN expr  */
#line 384 "limbaj.y"
                                { 
            if(symbolTable.variableExists((yyvsp[-2].string))) {
                error_variable_exists((yyvsp[-2].string));
            }
            if (strcmp((yyvsp[-3].string), (yyvsp[0].node)->string_type().c_str()) != 0){
                error_different_types((yyvsp[-3].string), (yyvsp[0].node)->string_type().c_str());
            }
            VarInfo* var = new VarInfo((yyvsp[-3].string), (yyvsp[-2].string), true);
            var->assign_expr((yyvsp[0].node));
            free((yyvsp[0].node));
            (yyval.var) = var;
            symbolTable.addVariable(*var);
    }
#line 2008 "limbaj.tab.c"
    break;

  case 22: /* decl: TYPE ID '[' expr ']'  */
#line 397 "limbaj.y"
                           {
            if((yyvsp[-1].node)->string_type() != "int") yyerror("Array size specifier is not an integer");
            if(symbolTable.variableExists((yyvsp[-3].string))) {
                error_variable_exists((yyvsp[-3].string));
            }
            VarInfo* var = new VarInfo((yyvsp[-4].string), (yyvsp[-3].string), false, get<int>((yyvsp[-1].node)->evaluate()));
            (yyval.var) = var;
            symbolTable.addVariable(*var);
    }
#line 2022 "limbaj.tab.c"
    break;

  case 23: /* decl: TYPE ID '[' expr ']' ASSIGN '{' expressions '}'  */
#line 406 "limbaj.y"
                                                      {
            if((yyvsp[-5].node)->string_type() != "int") yyerror("Array size specifier is not an integer");
            if(symbolTable.variableExists((yyvsp[-7].string))) {
                error_variable_exists((yyvsp[-7].string));
            }
            int nr_elements = (yyvsp[-1].nodes)->size();
            if((std::get<int>((yyvsp[-5].node)->evaluate())) < nr_elements) {
                yyerror("Array size is smaller than the number of elements provided");
            }
            
            ASTNode::ReturnValue values[nr_elements];
            
            for(int i = 0; i < nr_elements; ++i){
                ASTNode* node = (*(yyvsp[-1].nodes))[i];
                if(strcmp(node->string_type().c_str(), (yyvsp[-8].string)) != 0){
                    error_different_types((yyvsp[-8].string), node->string_type().c_str());
                }
                values[i] = node->evaluate();
            }

            VarInfo* var = new VarInfo((yyvsp[-8].string), (yyvsp[-7].string), false, get<int>((yyvsp[-5].node)->evaluate()));
            
            if(strcmp((yyvsp[-8].string), "int") == 0){
                    int* intVals = new int[nr_elements];
                    for(int i = 0; i < nr_elements; ++i){
                        intVals[i] = std::get<int>(values[i]);
                    }
                    var->setValue((void*)intVals);
            }
            else if (strcmp((yyvsp[-8].string), "bool") == 0){
                    bool* boolVals = new bool[nr_elements];
                    for(int i = 0; i < nr_elements; ++i){
                        boolVals[i] = std::get<bool>(values[i]);
                    }
                    var->setValue((void*)boolVals);
            }               
            else if (strcmp((yyvsp[-8].string), "char") == 0){
                    char* charVals = new char[nr_elements];
                    for(int i = 0; i < nr_elements; ++i){
                        charVals[i] = std::get<char>(values[i]);
                    }
                    var->setValue((void*)charVals);
            }
            else if (strcmp((yyvsp[-8].string), "float") == 0){    
                    float* floatVals = new float[nr_elements];
                    for(int i = 0; i < nr_elements; ++i){
                        floatVals[i] = std::get<float>(values[i]);
                    }
                    var->setValue((void*)floatVals);
            }    
            else if (strcmp((yyvsp[-8].string), "string") == 0){
                    char** stringVals = new char*[nr_elements];
                    for(int i = 0; i < nr_elements; ++i){
                        stringVals[i] = *(std::get<char**>(values[i]));
                    }
                    var->setValue((void*)stringVals);
            }    
            (yyval.var) = var;
            symbolTable.addVariable(*var);
    }
#line 2087 "limbaj.tab.c"
    break;

  case 24: /* decl: USR_TYPE ID ID  */
#line 466 "limbaj.y"
                     {
            if(symbolTable.variableExists((yyvsp[0].string))) {
                error_variable_exists((yyvsp[0].string));
            }
            VarInfo* var = new VarInfo((yyvsp[-1].string), (yyvsp[0].string), false, 1, nullptr, true);
            (yyval.var) = var;
            symbolTable.addVariable(*var);
    }
#line 2100 "limbaj.tab.c"
    break;

  case 25: /* decl: CONST USR_TYPE ID ID  */
#line 474 "limbaj.y"
                           {
            if(symbolTable.variableExists((yyvsp[0].string))) {
                error_variable_exists((yyvsp[0].string));
            }
            VarInfo* var = new VarInfo((yyvsp[-1].string), (yyvsp[0].string), true, 1, nullptr, true);
            (yyval.var) = var;
            symbolTable.addVariable(*var);
    }
#line 2113 "limbaj.tab.c"
    break;

  case 26: /* decl: USR_TYPE ID ID '{' initializer_list '}'  */
#line 482 "limbaj.y"
                                              { // initialize user type variable with initializer list 
            if(symbolTable.variableExists((yyvsp[-3].string))) {
                error_variable_exists((yyvsp[-3].string));
            }
            VarInfo* var = new VarInfo((yyvsp[-4].string), (yyvsp[-3].string), false, 1, nullptr, true);

            int nr_elements = (yyvsp[-1].nodes)->size();
            if(nr_elements == 0) {
                yyerror("Initializer list is empty in user type initialization");
            }

            int userTypeIndex = -1;
            for (int i = 0; i < userTypes.size(); ++i) {
                if (userTypes[i].getName() == (yyvsp[-4].string)) {
                    userTypeIndex = i;
                    break;
                }
            }
            if (userTypeIndex == -1) {
                char errorMsg[100];
                sprintf(errorMsg, "User type %s not found", (yyvsp[-4].string));
                yyerror(errorMsg);
            }
            if (userTypes[userTypeIndex].getVars().size() != nr_elements) {
                yyerror("Number of elements in the initializer list is not equal to the number of variables in the user type");
            }
            for (int i = 0; i < nr_elements; ++i) {
                if (userTypes[userTypeIndex].getVars()[i].getType() != (*(yyvsp[-1].nodes))[i]->string_type()) {
                    yyerror("Types of elements in the initializer list do not match the types of the variables in the user type");
                }
            }
            // copy the values from the initializer list to the user type variable
            int offset = 0;
            void* copy = malloc(var->getSize());
            memset(copy, 0, var->getSize());
            for (int i = 0; i < nr_elements; ++i) {
                std::visit([&](auto&& arg) {     // visit each element in the initializer list and copy it to the user type variable
                    using T = std::decay_t<decltype(arg)>;
                    if constexpr (std::is_same_v<T, int> || std::is_same_v<T, float> || std::is_same_v<T, bool> ||   std::is_same_v<T, char> || std::is_same_v<T, char**>) {
                        memcpy((char*)copy + offset, &arg, sizeof(T));
                        offset += sizeof(T);
                    }
                }, (*(yyvsp[-1].nodes))[i]->evaluate());
            }

            var->setValue(copy);
            (yyval.var) = var;
            symbolTable.addVariable(*var);
    }
#line 2167 "limbaj.tab.c"
    break;

  case 27: /* initializer_list: %empty  */
#line 533 "limbaj.y"
                                {
                    (yyval.nodes) = new vector<ASTNode*>();
                }
#line 2175 "limbaj.tab.c"
    break;

  case 28: /* initializer_list: initializer_list ',' expr  */
#line 536 "limbaj.y"
                                            {
                    (yyval.nodes) = (yyvsp[-2].nodes);
                    (yyval.nodes)->push_back((yyvsp[0].node));
                }
#line 2184 "limbaj.tab.c"
    break;

  case 29: /* initializer_list: expr  */
#line 540 "limbaj.y"
                       {
                    (yyval.nodes) = new vector<ASTNode*>();
                    (yyval.nodes)->push_back((yyvsp[0].node));
                }
#line 2193 "limbaj.tab.c"
    break;

  case 32: /* $@5: %empty  */
#line 550 "limbaj.y"
                                                           {symbolTable.enterScope(string((yyvsp[-4].string)));}
#line 2199 "limbaj.tab.c"
    break;

  case 33: /* $@6: %empty  */
#line 550 "limbaj.y"
                                                                                                                {symbolTable.exitScope();}
#line 2205 "limbaj.tab.c"
    break;

  case 34: /* global_function_definition: TYPE ID '(' func_param ')' '{' $@5 statements '}' $@6  */
#line 550 "limbaj.y"
                                                                                                                                           {
                            FunctionInfo* func = new FunctionInfo((yyvsp[-9].string), (yyvsp[-8].string), *(yyvsp[-6].vars));
                            symbolTable.addFunction(*func);
                        }
#line 2214 "limbaj.tab.c"
    break;

  case 35: /* func_param: %empty  */
#line 557 "limbaj.y"
                          {
                (yyval.vars) = new vector<VarInfo>();
            }
#line 2222 "limbaj.tab.c"
    break;

  case 36: /* func_param: list_param  */
#line 560 "limbaj.y"
                         {
                (yyval.vars) = (yyvsp[0].vars);
            }
#line 2230 "limbaj.tab.c"
    break;

  case 37: /* list_param: param  */
#line 565 "limbaj.y"
                  {
                (yyval.vars) = new vector<VarInfo>();
                (yyval.vars)->push_back(*(yyvsp[0].var));
                delete((yyvsp[0].var));
                }
#line 2240 "limbaj.tab.c"
    break;

  case 38: /* list_param: list_param ',' param  */
#line 570 "limbaj.y"
                                   {
                (yyval.vars) = (yyvsp[-2].vars);
                (yyval.vars)->push_back(*(yyvsp[0].var));
                delete((yyvsp[0].var));
            }
#line 2250 "limbaj.tab.c"
    break;

  case 39: /* param: TYPE ID  */
#line 577 "limbaj.y"
               {
            VarInfo* var = new VarInfo((yyvsp[-1].string), (yyvsp[0].string));
            (yyval.var) = var;
        }
#line 2259 "limbaj.tab.c"
    break;

  case 50: /* assignment_statement: ID ASSIGN expr ';'  */
#line 598 "limbaj.y"
                                         {
                        if(!symbolTable.variableExists((yyvsp[-3].string))) {
                            error_variable_not_found((yyvsp[-3].string));
                        }
                        VarInfo temp = symbolTable.getVariableReference((yyvsp[-3].string));

                        if(strcmp(temp.getType().c_str(), (yyvsp[-1].node)->string_type().c_str()) == 0){
                            temp.assign_expr((yyvsp[-1].node));
                        }
                        else{
                            error_different_types(temp.getType().c_str(), (yyvsp[-1].node)->string_type().c_str());
                        }
                    }
#line 2277 "limbaj.tab.c"
    break;

  case 51: /* assignment_statement: ID '[' expr ']' ASSIGN expr ';'  */
#line 611 "limbaj.y"
                                                      {
                        if(strcmp((yyvsp[-4].node)->string_type().c_str(), "int") == 0){
                            if(!symbolTable.variableExists((yyvsp[-6].string))) {
                                error_variable_not_found((yyvsp[-6].string));
                            }
                            
                            VarInfo temp = symbolTable.getVariableReference((yyvsp[-6].string));

                            if(strcmp(temp.getType().c_str(), (yyvsp[-1].node)->string_type().c_str()) == 0){
                                if(strcmp(temp.getType().c_str(), "int") == 0){
                                    int* intVals = (int*)(temp.getValueReference());
                                    intVals[std::get<int>((yyvsp[-4].node)->evaluate())] = std::get<int>((yyvsp[-1].node)->evaluate());
                                    temp.setValue((void*)intVals);
                                }
                                else if(strcmp(temp.getType().c_str(), "float") == 0){
                                    float* floatVals = (float*)(temp.getValueReference());
                                    floatVals[std::get<int>((yyvsp[-4].node)->evaluate())] = std::get<float>((yyvsp[-1].node)->evaluate());
                                    temp.setValue((void*)floatVals);
                                }
                                else if(strcmp(temp.getType().c_str(), "bool") == 0){
                                    bool* boolVals = (bool*)(temp.getValueReference());
                                    boolVals[std::get<int>((yyvsp[-4].node)->evaluate())] = std::get<bool>((yyvsp[-1].node)->evaluate());
                                    temp.setValue((void*)boolVals);
                                }
                                else if(strcmp(temp.getType().c_str(), "char") == 0){
                                    char* charVals = (char*)(temp.getValueReference());
                                    charVals[std::get<int>((yyvsp[-4].node)->evaluate())] = std::get<char>((yyvsp[-1].node)->evaluate());
                                    temp.setValue((void*)charVals);
                                }
                                else if(strcmp(temp.getType().c_str(), "string") == 0){
                                    char** stringVals = (char**)(temp.getValueReference());
                                    stringVals[std::get<int>((yyvsp[-4].node)->evaluate())] = *(std::get<char**>((yyvsp[-1].node)->evaluate()));
                                    temp.setValue((void*)stringVals);
                                }
                            }
                            else{
                                error_different_types(temp.getType().c_str(), (yyvsp[-1].node)->string_type().c_str());
                            }
                        }
                        else yyerror("Array element access number is not an integer");
                    }
#line 2323 "limbaj.tab.c"
    break;

  case 52: /* assignment_statement: ID '.' ID ASSIGN expr ';'  */
#line 652 "limbaj.y"
                                                {
                        bool found = false;
                        VarInfo variable = symbolTable.getVariableReference((yyvsp[-5].string));
                        // search for the user type
                        for (const UserType& userType : userTypes) {
                            if(userType.getName() == variable.getType()) {
                                found = true;
                                // check if the variable exists in the user type
                                bool foundVar = false;
                                for (const VarInfo& var : userType.getVars()) {
                                    if (var.getName() == (yyvsp[-3].string)) {
                                        foundVar = true;
                                        int offset = 0;
                                        for (const VarInfo& v : userType.getVars()) {
                                            if (v.getName() == (yyvsp[-3].string)) {
                                                break;
                                            }
                                            offset += v.getSize();
                                        }
                                        if (var.getType() == "int") {
                                            int value = *(int*)((char*)symbolTable.getVariableReference((yyvsp[-5].string)).getValueReference() + offset);
                                            if (strcmp((yyvsp[-1].node)->string_type().c_str(), "int") == 0) {
                                                *(int*)((char*)symbolTable.getVariableReference((yyvsp[-5].string)).getValueReference() + offset) = std::get<int>((yyvsp[-1].node)->evaluate());
                                            } else {
                                                error_different_types("int", (yyvsp[-1].node)->string_type().c_str());
                                            }
                                        } else if (var.getType() == "float") {
                                            float valuef = *(float*)((char*)symbolTable.getVariableReference((yyvsp[-5].string)).getValueReference() + offset);
                                            if (strcmp((yyvsp[-1].node)->string_type().c_str(), "float") == 0) {
                                                *(float*)((char*)symbolTable.getVariableReference((yyvsp[-5].string)).getValueReference() + offset) = std::get<float>((yyvsp[-1].node)->evaluate());
                                            } else {
                                                error_different_types("float", (yyvsp[-1].node)->string_type().c_str());
                                            }
                                        } else if (var.getType() == "bool") {
                                            bool valueb = *(bool*)((char*)symbolTable.getVariableReference((yyvsp[-5].string)).getValueReference() + offset);
                                            if (strcmp((yyvsp[-1].node)->string_type().c_str(), "bool") == 0) {
                                                *(bool*)((char*)symbolTable.getVariableReference((yyvsp[-5].string)).getValueReference() + offset) = std::get<bool>((yyvsp[-1].node)->evaluate());
                                            } else {
                                                error_different_types("bool", (yyvsp[-1].node)->string_type().c_str());
                                            }
                                        } else if (var.getType() == "char") {
                                            char valuec = *(char*)((char*)symbolTable.getVariableReference((yyvsp[-5].string)).getValueReference() + offset);
                                            if (strcmp((yyvsp[-1].node)->string_type().c_str(), "char") == 0) {
                                                *(char*)((char*)symbolTable.getVariableReference((yyvsp[-5].string)).getValueReference() + offset) = std::get<char>((yyvsp[-1].node)->evaluate());
                                            } else {
                                                error_different_types("char", (yyvsp[-1].node)->string_type().c_str());
                                            }
                                        } else if (var.getType() == "string") {
                                            char* values = *(char**)((char*)symbolTable.getVariableReference((yyvsp[-5].string)).getValueReference() + offset);
                                            if (strcmp((yyvsp[-1].node)->string_type().c_str(), "string") == 0) {
                                                *(char**)((char*)symbolTable.getVariableReference((yyvsp[-5].string)).getValueReference() + offset) = *(std::get<char**>((yyvsp[-1].node)->evaluate()));
                                            } else {
                                                error_different_types("string", (yyvsp[-1].node)->string_type().c_str());
                                            }
                                        } else {
                                            yyerror("Unknown type in user type variable");
                                        }
                                        break;
                                    }
                                }
                                if (!foundVar) {
                                    char errorMsg[100];
                                    sprintf(errorMsg, "Variable %s not found in user type %s", (yyvsp[-3].string), userType.getName().c_str());
                                    yyerror(errorMsg);
                                }
                                break;
                            }
                        }
                        if (!found) {
                            yyerror("User type not found");
                        }
                    }
#line 2400 "limbaj.tab.c"
    break;

  case 56: /* $@7: %empty  */
#line 731 "limbaj.y"
                                  {
        symbolTable.enterScope("if" + std::to_string(ifCounter++));
        if(strcmp((yyvsp[-2].node)->string_type().c_str(), "bool") != 0 || get<bool>((yyvsp[-2].node)->evaluate()) == 0){
            //symbolTable.exitScope();
            //break;
        }
        }
#line 2412 "limbaj.tab.c"
    break;

  case 57: /* if_statement: IF '(' expr ')' '{' $@7 statements '}'  */
#line 737 "limbaj.y"
                         {symbolTable.exitScope();}
#line 2418 "limbaj.tab.c"
    break;

  case 58: /* $@8: %empty  */
#line 740 "limbaj.y"
                                                                                      { symbolTable.enterScope("for" + std::to_string(forCounter++));}
#line 2424 "limbaj.tab.c"
    break;

  case 59: /* for_statement: FOR '(' assignment_statement ';' expr ';' assignment_statement ')' '{' $@8 statements '}'  */
#line 740 "limbaj.y"
                                                                                                                                                                      {symbolTable.exitScope();}
#line 2430 "limbaj.tab.c"
    break;

  case 60: /* $@9: %empty  */
#line 743 "limbaj.y"
                                        {symbolTable.enterScope("while" + std::to_string(whileCounter++));}
#line 2436 "limbaj.tab.c"
    break;

  case 61: /* while_statement: WHILE '(' expr ')' '{' $@9 statements '}'  */
#line 743 "limbaj.y"
                                                                                                                           {symbolTable.exitScope();}
#line 2442 "limbaj.tab.c"
    break;

  case 62: /* function_call: ID '(' arguments ')'  */
#line 746 "limbaj.y"
                                    {
        if(!symbolTable.functionExists((yyvsp[-3].string))) {
            error_function_not_found((yyvsp[-3].string));
        }
        FunctionCallNode* func = new FunctionCallNode((yyvsp[-3].string), (yyvsp[-1].nodes));
        (yyval.node) = func;
    }
#line 2454 "limbaj.tab.c"
    break;

  case 63: /* arguments: %empty  */
#line 755 "limbaj.y"
                         {
            vector<ASTNode*>* temp = new vector<ASTNode*>();
            (yyval.nodes) = temp;
        }
#line 2463 "limbaj.tab.c"
    break;

  case 64: /* arguments: arg_list  */
#line 759 "limbaj.y"
                   {(yyval.nodes) = (yyvsp[0].nodes);}
#line 2469 "limbaj.tab.c"
    break;

  case 65: /* arg_list: expr  */
#line 762 "limbaj.y"
               {
        vector<ASTNode*>* temp = new vector<ASTNode*>();
        temp->push_back((yyvsp[0].node));
        (yyval.nodes) = temp;
    }
#line 2479 "limbaj.tab.c"
    break;

  case 66: /* arg_list: arg_list ',' expr  */
#line 767 "limbaj.y"
                        {
        vector<ASTNode*>* temp = (yyvsp[-2].nodes);
        temp->push_back((yyvsp[0].node));
        (yyval.nodes) = temp;
    }
#line 2489 "limbaj.tab.c"
    break;

  case 67: /* expressions: expr  */
#line 774 "limbaj.y"
                  {
                vector<ASTNode*>* temp = new vector<ASTNode*>();
                temp->push_back((yyvsp[0].node));
                (yyval.nodes) = temp;
            }
#line 2499 "limbaj.tab.c"
    break;

  case 68: /* expressions: expressions ',' expr  */
#line 779 "limbaj.y"
                                  {
                vector<ASTNode*>* temp = (yyvsp[-2].nodes);
                temp->push_back((yyvsp[0].node));
                (yyval.nodes) = temp;
            }
#line 2509 "limbaj.tab.c"
    break;

  case 69: /* eval_statement: EVAL '(' expr ')' ';'  */
#line 786 "limbaj.y"
                                      { 
    switch((yyvsp[-2].node)->type()) {
        case ExprType::INT:
            printf("Evaluated expression: %d at line %d\n", std::get<int>((yyvsp[-2].node)->evaluate()), yylineno);
            break;
        case ExprType::FLOAT:
            printf("Evaluated expression: %f at line %d\n", std::get<float>((yyvsp[-2].node)->evaluate()), yylineno);
            break;
        case ExprType::BOOLEAN:
            printf("Evaluated expression: %s at line %d\n", std::get<bool>((yyvsp[-2].node)->evaluate())? "true" : "false", yylineno);
            break;
        case ExprType::STRING:
            if(std::get<char**>((yyvsp[-2].node)->evaluate()) != nullptr) {
                printf("Evaluated expression: %s at line %d\n", *(std::get<char**>((yyvsp[-2].node)->evaluate())), yylineno);

            }
            else
                printf("Evaluated expression: null\n");
            break;
        case ExprType::CHAR:
            printf("Evaluated expression: %c at line %d\n", std::get<char>((yyvsp[-2].node)->evaluate()), yylineno);
            break;
        default:
            printf("Evaluated expression: Unknown type\n");
            break;
    }
    free((yyvsp[-2].node)); // free the memory allocated for the expression
}
#line 2542 "limbaj.tab.c"
    break;

  case 70: /* type_of_statement: TYPEOF '(' expr ')' ';'  */
#line 816 "limbaj.y"
                                           { 
        switch ((yyvsp[-2].node)->type()) {
            case ExprType::INT:
                printf("Type of expression: int at line %d\n", yylineno);
                break;
            case ExprType::FLOAT:
                printf("Type of expression: float at line %d\n", yylineno);
                break;
            case ExprType::BOOLEAN:
                printf("Type of expression: bool at line %d\n", yylineno);
                break;
            case ExprType::STRING:
                printf("Type of expression: string at line %d\n", yylineno);
                break;
            case ExprType::CHAR:
                printf("Type of expression: char at line %d\n", yylineno);
                break;
            default:
                printf("Type of expression: unknown at line %d\n", yylineno);
                break;
        }
    free((yyvsp[-2].node)); // free the memory allocated for the expression
    }
#line 2570 "limbaj.tab.c"
    break;

  case 71: /* expr: expr PLUS expr  */
#line 841 "limbaj.y"
                     { (yyval.node) = new BinaryOpNode('+', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2576 "limbaj.tab.c"
    break;

  case 72: /* expr: expr MINUS expr  */
#line 842 "limbaj.y"
                      { (yyval.node) = new BinaryOpNode('-', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2582 "limbaj.tab.c"
    break;

  case 73: /* expr: expr MUL expr  */
#line 843 "limbaj.y"
                    { (yyval.node) = new BinaryOpNode('*', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2588 "limbaj.tab.c"
    break;

  case 74: /* expr: expr DIV expr  */
#line 844 "limbaj.y"
                    { (yyval.node) = new BinaryOpNode('/', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2594 "limbaj.tab.c"
    break;

  case 75: /* expr: expr MOD expr  */
#line 845 "limbaj.y"
                    { (yyval.node) = new BinaryOpNode('%', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2600 "limbaj.tab.c"
    break;

  case 76: /* expr: expr EQ expr  */
#line 846 "limbaj.y"
                   { (yyval.node) = new BinaryOpNode('=', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2606 "limbaj.tab.c"
    break;

  case 77: /* expr: expr NEQ expr  */
#line 847 "limbaj.y"
                    { (yyval.node) = new BinaryOpNode('n', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2612 "limbaj.tab.c"
    break;

  case 78: /* expr: expr LT expr  */
#line 848 "limbaj.y"
                   { (yyval.node) = new BinaryOpNode('<', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2618 "limbaj.tab.c"
    break;

  case 79: /* expr: expr LE expr  */
#line 849 "limbaj.y"
                   { (yyval.node) = new BinaryOpNode('l', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2624 "limbaj.tab.c"
    break;

  case 80: /* expr: expr GT expr  */
#line 850 "limbaj.y"
                   { (yyval.node) = new BinaryOpNode('>', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2630 "limbaj.tab.c"
    break;

  case 81: /* expr: expr GE expr  */
#line 851 "limbaj.y"
                   { (yyval.node) = new BinaryOpNode('g', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2636 "limbaj.tab.c"
    break;

  case 82: /* expr: expr AND expr  */
#line 852 "limbaj.y"
                    { (yyval.node) = new BinaryOpNode('&', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2642 "limbaj.tab.c"
    break;

  case 83: /* expr: expr OR expr  */
#line 853 "limbaj.y"
                   { (yyval.node) = new BinaryOpNode('|', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2648 "limbaj.tab.c"
    break;

  case 84: /* expr: NOT expr  */
#line 854 "limbaj.y"
               { (yyval.node) = new BinaryOpNode('!', (yyvsp[0].node), new BoolNode(false)); /* right node is a dummy value */ }
#line 2654 "limbaj.tab.c"
    break;

  case 85: /* expr: ID  */
#line 855 "limbaj.y"
         { (yyval.node) = new IdentifierNode((yyvsp[0].string));
        if(!symbolTable.variableExists((yyvsp[0].string))) {
            error_variable_not_found((yyvsp[0].string));
        }
    }
#line 2664 "limbaj.tab.c"
    break;

  case 86: /* expr: ID '[' expr ']'  */
#line 860 "limbaj.y"
                      {
        if(!symbolTable.variableExists((yyvsp[-3].string))) {
            error_variable_not_found((yyvsp[-3].string));
        }
        if((yyvsp[-1].node)->type() == ExprType::INT) {
            (yyval.node) = new VectorElementNode((yyvsp[-3].string), std::get<int>((yyvsp[-1].node)->evaluate()));
        }
        else yyerror("Access number must be integer type");
    }
#line 2678 "limbaj.tab.c"
    break;

  case 87: /* expr: INT  */
#line 869 "limbaj.y"
          { (yyval.node) = new IntNode((yyvsp[0].intValue)); }
#line 2684 "limbaj.tab.c"
    break;

  case 88: /* expr: FLOAT  */
#line 870 "limbaj.y"
            { (yyval.node) = new FloatNode((yyvsp[0].floatValue)); }
#line 2690 "limbaj.tab.c"
    break;

  case 89: /* expr: CHAR  */
#line 871 "limbaj.y"
           { (yyval.node) = new CharNode((yyvsp[0].charValue)); }
#line 2696 "limbaj.tab.c"
    break;

  case 90: /* expr: BOOL  */
#line 872 "limbaj.y"
           { (yyval.node) = new BoolNode((yyvsp[0].boolValue)); }
#line 2702 "limbaj.tab.c"
    break;

  case 91: /* expr: STRING  */
#line 873 "limbaj.y"
             { (yyval.node) = new StringNode(&(yyvsp[0].string)); }
#line 2708 "limbaj.tab.c"
    break;

  case 92: /* expr: function_call  */
#line 874 "limbaj.y"
                    { (yyval.node) = (yyvsp[0].node); }
#line 2714 "limbaj.tab.c"
    break;

  case 93: /* expr: ID '.' ID  */
#line 875 "limbaj.y"
                { 
        bool found = false;
        VarInfo variable = symbolTable.getVariableReference((yyvsp[-2].string));
        // search for the user type
        for (const UserType& userType : userTypes) {
            if(userType.getName() == variable.getType()) {
                found = true;
                // check if the variable exists in the user type
                bool foundVar = false;
                for (const VarInfo& var : userType.getVars()) {
                    if (var.getName() == (yyvsp[0].string)) {
                        foundVar = true;
                        int offset = 0;
                        for (const VarInfo& v : userType.getVars()) {
                            if (v.getName() == (yyvsp[0].string)) {
                                break;
                            }
                            offset += v.getSize();
                        }
                        if (var.getType() == "int") {
                            int value = *(int*)((char*)symbolTable.getVariableReference((yyvsp[-2].string)).getValueReference() + offset);
                            (yyval.node) = new IntNode(value);
                        } else if (var.getType() == "float") {
                            float valuef = *(float*)((char*)symbolTable.getVariableReference((yyvsp[-2].string)).getValueReference() + offset);
                            (yyval.node) = new FloatNode(valuef);
                        } else if (var.getType() == "bool") {
                            bool valueb = *(bool*)((char*)symbolTable.getVariableReference((yyvsp[-2].string)).getValueReference() + offset);
                            (yyval.node) = new BoolNode(valueb);
                        } else if (var.getType() == "char") {
                            char valuec = *(char*)((char*)symbolTable.getVariableReference((yyvsp[-2].string)).getValueReference() + offset);
                            
                            (yyval.node) = new CharNode(valuec);
                        } else if (var.getType() == "string") {
                            char* values = *(char**)((char*)symbolTable.getVariableReference((yyvsp[-2].string)).getValueReference() + offset);
                            (yyval.node) = new StringNode(&values);
                        } else {
                            yyerror("Unknown type in user type variable");
                        }
                        break;
                    }
                }
                if (!foundVar) {
                    char errorMsg[100];
                    sprintf(errorMsg, "Variable %s not found in user type %s", (yyvsp[0].string), userType.getName().c_str());
                    yyerror(errorMsg);
                }
                break;
            }
        }
        if (!found) {
            char errorMsg[100];
            sprintf(errorMsg, "User type %s not found", variable.getType().c_str());
            yyerror(errorMsg);
        }
    }
#line 2774 "limbaj.tab.c"
    break;

  case 94: /* expr: '(' expr ')'  */
#line 930 "limbaj.y"
                   { (yyval.node) = (yyvsp[-1].node); }
#line 2780 "limbaj.tab.c"
    break;

  case 95: /* $@10: %empty  */
#line 932 "limbaj.y"
                                               { symbolTable.enterScope("clean_code_executer"); }
#line 2786 "limbaj.tab.c"
    break;

  case 96: /* special_function: SPECIAL_FUNCTION '(' ')' '{' $@10 statements '}'  */
#line 932 "limbaj.y"
                                                                                                                 { symbolTable.exitScope(); }
#line 2792 "limbaj.tab.c"
    break;


#line 2796 "limbaj.tab.c"

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

#line 935 "limbaj.y"

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

void error_variable_exists(const char* name){
    printf("error: Variable already exists (%s) at line:%d\n",name,yylineno);
    exit(1);
}

void error_function_exists(const char* name){
    printf("error: Function already exists (%s) at line:%d\n",name,yylineno);
    exit(1);
}

void error_function_not_found(const char* name){
    printf("error: Function does not exist (%s) at line:%d\n",name,yylineno);
    exit(1);
}

void error_variable_not_found(const char* name){
    printf("error: Variable does not exist (%s) at line:%d\n",name,yylineno);
    exit(1);
}

void error_different_types(const char* left , const char* right){
    printf("error: Different types assignment (%s <- %s) at line:%d\n",left, right, yylineno);
    exit(1);
}

void error_type_mismatch(const char* left , const char* right){
    printf("error: Type mismatch (%s, %s) at line:%d\n",left, right, yylineno);
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
    // search for variable in current scope and all parent scopes
    for (int i = symbolTable.getCurrentScope().length(); i >= 0; --i) {
        string currentScope = symbolTable.getCurrentScope().substr(0, i);
        auto it = variables.find(currentScope);
        if (it != variables.end() && it->second.find(name) != it->second.end()) {            
            return true;
        }
    }
    return false;
}

bool SymbolTable::functionExists(const string& name) {
    // search in global scope
    return functions[""].find(name) != functions[""].end();
}

VarInfo& SymbolTable::getVariableReference(const string& name) {
    // search for variable in current scope and all parent scopes
    for (int i = symbolTable.getCurrentScope().length(); i >= 0; --i) {
        string currentScope = symbolTable.getCurrentScope().substr(0, i);
        auto it = variables.find(currentScope);
        if (it != variables.end() && it->second.find(name) != it->second.end()) {
            return it->second[name];
        }
    }
    return DummyVarInfo; // return dummy variable (empty) if variable does not exist
}

FunctionInfo SymbolTable::getFunction(const string& name) {
    //search for function in global scope
    auto it = functions[""].find(name);
    if (it != functions[""].end()) {
        return it->second;
    }
    return DummyFunctionInfo;
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

VarInfo::VarInfo(string type, string name, bool is_const, int arraySize, void* value, bool isUserType) {
    this->type = type;
    this->name = name;
    this->isConst = is_const;
    // Deduct the size from the type
    switch (type[0]) {
    case 'i': // int
        this->size = sizeof(int);
        break;
    case 'c': // char
        this->size = sizeof(char);
        break;
    case 'f': // float
        this->size = sizeof(float);
        break;
    case 'b': // bool
        this->size = sizeof(bool);
        break;
    case 's': // string
        this->size = sizeof(char**);
        break;
    default:
        this->size = 0;
        break;
    }
    if(isUserType) {
        this->size = 0;
        bool found = false;
        for (const UserType& userType : userTypes) {
            if (userType.getName() == type) {
                found = true;
                // calculate the size of the user type
                for (const VarInfo& var : userType.getVars()) {
                    this->size += var.getSize();
                }
                break;
            }
        }
        if (!found) {
            char errorMsg[100];
            sprintf(errorMsg, "User type %s not found", type.c_str());
            yyerror(errorMsg);
        }
        this->isUserType = true;
    }

    // Allocate memory for the variable
    this->memoryLocation = malloc(this->size * arraySize);
    if (value != nullptr) {
        memcpy(this->memoryLocation, value, this->size * arraySize);
    }
    else {
        *((char**)this->memoryLocation) = nullptr;
    }

    this->size = this->size * arraySize;
}

void VarInfo::setSize(int size) {
    free(this->memoryLocation);
    this->memoryLocation = malloc(size);
    this->size = size;
}

void VarInfo::setValue(void* value){
    // print value for debugging in case var is string
    if(this->type == "string" && this->size == sizeof(char*)) {
    }
    memcpy(this->memoryLocation, value, this->size);
}

void* VarInfo::getValueReference() const {
    return this->memoryLocation;
    
}

void VarInfo::write_to_string(string& str) const {
    if(this->size == 0) return; // variabila nu exosta
    if(!this->isUserType) {
        str += "name: " + this->name;
        str += "\ntype: " + this->type;
        str += "\nconst: " + std::to_string(this->isConst);
        str += "\nsize in bytes: " + std::to_string(this->size);
        str += "\nvalue: ";
    }
    if(this->memoryLocation == nullptr) {
        str += "null";
        str += "\n\n";
        return;
    }
    if(this->type == "int"){
        if(this->size == sizeof(int)) str += std::to_string(*(int*)this->memoryLocation);
        else if (this->size > sizeof(int) && this->memoryLocation != nullptr){
            int* arr = (int*)(this->memoryLocation);
            for(int j = 0; j < this->size/sizeof(int); ++j){
                str += (std::to_string(arr[j]));
                str += " ";
            }
        }
    }
    else if (this->type == "char"){
        if(this->size == sizeof(char)) str += *(char*)this->memoryLocation;
        else if (this->size > sizeof(char) && this->memoryLocation != nullptr){
            char* arr = (char*)(this->memoryLocation);
            for(int j = 0; j < this->size/sizeof(char); ++j){
                if(arr[j] != (char)NULL){
                    str += arr[j];
                    str += " ";
                }
            }
        }
    }
    else if (this->type == "float"){
        if(this->size == sizeof(float)) str += std::to_string(*(float*)this->memoryLocation);
        else if (this->size > sizeof(float) && this->memoryLocation != nullptr){
            float* arr = (float*)(this->memoryLocation);
            for(int j = 0; j < this->size/sizeof(float); ++j){
                str += (std::to_string(arr[j]));
                str += " ";
            }
        }
    }
    else if (this->type == "bool"){
        if(this->size == sizeof(bool)) str += std::to_string(*(bool*)this->memoryLocation);
        else if (this->size > sizeof(bool) && this->memoryLocation != nullptr){
            bool* arr = (bool*)(this->memoryLocation);
            for(int j = 0; j < this->size/sizeof(bool); ++j){
                str += (std::to_string(arr[j]));
                str += " ";
            }
        }
    }
    else if (this->type == "string"){
        if(this->memoryLocation != nullptr) {
            if(*((char**)this->memoryLocation) != nullptr) {
                if(this->size == sizeof(char*)) {
                    str += *((char**)this->memoryLocation);
                }
                else if (this->size > sizeof(char*)) {
                    char** arr = (char**)(this->memoryLocation);
                    for(int j = 0; j < this->size/sizeof(char*); ++j){
                        if(arr[j] != nullptr) {
                            str += arr[j];
                            str += " ";
                        }
                    }
                }
            }
            else {
                str += "null";
            }
        }
    }
    else if (this->isUserType) {
        str += "\n\n____user type variable: \n\n";
        str += "type: " + this->type + "\n";
        str += "name: " + this->name + "\n";
        str += "size in bytes: " + std::to_string(this->size) + "\n";
        str += "const: " + std::to_string(this->isConst) + "\n\n";
        str += "__variables: \n";
        for (int i = 0; i < userTypes.size(); ++i) {
            if (userTypes[i].getName() == this->type) {
                int offset = 0;
                for (const VarInfo& var : userTypes[i].getVars()) {
                    str += "name: " + var.getName();
                    str += "\ntype: " + var.getType();
                    str += "\nsize in bytes: " + std::to_string(var.getSize());
                    str += "\nconst: " + std::to_string(var.isConst);
                    str += "\nvalue: ";
                    if (var.getType() == "int") {
                        str += std::to_string(*(int*)((char*)this->memoryLocation + offset));
                    }
                    else if (var.getType() == "char") {
                        str += *(char*)((char*)this->memoryLocation + offset);
                    }
                    else if (var.getType() == "float") {
                        str += std::to_string(*(float*)((char*)this->memoryLocation + offset));
                    }
                    else if (var.getType() == "bool") {
                        str += std::to_string(*(bool*)((char*)this->memoryLocation + offset));
                    }
                    else if (var.getType() == "string") {
                        str += *(((char**)this->memoryLocation + offset));
                    }
                    str += "\n\n";
                    offset += var.getSize();
                }
                break;
            }
        }
        str += "____end of user type variable: ";
    }
    str += "\n\n";
}

void VarInfo::printMembers() const {
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
    case ExprType::CHAR: {
        this->setSize(sizeof(char));
        void* value = malloc(sizeof(char));
        char temp4 = std::get<char>(expr->evaluate());
        memcpy(value, &temp4, sizeof(char));
        this->setValue(value);
        break;
    }
    case ExprType::STRING: {
        this->setSize(sizeof(char**));
        void* value = std::get<char**>(expr->evaluate()); 
        this->setValue(value);
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
    str += "name: " + name;
    str += "\nreturn type: " + type;
    str += "\nparams: ";
    if(params.size() != 0) {
        for (const VarInfo& v : params) {
            str += v.getType() + " " + v.getName();
            if(&v != &params.back()) str += ", ";
        }
    }
    str += "\n\n";
}

// FUNCTIONINFO IMPLEMENTATION ENDS

// BINARYOPNODE IMPLEMENTATION

BinaryOpNode::BinaryOpNode(char oper, const ASTNode* l, const ASTNode* r) {
    if((oper == '+' || oper == '-' || oper == '*' || oper == '/' || oper == '%') && (l->type() == ExprType::BOOLEAN || r->type() == ExprType::BOOLEAN)) {
        yyerror("No arithmetic operations on bool type allowed");
    }
    if((oper == '&' || oper == '|' || oper == '!') && (l->type() != ExprType::BOOLEAN || r->type() != ExprType::BOOLEAN)) {
        yyerror("Logical operations allowed only on bool type");
    }
    if(l->type() == ExprType::STRING || r->type() == ExprType::STRING) {
        yyerror("No operations allowed on string type");
    }
    if(l->type() == ExprType::CHAR || r->type() == ExprType::CHAR) {
        yyerror("No operations allowed on char type");
    }
    this->op = oper;
    this->left = l;
    this->right = r;
}

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
            if constexpr (std::is_same_v<T, float>) {
                yyerror("Cannot use modulo on float");
            } else {
                return ASTNode::ReturnValue(leftValue % rightValue);
            }
            break;
        case '=':
            return ASTNode::ReturnValue(leftValue == rightValue);
        case 'n':
            return ASTNode::ReturnValue(leftValue != rightValue);
        case '<':
            return ASTNode::ReturnValue(leftValue < rightValue);
        case 'l':
            return ASTNode::ReturnValue(leftValue <= rightValue);
        case '>':
            return ASTNode::ReturnValue(leftValue > rightValue);
        case 'g':
            return ASTNode::ReturnValue(leftValue >= rightValue);
        case '&':
            return ASTNode::ReturnValue(leftValue && rightValue);
        case '|':
            return ASTNode::ReturnValue(leftValue || rightValue);
        case '!':
            return ASTNode::ReturnValue(!leftValue);
        default:
            return ASTNode::ReturnValue(0);
    }
    return ASTNode::ReturnValue(0); //safety return
}

ASTNode::ReturnValue BinaryOpNode::evaluate() const {
    if(left->type() != right->type()) {
        error_type_mismatch(left->string_type().c_str(), right->string_type().c_str());
    }
    ExprType type = left->type();
    switch (type) {
        case ExprType::INT:
            return handleOperation(op, std::get<int>(left->evaluate()), std::get<int>(right->evaluate()));
        case ExprType::FLOAT:
            return handleOperation(op, std::get<float>(left->evaluate()), std::get<float>(right->evaluate()));
        case ExprType::BOOLEAN:
            return handleOperation(op, std::get<bool>(left->evaluate()), std::get<bool>(right->evaluate()));
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
        error_type_mismatch(left->string_type().c_str(), right->string_type().c_str());
    }
    if(this->op == '=' || this->op == 'n' || this->op == '<' || this->op == 'l' || this->op == '>' || this->op == 'g' || this->op == '&' || this->op == '|') {
        return ExprType::BOOLEAN;
    }
    else{
        return left->type();
    }
}

string BinaryOpNode::string_type() const {
    if(left->type() != right->type()) {
        error_type_mismatch(left->string_type().c_str(), right->string_type().c_str());
    }
    if(this->op == '=' || this->op == 'n' || this->op == '<' || this->op == 'l' || this->op == '>' || this->op == 'g' || this->op == '&' || this->op == '|') {
        return "bool";
    }
    else{
        return left->string_type();
    }
}

// BINARYOPNODE IMPLEMENTATION ENDS

// FUNCTIONCALLNODE IMPLEMENTATION

FunctionCallNode::FunctionCallNode(string name, vector<ASTNode*>* args) {
    // check if function exists
    if(!symbolTable.functionExists(name)) {
        error_function_not_found(name.c_str());
    }
    // check if number of arguments is correct
    FunctionInfo func = symbolTable.getFunction(name);
    if(func.getParams().size() != args->size()) {
        char errorMsg[100];
        sprintf(errorMsg, "Wrong number of arguments for function %s", name.c_str());
        yyerror(errorMsg);
    }
    // check if types of arguments are correct
    for (int i = 0; i < args->size(); ++i) {
        vector<VarInfo> params = func.getParams();
        if(params[i].getType() != args->at(i)->string_type()) {
            char errorMsg[100];
            sprintf(errorMsg, "Wrong type of argument %d for function %s", i + 1, name.c_str());
            yyerror(errorMsg);
        }
    }
    this->name = name;
    this->params = args;
}

ASTNode::ReturnValue FunctionCallNode::evaluate() const {
    FunctionInfo temp = symbolTable.getFunction(name);
    switch(temp.getType()[0]) {
        case 'i':
            return ReturnValue(0);
        case 'f':
            return ReturnValue(0.0f);
        case 'b':
            return ReturnValue(false);
        case 'c':
            return ReturnValue('0');
        case 's':
            return ReturnValue((char**)nullptr);
        default:
            return ReturnValue(0);
    }
    return ReturnValue(0); //temp 
}

ExprType FunctionCallNode::type() const {
    FunctionInfo func = symbolTable.getFunction(name);
    switch (func.getType()[0]) {
        case 'i':
            return ExprType::INT;
        case 'f':
            return ExprType::FLOAT;
        case 'b':
            return ExprType::BOOLEAN;
        case 'c':
            return ExprType::CHAR;
        case 's':
            return ExprType::STRING;
        default:
            return ExprType::INT;
    }
}

string FunctionCallNode::string_type() const {
    FunctionInfo temp = symbolTable.getFunction(name);
    return temp.getType();
}

// FUNCTIONCALLNODE IMPLEMENTATION ENDS

// VECTORELEMENTNODE IMPLEMENTATION

ASTNode::ReturnValue VectorElementNode::evaluate() const {
    VarInfo var = symbolTable.getVariableReference(name);
    if(strcmp(var.getType().c_str(), "int") == 0){
        void* vals = var.getValueReference();
        int* intVals = (int*)vals;
        return ReturnValue(intVals[index]);
    }
    else if(strcmp(var.getType().c_str(), "bool") == 0){
        void* vals = var.getValueReference();
        bool* boolVals = (bool*)vals;
        return ReturnValue(boolVals[index]);
    }
    else if(strcmp(var.getType().c_str(), "float") == 0){
        void* vals = var.getValueReference();
        float* floatVals = (float*)vals;
        return ReturnValue(floatVals[index]);
    }
    else if(strcmp(var.getType().c_str(), "char") == 0){
        void* vals = var.getValueReference();
        char* charVals = (char*)vals;
        return ReturnValue(charVals[index]);
    }
    else if(strcmp(var.getType().c_str(), "string") == 0){
        void* vals = var.getValueReference();
        char** stringVals = (char**)vals;
        return ReturnValue(&(stringVals[index]));
    }
    return ReturnValue(0);
}

ExprType VectorElementNode::type() const {
    VarInfo var = symbolTable.getVariableReference(name);
    if(strcmp(var.getType().c_str(), "int") == 0) return ExprType::INT;
    else if(strcmp(var.getType().c_str(), "bool") == 0) return ExprType::BOOLEAN; 
    else if(strcmp(var.getType().c_str(), "float") == 0) return ExprType::FLOAT;
    else if(strcmp(var.getType().c_str(), "char") == 0) return ExprType::CHAR;
    else if(strcmp(var.getType().c_str(), "string") == 0) return ExprType::STRING;
    return ExprType::INT;
}

string VectorElementNode::string_type() const {
    VarInfo var = symbolTable.getVariableReference(name);
    return var.getType();
}

// VECTORELEMENTNODE IMPLEMENTATION ENDS

// IDENTIFIERNODE IMPLEMENTATION

ASTNode::ReturnValue IdentifierNode::evaluate() const {
    VarInfo var = symbolTable.getVariableReference(name);
    switch (var.getType()[0]) {
        case 'i':
            return ReturnValue(*(int*)var.getValueReference());
        case 'f':
            return ReturnValue(*(float*)var.getValueReference());
        case 'b':
            return ReturnValue(*(bool*)var.getValueReference());
        case 'c':
            return ReturnValue(*(char*)var.getValueReference());
        case 's':
            return ReturnValue((char**)var.getValueReference());
        default:
            return ReturnValue(0);
    }
    return ReturnValue(0);  
}

ExprType IdentifierNode::type() const {
    VarInfo var = symbolTable.getVariableReference(name);
    switch (var.getType()[0]) {
        case 'i':
            return ExprType::INT;
        case 'f':
            return ExprType::FLOAT;
        case 'b':
            return ExprType::BOOLEAN;
        case 'c':
            return ExprType::CHAR;
        case 's':
            return ExprType::STRING;
        default:
            return ExprType::INT;
    }
}

string IdentifierNode::string_type() const {
    VarInfo var = symbolTable.getVariableReference(name);
    return var.getType();
}

// IDENTIFIERNODE IMPLEMENTATION ENDS

// STRINGNODE IMPLEMENTATION

StringNode::StringNode(char** val) {
    value = new char*[1];
    value[0] = new char[strlen(*val) + 1];
    strcpy(value[0], *val);
}

ASTNode::ReturnValue StringNode::evaluate() const {
    char** copy = new char*[1];
    copy[0] = new char[strlen(*value) + 1];
    strcpy(copy[0], *value);
    return ReturnValue(copy);
}

// STRINGNODE IMPLEMENTATION ENDS

int main(int argc, char** argv){
    yyin=fopen(argv[1],"r");
    yyparse();

    // Print symbol table in file
    symbolTable.saveInFile();
}
