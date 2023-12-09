%{
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

%}

%union {
    int intValue;
    float floatValue;
    char charValue;
    bool boolValue;
    char* string;
}


%token <intValue> _int
%token <floatValue> _float
%token <charValue> _char
%token <string> _string
%token <boolValue> _bool
%token <string> _id _type
%token _if _while _for  
%token _special_function _end_usr_types _end_global_vars _end_global_funcs
%token _const _usr_type
%token _not _eq _neq _lt _le _gt _ge _assign _plus _minus _mul _div _mod _and _or _geq _leq

%type <floatValue> EXPR T F G H I J VAR

%start program 
%%
// Entry point of the program
program: declarations _end_global_vars user_defined_types _end_usr_types global_function_definitions _end_global_funcs special_function {printf("The programme is correct!\n");}


user_defined_types: /* epsilon */
                    | user_defined_types user_defined_type
                    ;

// User-defined data types
user_defined_type: _usr_type _id '{' usr_type_body '}' {
    printf("User-defined type: %s\n", $2);
    // Code to handle user-defined types
    // You can store the type information in a symbol table or generate C++ code for the type
}

usr_type_body: /* epsilon */
            | usr_type_body member
            ;

member: _type _id ';'
            | _type _id '(' list_param ')' '{' statements '}'
            ;

// Global variables
declarations : decl ';'
                | declarations  decl ';'
                ;

decl: _type _id {
    printf("Variable: %s, name: %s\n", $1, $2);
    // Code to handle global variable declarations
    // You can store the variable information in a symbol table or generate C++ code for the variable
    // Access the variable using $$ = $2;
    }
        | _const _type _id '=' CONST_VAL {
            // Code to handle global constant declarations
            // You can store the constant information in a symbol table or generate C++ code for the constant
            // Access the constant using $$ = $4;
        }

CONST_VAL: _int
            | _float
            | _char
            | _string
            | _bool
            ;

// Function definitions
global_function_definitions: /* epsilon */
                            | global_function_definitions global_function_definition
                            ;

global_function_definition: _type _id '(' list_param ')' '{' statements '}' {
    // Code to handle function definitions
    // You can store the function information in a symbol table or generate C++ code for the function
    // Access the function using $$ = $2;
}

list_param: /* epsilon */
            | list_param param
            ;

param: _type _id {
    // Code to handle function parameters
    // You can store the parameter information in a symbol table or generate C++ code for the parameter
}




statements: /* epsilon */
            | statements statement
            ;

statement: assignment_statement
            | control_statement
            | function_call_statement
            ;

assignment_statement: left_value _assign EXPR ';'  {cout << "Expression value: " << $3 << endl;}

left_value: _id
            | array_element_access
            ;

array_element_access: _id '[' EXPR ']'

control_statement: if_statement
                    | for_statement
                    | while_statement
                    ;

if_statement: _if '(' EXPR ')' '{' statements '}' {
    // Code to handle if statements
    // You can generate C++ code for the if statement
}

for_statement: _for '(' assignment_statement ';' EXPR ';' assignment_statement ')' '{' statements '}' {
    // Code to handle for statements
    // You can generate C++ code for the for statement
}

while_statement: _while '(' EXPR ')' '{' statements '}' {
    // Code to handle while statements
    // You can generate C++ code for the while statement
}

function_call_statement: function_call ';'

function_call: _id '(' arguments ')'

arguments: /* epsilon */
            | arguments_list
            ;

arguments_list: EXPR 
                | function_call
                | arguments_list ',' EXPR 
                ;

EXPR: EXPR _and T { $$ = ($1 && $3); cout << "e && e" << " : " <<$$ <<endl; }
    | EXPR _or T {($1 || $3); cout << "e || e" << " : " <<$$ <<endl; }
    | T { $$ = $1;}
    ;
T : T _eq F { $$ = ($1 == $3); cout << "e == e" << ": " <<$$ <<endl; }
    | T _neq F { $$ = ($1 != $3); cout << "e != e" << ": " <<$$ <<endl; }
    | F { $$ = $1;}
    ;
F : F _lt G { $$ = ($1 < $3); cout << "e < e" << ": " <<$$ <<endl; }
    | F _le G { $$ = ($1 <= $3); cout << "e <= e" << ": " <<$$ <<endl; }
    | F _gt G { $$ = ($1 > $3); cout << "e > e" << ": " <<$$ <<endl; }
    | F _ge G { $$ = ($1 >= $3); cout << "e >= e" << ": " <<$$ <<endl; }
    | G { $$ = $1;}
    ;
G : G _plus H { $$ = ($1 + $3); cout << "e + e" << " : " <<$$ <<endl; }
    | G _minus H { $$ = ($1 - $3); cout << "e - e" << " : " <<$$ <<endl; }
    | H { $$ = $1;}
    ;
H : H _mul I { $$ = ($1 * $3); cout << "e * e" << " : " <<$$ <<endl; }
    | H _div I { $$ = ($1 / $3); cout << "e / e" << " : " <<$$ <<endl; }
    | H _mod I { $$ = (float)((int)$1 % (int)$3); cout << "e % e" << " : " <<$$ <<endl; }
    | I { $$ = $1;}
    ;
I : _not J { $$ = !$2; cout << "!e" << " : " <<$$ <<endl; }
    | J { $$ = $1;}
    ;
J : VAR { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | _int { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | _float { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | _bool { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | '(' EXPR ')' { $$ = $2; cout << "e->(e)" <<$2<< " : " <<$$ <<endl; }
    ;

VAR : _id {$$ = 0 /* add code to retreive variable value */; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    ;

special_function: _special_function '(' ')' '{' statements '}'
%%

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
