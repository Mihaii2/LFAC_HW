%{
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "usefulFunctions.h"
#include "varInfo.h"
#include "functionInfo.h"
#include "symbolTable.h"
using namespace std;
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);

SymbolTable symbolTable;
vector<UserType> userTypes;

%}

%define parse.error verbose
%define parse.trace

%code requires {
    #include <vector>
    #include <string>
    using namespace std;
    class VarInfo;
    class FunctionInfo;
    VarInfo* createVarInfo(string type, string name, string scope, int arraySize, void* memoryLocation);
}

%union {
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

}

%token <intValue> INT
%token <floatValue> FLOAT
%token <charValue> CHAR
%token <string> STRING
%token <boolValue> BOOL
%token <string> ID TYPE
%token IF WHILE FOR  
%token SPECIAL_FUNCTION END_USR_TYPES END_USR_TYPE_VARS END_GLOBAL_VARS END_GLOBAL_FUNCS
%token CONST USR_TYPE
%token NOT EQ NEQ LT LE GT GE ASSIGN PLUS MINUS MUL DIV MOD AND OR GEQ LEQ

%type<vars> usr_type_vars list_param func_param
%type<funcs> usr_type_methods
%type<var> usr_type_var param decl
%type<func> usr_type_method



%left AND OR
%left LT LE GT GE EQ NEQ
%left PLUS MINUS
%left MUL DIV MOD
%right NOT
%start program 

%%

program: user_defined_types END_USR_TYPES declarations END_GLOBAL_VARS global_function_definitions END_GLOBAL_FUNCS special_function {printf("The programme is correct!\n");}

user_defined_types: /* epsilon */
                    | user_defined_types user_defined_type
                    ;

user_defined_type: USR_TYPE ID '{' { symbolTable.enterScope(string($2)); 
    cout<<"Current scope: "<<symbolTable.getCurrentScope()<<endl;
 } usr_type_vars END_USR_TYPE_VARS usr_type_methods '}' { symbolTable.exitScope(); 
    cout<<"Current scope: "<<symbolTable.getCurrentScope()<<endl; } {
                        UserType userType;
                        userType.name = string($2);
                        userType.vars = *$5;
                        userType.methods = *$7;
                        userTypes.push_back(userType);
                    }
                    ;

usr_type_vars: /* epsilon */ {
                    $$ = new vector<VarInfo>();
                }
                | usr_type_vars usr_type_var ';'{
                    $$ = $1;
                    $$->push_back(*$2);
                    delete($2);
                }
                ;

usr_type_var: TYPE ID {
                    VarInfo* var = createVarInfo($1, $2, symbolTable.getCurrentScope());
                    $$ = var;
                    symbolTable.addVariable(*var);
                }
                ;

usr_type_methods: /* epsilon */ {
                    $$ = new vector<FunctionInfo>();
                }
                | usr_type_methods usr_type_method {
                    $$ = $1;
                    $$->push_back(*$2);
                    delete($2);
                }
                ;

usr_type_method: TYPE ID '(' func_param ')' '{' statements '}' {
                    FunctionInfo* func = createFunctionInfo($1, $2, symbolTable.getCurrentScope(), *$4);
                    $$ = func;
                    symbolTable.addFunction(*func);
                }
                ;

declarations : decl ';' 
    | declarations  decl ';'
    ;

decl: TYPE ID {
            VarInfo* var = createVarInfo($1, $2, symbolTable.getCurrentScope());
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | CONST TYPE ID {
            VarInfo* var = createVarInfo($2, $3, symbolTable.getCurrentScope());
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID ASSIGN const_val {
            VarInfo* var = createVarInfo($1, $2, symbolTable.getCurrentScope());
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | CONST TYPE ID ASSIGN const_val {
            VarInfo* var = createVarInfo($2, $3, symbolTable.getCurrentScope());
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID '[' INT ']' {
            VarInfo* var = createVarInfo($1, $2, symbolTable.getCurrentScope(), $4);
            $$ = var;
            symbolTable.addVariable(*var);

    }
    | TYPE ID '[' INT ']' ASSIGN '{' const_vals '}' {
            VarInfo* var = createVarInfo($1, $2, symbolTable.getCurrentScope(), $4);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID '[' INT ']' '[' INT ']' {
            VarInfo* var = createVarInfo($1, $2, symbolTable.getCurrentScope(), $4 * $7);
            $$ = var;
            symbolTable.addVariable(*var);}
    | TYPE ID '[' INT ']' '[' INT ']' ASSIGN '{' const_vals '}' {
            VarInfo* var = createVarInfo($1, $2, symbolTable.getCurrentScope(), $4 * $7);
            $$ = var;
            symbolTable.addVariable(*var);
    }

const_vals : const_vals ',' const_val{}
           | const_val

const_val: INT
    | FLOAT
    | CHAR
    | STRING
    | BOOL
    ;

global_function_definitions: /* epsilon */
    | global_function_definitions global_function_definition
    ;

global_function_definition: TYPE ID '(' func_param ')' '{' statements '}' 
    ;

func_param: /* epsilon */ {
                $$ = new vector<VarInfo>();
            }
            | list_param {
                $$ = $1;
            }
    ;

list_param: param {
                    $$ = new vector<VarInfo>();
                    $$->push_back(*$1);
                    delete($1);
                }
                | list_param ',' param {
                    $$ = $1;
                    $$->push_back(*$3);
                    delete($3);
                }
                ;

param: TYPE ID {
            VarInfo* var = createVarInfo($1, $2, symbolTable.getCurrentScope());
            var->scope = symbolTable.getCurrentScope();
            $$ = var;
        }
        ;

statements: /* epsilon */
    | statements statement
    ;

statement: assignment_statement 
    | decl ';' 
    | control_statement
    | function_call_statement 
    ;

assignment_statement: left_value ASSIGN expr ';' 

left_value: ID
    | array_element_access 
    ;

array_element_access: ID '[' expr ']'
    ;

control_statement: if_statement 
    | for_statement
    | while_statement 
    ;

if_statement: IF '(' expr ')' '{' statements '}'
    | IF '(' e_bool ')' '{' statements '}' 
    ;

for_statement: FOR '(' assignment_statement ';' expr ';' assignment_statement ')' '{' statements '}'
    ;

while_statement: WHILE '(' expr ')' '{' statements '}'
    ;

function_call_statement: function_call ';' 

function_call: ID '(' arguments ')' 

arguments: /* epsilon */
    | arg_list
    ;

arg_list: expr 
    | function_call
    | arg_list ',' expr 
    ;

expr: expr PLUS expr
    | expr MINUS expr
    | expr MUL expr
    | expr DIV expr
    | expr MOD expr
    | var  
    | INT
    | '(' expr ')'
    ;

var : ID
    ;

e_bool: expr EQ expr
    | expr NEQ expr
    | expr LT expr
    | expr LE expr
    | expr GT expr
    | expr GE expr
    | e_bool AND e_bool
    | e_bool OR e_bool
    | '(' e_bool ')'
    ;

special_function: SPECIAL_FUNCTION '(' ')' '{' statements '}'
%%

void yyerror(const char * s){
    printf("error: %s at line:%d\n",s,yylineno);
}



int main(int argc, char** argv){
    yyin=fopen(argv[1],"r");
    yyparse();

    // Print user types
    for (UserType& userType : userTypes) {
        userType.printMembers();
    }

    cout<<"\n\nSymbol Table: \n\n";
    // Print symbol table
    symbolTable.printTable();
}
