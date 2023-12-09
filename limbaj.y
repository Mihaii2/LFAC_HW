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


%token <intValue> INT
%token <floatValue> FLOAT
%token <charValue> CHAR
%token <string> STRING
%token <boolValue> BOOL
%token <string> ID TYPE
%token IF ELSE WHILE FOR  
%token SPECIAL_FUNCTION END_USR_TYPES END_GLOBAL_VARS END_GLOBAL_FUNCS
%token CONST USR_TYPE
%token NOT EQ NEQ LT LE GT GE ASSIGN PLUS MINUS MUL DIV 0 MOD AND OR
%type <floatValue> expr T F G H I J VAR

%start program 
%%
// Entry point of the program
program: declarations END_GLOBAL_VARS user_defined_types END_USR_TYPES global_function_definitions END_GLOBAL_FUNCS special_function {printf("The programme is correct!\n");}


user_defined_types: /* epsilon */
                    | user_defined_types user_defined_type
                    ;

// User-defined data types
user_defined_type: USR_TYPE ID '{' usr_type_body '}' {
    printf("User-defined type: %s\n", $2);
    // Code to handle user-defined types
    // You can store the type information in a symbol table or generate C++ code for the type
}

usr_type_body: /* epsilon */
            | usr_type_body member
            ;

member: TYPE ID ';'
            | TYPE ID '(' list_param ')' '{' statements '}'
            ;

// Global variables
declarations : decl ';'
                | declarations  decl ';'
                ;

decl: TYPE ID {
    printf("Variable: %s, name: %s\n", $1, $2);
    // Code to handle global variable declarations
    // You can store the variable information in a symbol table or generate C++ code for the variable
    // Access the variable using $$ = $2;
    }
        | CONST TYPE ID '=' CONST_VAL {
            // Code to handle global constant declarations
            // You can store the constant information in a symbol table or generate C++ code for the constant
            // Access the constant using $$ = $4;
        }

CONST_VAL: INT
            | FLOAT
            | CHAR
            | STRING
            | BOOL
            ;

// Function definitions
global_function_definitions: /* epsilon */
                            | global_function_definitions global_function_definition
                            ;

global_function_definition: TYPE ID '(' list_param ')' '{' statements '}' {
    // Code to handle function definitions
    // You can store the function information in a symbol table or generate C++ code for the function
    // Access the function using $$ = $2;
}

list_param: /* epsilon */
            | list_param param
            ;

param: TYPE ID {
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

assignment_statement: left_value ASSIGN expr ';'  {cout << "Expression value: " << $3 << endl;}

left_value: ID
            | array_element_access
            ;

array_element_access: ID '[' expr ']'

control_statement: if_statement
                    | for_statement
                    | while_statement
                    ;

if_statement: IF '(' expr ')' '{' statements '}' {
    // Code to handle if statements
    // You can generate C++ code for the if statement
}

for_statement: FOR '(' assignment_statement ';' expr ';' assignment_statement ')' '{' statements '}' {
    // Code to handle for statements
    // You can generate C++ code for the for statement
}

while_statement: WHILE '(' expr ')' '{' statements '}' {
    // Code to handle while statements
    // You can generate C++ code for the while statement
}

function_call_statement: function_call ';'

function_call: ID '(' arguments ')'

arguments: /* epsilon */
            | arguments_list
            ;

arguments_list: expr 
                | arguments_list ',' expr 
                ;

expr: expr AND T { $$ = ($1 && $3); cout << "e && e" << " : " <<$$ <<endl; }
    | expr OR T {($1 || $3); cout << "e || e" << " : " <<$$ <<endl; }
    | T { $$ = $1;}
    ;
T : T EQ F { $$ = ($1 == $3); cout << "e == e" << ": " <<$$ <<endl; }
    | T NEQ F { $$ = ($1 != $3); cout << "e != e" << ": " <<$$ <<endl; }
    | F { $$ = $1;}
    ;
F : F LT G { $$ = ($1 < $3); cout << "e < e" << ": " <<$$ <<endl; }
    | F LE G { $$ = ($1 <= $3); cout << "e <= e" << ": " <<$$ <<endl; }
    | F GT G { $$ = ($1 > $3); cout << "e > e" << ": " <<$$ <<endl; }
    | F GE G { $$ = ($1 >= $3); cout << "e >= e" << ": " <<$$ <<endl; }
    | G { $$ = $1;}
    ;
G : G PLUS H { $$ = ($1 + $3); cout << "e + e" << " : " <<$$ <<endl; }
    | G MINUS H { $$ = ($1 - $3); cout << "e - e" << " : " <<$$ <<endl; }
    | H { $$ = $1;}
    ;
H : H MUL I { $$ = ($1 * $3); cout << "e * e" << " : " <<$$ <<endl; }
    | H DIV I { $$ = ($1 / $3); cout << "e / e" << " : " <<$$ <<endl; }
    | H MOD I { $$ = (float)((int)$1 % (int)$3); cout << "e % e" << " : " <<$$ <<endl; }
    | I { $$ = $1;}
    ;
I : NOT J { $$ = !$2; cout << "!e" << " : " <<$$ <<endl; }
    | J { $$ = $1;}
    ;
J : VAR { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | INT { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | FLOAT { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | BOOL { $$ = $1; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    | '(' expr ')' { $$ = $2; cout << "e->(e)" <<$2<< " : " <<$$ <<endl; }
    ;

VAR : ID {$$ = 0 /* add code to retreive variable value */; cout << "e->" <<$1<< " : " <<$$ <<endl; }
    ;

special_function: SPECIAL_FUNCTION '(' ')' '{' statements '}'
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
