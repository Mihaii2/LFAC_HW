%{
#include <iostream>
#include <string>
#include <vector>
using namespace std;

// User-defined data types
class MyClass {
public:
    int myField;
    void myMethod() {
        cout << "Hello from myMethod!" << endl;
    }
};

// Global variables
int globalVar;

// Function declarations
void globalFunction(int param);

%}

%union {
    int intValue;
    float floatValue;
    char charValue;
    string stringValue;
    bool boolValue;
    MyClass* classValue;
}

%token <intValue> INT
%token <floatValue> FLOAT
%token <charValue> CHAR
%token <stringValue> STRING
%token <boolValue> BOOL
%token ID TYPE 

%type <intValue> expression
%type <boolValue> boolean_expression
%type <classValue> user_defined_type

%%
// Entry point of the program
program: user_defined_types 'END_USR_TYPES' global_variables 'END_GLOBAL_VAR' global_function_definitions 'END_GLOBAL_FUNC' special_function



// User-defined data types
user_defined_type: 'class' ID '{' class_body '}' {
    // Code to handle user-defined types
    // You can store the type information in a symbol table or generate C++ code for the type
}

class_body: /* epsilon */
            | class_body class_member
            ;

class_member: TYPE ID ';'
            | TYPE ID '(' parameters ')' '{' statements '}'
            ;

// Global variables
global_variables: global_variable
                | global_variables global_variable
                ;

global_variable: TYPE ID {
    // Code to handle global variable declarations
    // You can store the variable information in a symbol table or generate C++ code for the variable
    // Access the variable using $$ = $2;
}

// Function definitions
global_function_definitions: global_function_definition
                            | global_function_definitions global_function_definition
                            ;

global_function_definition: TYPE ID '(' parameters ')' '{' statements '}' {
    // Code to handle function definitions
    // You can store the function information in a symbol table or generate C++ code for the function
    // Access the function using $$ = $2;
}

parameters: /* epsilon */
            | parameters parameter
            ;

parameter: TYPE ID {
    // Code to handle function parameters
    // You can store the parameter information in a symbol table or generate C++ code for the parameter
}




statements: /* epsilon */
            | statement
            | statements statement
            ;

statement: assignment_statement
            | control_statement
            | function_call_statement
            ;

assignment_statement: left_value '=' expression {
    // Code to handle assignment statements
    // You can generate C++ code for the assignment
}

left_value: ID
            | array_element_access
            ;

array_element_access: ID '[' expression ']'

control_statement: if_statement
                    | for_statement
                    | while_statement
                    ;

if_statement: 'if' '(' boolean_expression ')' '{' statements '}' {
    // Code to handle if statements
    // You can generate C++ code for the if statement
}

for_statement: 'for' '(' assignment_statement ';' boolean_expression ';' assignment_statement ')' '{' statements '}' {
    // Code to handle for statements
    // You can generate C++ code for the for statement
}

while_statement: 'while' '(' boolean_expression ')' '{' statements '}' {
    // Code to handle while statements
    // You can generate C++ code for the while statement
}

function_call_statement: function_call ';'

function_call: ID '(' arguments ')'

arguments: /* epsilon */
            | argument_list
            ;

argument_list: expression
                | argument_list ',' expression
                ;

// Arithmetic expressions
expression: INT
            | FLOAT
            | CHAR
            | STRING
            | boolean_expression
            | user_defined_type
            | ID
            | expression '+' expression
            | expression '-' expression
            | expression '*' expression
            | expression '/' expression
            | '(' expression ')'
            ;

// Boolean expressions
boolean_expression: BOOL
            | expression '<' expression
            | expression '>' expression
            | expression '<=' expression
            | expression '>=' expression
            | expression '==' expression
            | expression '!=' expression
            | '!' boolean_expression
            | boolean_expression '&&' boolean_expression
            | boolean_expression '||' boolean_expression
            | '(' boolean_expression ')'
            ;

special_function: 'clean_code_executer' '(' ')' '{' statements '}'

%%

// Function to evaluate expressions
void Eval(arg) {
    // Code to evaluate expressions
    // You can generate C++ code for evaluating the expression
}

// Function to get the type of an expression
void TypeOf(arg) {
    // Code to get the type of an expression
    // You can generate C++ code for getting the type
}

// Function to handle global function calls
void globalFunction(int param) {
    // Code to handle global function calls
    // You can generate C++ code for the function call
}

%%

int yucc() {
    yyparse();
    return 0;
}

int yyerror(const char* msg) {
    cout << "Error: " << msg << endl;
    return 0;
}
