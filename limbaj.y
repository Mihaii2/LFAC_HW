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
    string type;
    string name;
    bool isConst = false;
    int size = 0;
    void* memoryLocation;
public:

    VarInfo() {}
    VarInfo(string type, string name, bool is_const = false, int arraySize = 1, void* memoryLocation = nullptr);
    string getName() const { return name; }
    string getType() const { return type; }
    void write_to_string(string &str) const;

};
class FunctionInfo {
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
public:
    string name;
    vector<VarInfo> vars;
    vector<FunctionInfo> methods;

    void addVar(const char* type, const char* name, const char* scope);
    void addMethod(const char* type, const char* name, const char* scope);
    void printMembers();
    UserType() {}
    UserType(string name, vector<VarInfo> vars, vector<FunctionInfo> methods);
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
                        UserType userType = UserType($2, *$5, *$7);
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
                    VarInfo* var = new VarInfo($1, $2);
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
                    FunctionInfo* func = new FunctionInfo($1, $2, *$4);
                    $$ = func;
                    symbolTable.addFunction(*func);
                }
                ;

declarations : decl ';' 
    | declarations  decl ';'
    ;

decl: TYPE ID {
            VarInfo* var = new VarInfo($1, $2);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | CONST TYPE ID {
            VarInfo* var = new VarInfo($2, $3, true);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID ASSIGN expr {
            VarInfo* var = new VarInfo($1, $2);
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
    
    | CONST TYPE ID ASSIGN expr { 
            VarInfo* var = new VarInfo($2, $3, true);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID '[' INT ']' {
            VarInfo* var = new VarInfo($1, $2, false, $4);
            $$ = var;
            symbolTable.addVariable(*var);

    }
    | TYPE ID '[' INT ']' ASSIGN '{' const_vals '}' {
            VarInfo* var = new VarInfo($1, $2, false, $4);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID '[' INT ']' '[' INT ']' {
            VarInfo* var = new VarInfo($1, $2, false, $4 * $7);
            $$ = var;
            symbolTable.addVariable(*var);}
    | TYPE ID '[' INT ']' '[' INT ']' ASSIGN '{' const_vals '}' {
            VarInfo* var = new VarInfo($1, $2, false, $4 * $7);
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
            VarInfo* var = new VarInfo($1, $2);
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
        perror("Eroare la open fisier symbol table\n");
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
    if(write(fd, st_data.c_str(), st_data.length()) == -1) perror("Eroare la write in fisier symbol table\n");
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

VarInfo::VarInfo(string type, string name, bool is_const, int arraySize, void* memoryLocation) {
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
            if (userType.name == type) {
                this->size = 0;
                for (const VarInfo& v : userType.vars) {
                    this->size += v.size;
                }
                break;
            }
        }
    }
    // Allocate memory for the variable
    this->memoryLocation = malloc(this->size * arraySize);
    this->size = this->size * arraySize;
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
    string size = std::to_string(this->size);
    str += size;
    str += "\n\n";
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
    for (const VarInfo& v : params) {
        str += v.getType();
        str += " ";
        str += v.getName();
        str += ", ";
    }
    str += "\n\n";
}

// FUNCTIONINFO IMPLEMENTATION ENDS

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
