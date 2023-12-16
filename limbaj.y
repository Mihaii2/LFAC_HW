%{
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
void yyerror(const char * s);


class VarInfo {
public:
    string type;
    string name;
    string scope;
    int size = 0;
    void* memoryLocation;

};
class FunctionInfo {
public:
    string type;
    string name;
    string scope;
    vector<VarInfo> params;
};

class UserType {
public:
    string name;
    vector<VarInfo> vars;
    vector<FunctionInfo> methods;

    void addVar(const char* type, const char* name, const char* scope);
    void addMethod(const char* type, const char* name, const char* scope);
    void printMembers();
};


class SymbolTable {
private:
    unordered_map<string, VarInfo> variables;
    unordered_map<string, FunctionInfo> functions;
    std::string currentScope = "::";

public:
    void enterScope(const std::string& scopeName);
    void exitScope();
    string getCurrentScope() { return currentScope; }
    void addVariable(VarInfo var);
    void addFunction(FunctionInfo func);
    bool variableExists(const string& name);
    bool functionExists(const string& name);
    VarInfo getVariable(const string& name);
    FunctionInfo getFunction(const string& name);
    void printTable();
};

SymbolTable symbolTable;
vector<UserType> userTypes;

// USEFUL FUNCTIONS IMPLEMENTATION

VarInfo* createVarInfo(string type, string name, string scope, int arraySize = 0, void* memoryLocation = nullptr) {
    VarInfo* var = new VarInfo();
    var->type = type;
    var->name = name;
    var->scope = scope;
    // Deduct the size from the type
    if (type == "int") {
        var->size = 4;
    } else if (type == "float") {
        var->size = 4;
    } else if (type == "char") {
        var->size = 1;
    } else if (type == "bool") {
        var->size = 1;
    } else if (type == "string") {
        var->size = 1;
    } else {
        // User defined type
        for (const UserType& userType : userTypes) {
            if (userType.name == type) {
                var->size = 0;
                for (const VarInfo& v : userType.vars) {
                    var->size += v.size;
                }
                break;
            }
        }
    }
    // Allocate memory for the variable
    if (arraySize == 0) {
        var->memoryLocation = malloc(var->size);
    }
    else {
        var->memoryLocation = malloc(var->size * arraySize);
        var->size = var->size * arraySize;
    }
    return var;
}

FunctionInfo* createFunctionInfo(string type, string name, string scope, vector<VarInfo> params) {
    FunctionInfo* func = new FunctionInfo();
    func->type = type;
    func->name = name;
    func->scope = scope;
    func->params = params;
    return func;
}

// USEFUL FUNCTIONS IMPLEMENTATION ENDS

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

// SYMBOL TABLE IMPLEMENTATION

void SymbolTable::enterScope(const std::string& scopeName) {
    currentScope += scopeName + "::";
}

void SymbolTable::exitScope() {
    size_t lastScopePos = currentScope.rfind("::");

    if (lastScopePos != std::string::npos) {
        size_t secondLastScopePos = currentScope.rfind("::", lastScopePos - 1);
        if (secondLastScopePos != std::string::npos) {
            currentScope.erase(secondLastScopePos + 2);  // +2 to keep the "::"
        } else {
            currentScope = "::";  // Reset to global scope
        }
    }
}

void SymbolTable::addVariable(VarInfo var) {
    variables[var.name] = var;
}

void SymbolTable::addFunction(FunctionInfo func) {
    functions[func.name] = func;
}

bool SymbolTable::variableExists(const string& name) {
    return variables.find(name) != variables.end();
}

bool SymbolTable::functionExists(const string& name) {
    return functions.find(name) != functions.end();
}

VarInfo SymbolTable::getVariable(const string& name) {
    return variables[name];
}

FunctionInfo SymbolTable::getFunction(const string& name) {
    return functions[name];
}

void SymbolTable::printTable() {
    cout << "Variables: " << endl;
    for (const auto& var : variables) {
        cout << "name: " << var.second.name << "\ntype:" << var.second.type  << "\nscope: " << var.second.scope << "\nsize in bytes: " << var.second.size << "\n\n";
    }
    cout << "Functions: " << endl;
    for (const auto& func : functions) {
        cout << "name: " << func.second.name << "\ntype:" << func.second.type  << "\nscope: " << func.second.scope << "\n\n";
    }
}

// SYMBOL TABLE IMPLEMENTATION ENDS

// USER TYPE IMPLEMENTATION

void UserType::addVar(const char* type, const char* name, const char* scope) {
    VarInfo var;
    var.type = type;
    var.name = name;
    var.scope = scope;
    vars.push_back(var);
}

void UserType::addMethod(const char* type, const char* name, const char* scope) {
    FunctionInfo method;
    method.type = type;
    method.name = name;
    method.scope = scope;
    methods.push_back(method);
}

void UserType::printMembers() {
    cout << "User type name: " << name << endl;
    cout << "Variables: " << endl;
    for (const VarInfo& v : vars) {
        cout << "name: " << v.name << " type:" << v.type << endl;
    }
    cout << "Methods: " << endl;
    for (const FunctionInfo& m : methods) {
        cout << "name: " << m.name << " type:" << m.type << endl;
    }
}

// USER TYPE IMPLEMENTATION ENDS

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
