%{
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
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
    bool isConst = false;
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
    void saveInFile();
};

SymbolTable symbolTable;
vector<UserType> userTypes;

// USEFUL FUNCTIONS IMPLEMENTATION

VarInfo* createVarInfo(string type, string name, string scope, bool is_const = false, int arraySize = 1, void* memoryLocation = nullptr) {
    VarInfo* var = new VarInfo();
    var->type = type;
    var->name = name;
    var->scope = scope;
    var->isConst = is_const;
    // Deduct the size from the type
    if (type == "int" || type == "float") {
        var->size = 4;
    } 
    else if (type == "char" || type == "bool" || type == "string") {
        var->size = 1;
    }
    else {
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
    var->memoryLocation = malloc(var->size * arraySize);
    var->size = var->size * arraySize;
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
    VarInfo* createVarInfo(string type, string name, string scope, bool is_const, int arraySize, void* memoryLocation);
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
//%type<boolValue> e_bool
%type<var> variable

%left AND OR
%left LT LE GT GE EQ NEQ
%left PLUS MINUS
%left MUL DIV MOD
%right NOT
%start program 

%%

program: user_defined_types END_USR_TYPES declarations END_GLOBAL_VARS global_function_definitions END_GLOBAL_FUNCS special_function {printf("The programm is correct!\n");}

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
            VarInfo* var = createVarInfo($2, $3, symbolTable.getCurrentScope(), true);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID ASSIGN expr {
            VarInfo* var = createVarInfo($1, $2, symbolTable.getCurrentScope());
            //var->memoryLocation = malloc(sizeof(int)) // Hmm, am putea sa luam 4 octeti ca sa pastram orice tip de variabila? 
            // int/char/bool/float/string * name = (respectiv int/char/bool/float/string *) memoryLocation;
            // name = const_val;

            // Probabil va trebui sa inlocuim const_val cu fiecare tip de date?
            // Ex: TYPE ID ASSIGN INT {...} 
            //     | TYPE ID ASSIGN BOOL {...} // Si in asa mod pentru fiecare regula.
            // Pentru ca trebuie sa stim ce tip de valoare asignam variabilei,
            // dar problema e ca si nu putem atribui neterminalului const_val un tip concret (cred).
            $$ = var;
            symbolTable.addVariable(*var);
    }
    
    | CONST TYPE ID ASSIGN expr { // Ne da un warning din cauza ca ambele expr si const_val pot fi INT, dar nu cred ca e o problema
            VarInfo* var = createVarInfo($2, $3, symbolTable.getCurrentScope(), true);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID '[' INT ']' {
            VarInfo* var = createVarInfo($1, $2, symbolTable.getCurrentScope(), false, $4);
            $$ = var;
            symbolTable.addVariable(*var);

    }
    | TYPE ID '[' INT ']' ASSIGN '{' const_vals '}' {
            VarInfo* var = createVarInfo($1, $2, symbolTable.getCurrentScope(), false, $4);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID '[' INT ']' '[' INT ']' {
            VarInfo* var = createVarInfo($1, $2, symbolTable.getCurrentScope(), false, $4 * $7);
            $$ = var;
            symbolTable.addVariable(*var);}
    | TYPE ID '[' INT ']' '[' INT ']' ASSIGN '{' const_vals '}' {
            VarInfo* var = createVarInfo($1, $2, symbolTable.getCurrentScope(), false, $4 * $7);
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

if_statement: IF '[' ID ']' '(' expr ')' '{' statements '}' {
        std::vector<VarInfo> no_params;
        FunctionInfo* func = createFunctionInfo("if", $3, symbolTable.getCurrentScope(), no_params);
        symbolTable.addFunction(*func);
    }
    | IF '[' ID ']' '(' e_bool ')' '{' statements '}' {
        std::vector<VarInfo> no_params;
        FunctionInfo* func = createFunctionInfo("if", $3, symbolTable.getCurrentScope(), no_params);
        symbolTable.addFunction(*func);
        //if($6){
            //exec statements
        //}
    }
    ;

for_statement: FOR '[' ID ']' '(' assignment_statement ';' expr ';' assignment_statement ')' '{' statements '}'
    ;

while_statement: WHILE '[' ID ']' '(' expr ')' '{' statements '}'
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

expr: expr PLUS expr {/*$$ = $1 + $3*/}
    | expr MINUS expr {/*$$ = $1 - $3*/}
    | expr MUL expr {/*$$ = $1 * $3*/}
    | expr DIV expr {/*$$ = $1 / $3*/}
    | expr MOD expr {/*$$ = $1 % $3*/}
    | variable  {/*if(strstr($1.scope, symbolTable.getCurrentScope()) != NULL) $$ = $1*/}
    | INT {/*$$ = $1*/}
    | FLOAT {/*$$ = $1*/}
    | CHAR {/*$$ = $1*/}
    | STRING {/*$$ = $1*/}
    | BOOL {/*$$ = $1*/}
    | '(' expr ')'
    ;

variable : ID { // va returna un VarInfo
        /*for (const auto& var : variables) {
            if(var.second.name == $1) $$ = var; // verificam daca se afla in scope-ul necesar deja in expr
        }*/
    }
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
        cout << "name: " << var.second.name << "\ntype: " << var.second.type  << "\nconst: " << var.second.isConst << "\nscope: " << var.second.scope << "\nsize in bytes: " << var.second.size << "\n\n";
    }
    cout << "Functions: " << endl;
    for (const auto& func : functions) {
        cout << "name: " << func.second.name << "\ntype:" << func.second.type  << "\nscope: " << func.second.scope << "\n\n";
    }

}

void SymbolTable::saveInFile(){
    int fd;
    if((fd = open("symbolTable.txt", O_RDWR | O_CREAT | O_TRUNC, 0666)) == -1){
        perror("Eroare la open fisier symbol table\n");
    }
    std::string st_data = "Variables:\n";
    for (const auto& var : variables) {
        st_data += "name: ";
        st_data += var.second.name;
        st_data += "\ntype: ";
        st_data += var.second.type;
        st_data += "\nconst: ";
        st_data += var.second.isConst + '0';
        st_data += "\nscope: ";
        st_data += var.second.scope;
        st_data += "\nsize in bytes: ";
        st_data += var.second.size + '0';
        st_data += "\n\n";
    }
    st_data += "Functions:\n";
    for (const auto& func : functions) {
        st_data += "name: ";
        st_data += func.second.name;
        st_data += "\ntype: ";
        st_data += func.second.type; 
        st_data += "\nscope: ";
        st_data += func.second.scope;
        st_data += "\n\n";
    }
    if(write(fd, st_data.c_str(), st_data.length()) == -1) perror("Eroare la write in fisier symbol table\n");
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
        cout << "name: " << v.name << " type:" << v.type << "const: " << v.isConst << endl;
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
    symbolTable.saveInFile();
}
