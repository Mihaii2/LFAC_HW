%{
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

%}

%define parse.error verbose
%define parse.trace

%code requires {
    #include <vector>
    #include <string>
    using namespace std;
    class VarInfo;
    class FunctionInfo;
    class ASTNode;
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
    ASTNode* node;
    std::vector<ASTNode*>* nodes;
}

%token <intValue> INT
%token <floatValue> FLOAT
%token <charValue> CHAR
%token <string> STRING
%token <boolValue> BOOL
%token <string> ID TYPE SPECIAL_FUNCTION USR_TYPE
%token IF WHILE FOR  
%token END_USR_TYPES END_USR_TYPE_VARS END_GLOBAL_VARS END_GLOBAL_FUNCS
%token CONST EVAL TYPEOF RETURN
%token NOT EQ NEQ LT LE GT GE ASSIGN PLUS MINUS MUL DIV MOD AND OR GEQ LEQ

%type<vars> usr_type_vars list_param func_param
%type<funcs> usr_type_methods
%type<var> usr_type_var param decl
%type<func> usr_type_method
%type<node> expr function_call
%type<nodes> expressions arguments arg_list initializer_list


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

user_defined_type: USR_TYPE ID '{' {symbolTable.enterScope(string($2));} usr_type_vars END_USR_TYPE_VARS usr_type_methods '}' { symbolTable.exitScope();} {
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

usr_type_method: TYPE ID '(' func_param ')' '{' {symbolTable.enterScope(string($2));} statements '}' {symbolTable.exitScope();} {
                    FunctionInfo* func = new FunctionInfo($1, $2, *$4);
                    $$ = func;
                    symbolTable.addFunction(*func);
                }
                ;

declarations : decl ';' 
    | declarations  decl ';'
    ;

decl: TYPE ID {
            if(symbolTable.variableExists($2)) {
                error_variable_exists($2);
            }
            VarInfo* var = new VarInfo($1, $2);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | CONST TYPE ID {
            if(symbolTable.variableExists($3)) {
                error_variable_exists($3);
            }
            VarInfo* var = new VarInfo($2, $3, true);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID ASSIGN expr {
            if(symbolTable.variableExists($2)) {
                error_variable_exists($2);   
            }
            if (strcmp($4->string_type().c_str(), $1) != 0){                
                error_different_types($1, $4->string_type().c_str());
            }
            VarInfo* var = new VarInfo($1, $2, false);
            var->assign_expr($4);
            free($4);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | CONST TYPE ID ASSIGN expr { 
            if(symbolTable.variableExists($3)) {
                error_variable_exists($3);
            }
            if (strcmp($2, $5->string_type().c_str()) != 0){
                error_different_types($2, $5->string_type().c_str());
            }
            VarInfo* var = new VarInfo($2, $3, true);
            var->assign_expr($5);
            free($5);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID '[' expr ']' {
            if($4->string_type() != "int") yyerror("Array size specifier is not an integer");
            if(symbolTable.variableExists($2)) {
                error_variable_exists($2);
            }
            VarInfo* var = new VarInfo($1, $2, false, get<int>($4->evaluate()));
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID '[' expr ']' ASSIGN '{' expressions '}' {
            if($4->string_type() != "int") yyerror("Array size specifier is not an integer");
            if(symbolTable.variableExists($2)) {
                error_variable_exists($2);
            }
            int nr_elements = $8->size();
            if((std::get<int>($4->evaluate())) < nr_elements) {
                yyerror("Array size is smaller than the number of elements provided");
            }
            
            ASTNode::ReturnValue values[nr_elements];
            
            for(int i = 0; i < nr_elements; ++i){
                ASTNode* node = (*$8)[i];
                if(strcmp(node->string_type().c_str(), $1) != 0){
                    error_different_types($1, node->string_type().c_str());
                }
                values[i] = node->evaluate();
            }

            VarInfo* var = new VarInfo($1, $2, false, get<int>($4->evaluate()));
            
            if(strcmp($1, "int") == 0){
                    int* intVals = new int[nr_elements];
                    for(int i = 0; i < nr_elements; ++i){
                        intVals[i] = std::get<int>(values[i]);
                    }
                    var->setValue((void*)intVals);
            }
            else if (strcmp($1, "bool") == 0){
                    bool* boolVals = new bool[nr_elements];
                    for(int i = 0; i < nr_elements; ++i){
                        boolVals[i] = std::get<bool>(values[i]);
                    }
                    var->setValue((void*)boolVals);
            }               
            else if (strcmp($1, "char") == 0){
                    char* charVals = new char[nr_elements];
                    for(int i = 0; i < nr_elements; ++i){
                        charVals[i] = std::get<char>(values[i]);
                    }
                    var->setValue((void*)charVals);
            }
            else if (strcmp($1, "float") == 0){    
                    float* floatVals = new float[nr_elements];
                    for(int i = 0; i < nr_elements; ++i){
                        floatVals[i] = std::get<float>(values[i]);
                    }
                    var->setValue((void*)floatVals);
            }    
            else if (strcmp($1, "string") == 0){
                    char** stringVals = new char*[nr_elements];
                    for(int i = 0; i < nr_elements; ++i){
                        stringVals[i] = *(std::get<char**>(values[i]));
                    }
                    var->setValue((void*)stringVals);
            }    
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | USR_TYPE ID ID {
            if(symbolTable.variableExists($3)) {
                error_variable_exists($3);
            }
            VarInfo* var = new VarInfo($2, $3, false, 1, nullptr, true);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | CONST USR_TYPE ID ID {
            if(symbolTable.variableExists($4)) {
                error_variable_exists($4);
            }
            VarInfo* var = new VarInfo($3, $4, true, 1, nullptr, true);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | USR_TYPE ID ID '{' initializer_list '}' { // initialize user type variable with initializer list 
            if(symbolTable.variableExists($3)) {
                error_variable_exists($3);
            }
            VarInfo* var = new VarInfo($2, $3, false, 1, nullptr, true);

            int nr_elements = $5->size();
            if(nr_elements == 0) {
                yyerror("Initializer list is empty in user type initialization");
            }

            int userTypeIndex = -1;
            for (int i = 0; i < userTypes.size(); ++i) {
                if (userTypes[i].getName() == $2) {
                    userTypeIndex = i;
                    break;
                }
            }
            if (userTypeIndex == -1) {
                char errorMsg[100];
                sprintf(errorMsg, "User type %s not found", $2);
                yyerror(errorMsg);
            }
            if (userTypes[userTypeIndex].getVars().size() != nr_elements) {
                yyerror("Number of elements in the initializer list is not equal to the number of variables in the user type");
            }
            for (int i = 0; i < nr_elements; ++i) {
                if (userTypes[userTypeIndex].getVars()[i].getType() != (*$5)[i]->string_type()) {
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
                }, (*$5)[i]->evaluate());
            }

            var->setValue(copy);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    ;

initializer_list: /* epsilon */ {
                    $$ = new vector<ASTNode*>();
                }
                | initializer_list ',' expr {
                    $$ = $1;
                    $$->push_back($3);
                }
                | expr {
                    $$ = new vector<ASTNode*>();
                    $$->push_back($1);
                }
                ;

global_function_definitions: /* epsilon */
    | global_function_definitions global_function_definition
    ;

global_function_definition: TYPE ID '(' func_param ')' '{' {symbolTable.enterScope(string($2));} statements '}' {symbolTable.exitScope();} {
                            FunctionInfo* func = new FunctionInfo($1, $2, *$4);
                            symbolTable.addFunction(*func);
                        }

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

statement: decl ';' 
    | assignment_statement
    | control_statement
    | function_call ';'
    | eval_statement
    | type_of_statement
    | return_statement
    ;

return_statement: RETURN expr ';';

assignment_statement: ID ASSIGN expr ';' {
                        if(!symbolTable.variableExists($1)) {
                            error_variable_not_found($1);
                        }
                        VarInfo temp = symbolTable.getVariableReference($1);

                        if(strcmp(temp.getType().c_str(), $3->string_type().c_str()) == 0){
                            temp.assign_expr($3);
                        }
                        else{
                            error_different_types(temp.getType().c_str(), $3->string_type().c_str());
                        }
                    }
                    | ID '[' expr ']' ASSIGN expr ';' {
                        if(strcmp($3->string_type().c_str(), "int") == 0){
                            if(!symbolTable.variableExists($1)) {
                                error_variable_not_found($1);
                            }
                            
                            VarInfo temp = symbolTable.getVariableReference($1);

                            if(strcmp(temp.getType().c_str(), $6->string_type().c_str()) == 0){
                                if(strcmp(temp.getType().c_str(), "int") == 0){
                                    int* intVals = (int*)(temp.getValueReference());
                                    intVals[std::get<int>($3->evaluate())] = std::get<int>($6->evaluate());
                                    temp.setValue((void*)intVals);
                                }
                                else if(strcmp(temp.getType().c_str(), "float") == 0){
                                    float* floatVals = (float*)(temp.getValueReference());
                                    floatVals[std::get<int>($3->evaluate())] = std::get<float>($6->evaluate());
                                    temp.setValue((void*)floatVals);
                                }
                                else if(strcmp(temp.getType().c_str(), "bool") == 0){
                                    bool* boolVals = (bool*)(temp.getValueReference());
                                    boolVals[std::get<int>($3->evaluate())] = std::get<bool>($6->evaluate());
                                    temp.setValue((void*)boolVals);
                                }
                                else if(strcmp(temp.getType().c_str(), "char") == 0){
                                    char* charVals = (char*)(temp.getValueReference());
                                    charVals[std::get<int>($3->evaluate())] = std::get<char>($6->evaluate());
                                    temp.setValue((void*)charVals);
                                }
                                else if(strcmp(temp.getType().c_str(), "string") == 0){
                                    char** stringVals = (char**)(temp.getValueReference());
                                    stringVals[std::get<int>($3->evaluate())] = *(std::get<char**>($6->evaluate()));
                                    temp.setValue((void*)stringVals);
                                }
                            }
                            else{
                                error_different_types(temp.getType().c_str(), $6->string_type().c_str());
                            }
                        }
                        else yyerror("Array element access number is not an integer");
                    }
                    | ID '.' ID ASSIGN expr ';' {
                        bool found = false;
                        VarInfo variable = symbolTable.getVariableReference($1);
                        // search for the user type
                        for (const UserType& userType : userTypes) {
                            if(userType.getName() == variable.getType()) {
                                found = true;
                                // check if the variable exists in the user type
                                bool foundVar = false;
                                for (const VarInfo& var : userType.getVars()) {
                                    if (var.getName() == $3) {
                                        foundVar = true;
                                        int offset = 0;
                                        for (const VarInfo& v : userType.getVars()) {
                                            if (v.getName() == $3) {
                                                break;
                                            }
                                            offset += v.getSize();
                                        }
                                        if (var.getType() == "int") {
                                            int value = *(int*)((char*)symbolTable.getVariableReference($1).getValueReference() + offset);
                                            if (strcmp($5->string_type().c_str(), "int") == 0) {
                                                *(int*)((char*)symbolTable.getVariableReference($1).getValueReference() + offset) = std::get<int>($5->evaluate());
                                            } else {
                                                error_different_types("int", $5->string_type().c_str());
                                            }
                                        } else if (var.getType() == "float") {
                                            float valuef = *(float*)((char*)symbolTable.getVariableReference($1).getValueReference() + offset);
                                            if (strcmp($5->string_type().c_str(), "float") == 0) {
                                                *(float*)((char*)symbolTable.getVariableReference($1).getValueReference() + offset) = std::get<float>($5->evaluate());
                                            } else {
                                                error_different_types("float", $5->string_type().c_str());
                                            }
                                        } else if (var.getType() == "bool") {
                                            bool valueb = *(bool*)((char*)symbolTable.getVariableReference($1).getValueReference() + offset);
                                            if (strcmp($5->string_type().c_str(), "bool") == 0) {
                                                *(bool*)((char*)symbolTable.getVariableReference($1).getValueReference() + offset) = std::get<bool>($5->evaluate());
                                            } else {
                                                error_different_types("bool", $5->string_type().c_str());
                                            }
                                        } else if (var.getType() == "char") {
                                            char valuec = *(char*)((char*)symbolTable.getVariableReference($1).getValueReference() + offset);
                                            if (strcmp($5->string_type().c_str(), "char") == 0) {
                                                *(char*)((char*)symbolTable.getVariableReference($1).getValueReference() + offset) = std::get<char>($5->evaluate());
                                            } else {
                                                error_different_types("char", $5->string_type().c_str());
                                            }
                                        } else if (var.getType() == "string") {
                                            char* values = *(char**)((char*)symbolTable.getVariableReference($1).getValueReference() + offset);
                                            if (strcmp($5->string_type().c_str(), "string") == 0) {
                                                *(char**)((char*)symbolTable.getVariableReference($1).getValueReference() + offset) = *(std::get<char**>($5->evaluate()));
                                            } else {
                                                error_different_types("string", $5->string_type().c_str());
                                            }
                                        } else {
                                            yyerror("Unknown type in user type variable");
                                        }
                                        break;
                                    }
                                }
                                if (!foundVar) {
                                    char errorMsg[100];
                                    sprintf(errorMsg, "Variable %s not found in user type %s", $3, userType.getName().c_str());
                                    yyerror(errorMsg);
                                }
                                break;
                            }
                        }
                        if (!found) {
                            yyerror("User type not found");
                        }
                    }
                    ;

control_statement: if_statement 
    | for_statement
    | while_statement 
    ;

if_statement: IF '(' expr ')' '{' {
        symbolTable.enterScope("if" + std::to_string(ifCounter++));
        if(strcmp($3->string_type().c_str(), "bool") != 0 || get<bool>($3->evaluate()) == 0){
            //symbolTable.exitScope();
            //break;
        }
        } statements '}' {symbolTable.exitScope();}
    ;

for_statement: FOR '(' assignment_statement ';' expr ';' assignment_statement ')' '{' { symbolTable.enterScope("for" + std::to_string(forCounter++));} statements '}' {symbolTable.exitScope();}
    ;

while_statement: WHILE '(' expr ')' '{' {symbolTable.enterScope("while" + std::to_string(whileCounter++));} statements '}' {symbolTable.exitScope();}
    ;

function_call: ID '(' arguments ')' {
        if(!symbolTable.functionExists($1)) {
            error_function_not_found($1);
        }
        FunctionCallNode* func = new FunctionCallNode($1, $3);
        // Added some comment lmao
        // Another comment
        $$ = func;
    }
    ;

arguments: /* epsilon */ {
            vector<ASTNode*>* temp = new vector<ASTNode*>();
            $$ = temp;
        }
        | arg_list {$$ = $1;}
        ;

arg_list: expr {
        vector<ASTNode*>* temp = new vector<ASTNode*>();
        temp->push_back($1);
        $$ = temp;
    }
    | arg_list ',' expr {
        vector<ASTNode*>* temp = $1;
        temp->push_back($3);
        $$ = temp;
    }
    ;

expressions: expr {
                vector<ASTNode*>* temp = new vector<ASTNode*>();
                temp->push_back($1);
                $$ = temp;
            }
           | expressions ',' expr {
                vector<ASTNode*>* temp = $1;
                temp->push_back($3);
                $$ = temp;
            }
           ;

eval_statement: EVAL '(' expr ')' ';' { 
    switch($3->type()) {
        case ExprType::INT:
            printf("Evaluated expression: %d at line %d\n", std::get<int>($3->evaluate()), yylineno);
            break;
        case ExprType::FLOAT:
            printf("Evaluated expression: %f at line %d\n", std::get<float>($3->evaluate()), yylineno);
            break;
        case ExprType::BOOLEAN:
            printf("Evaluated expression: %s at line %d\n", std::get<bool>($3->evaluate())? "true" : "false", yylineno);
            break;
        case ExprType::STRING:
            if(std::get<char**>($3->evaluate()) != nullptr) {
                printf("Evaluated expression: %s at line %d\n", *(std::get<char**>($3->evaluate())), yylineno);

            }
            else
                printf("Evaluated expression: null\n");
            break;
        case ExprType::CHAR:
            printf("Evaluated expression: %c at line %d\n", std::get<char>($3->evaluate()), yylineno);
            break;
        default:
            printf("Evaluated expression: Unknown type\n");
            break;
    }
    free($3); // free the memory allocated for the expression
}
    ;

type_of_statement: TYPEOF '(' expr ')' ';' { 
        switch ($3->type()) {
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
    free($3); // free the memory allocated for the expression
    }
    ;

expr: expr PLUS expr { $$ = new BinaryOpNode('+', $1, $3); }
    | expr MINUS expr { $$ = new BinaryOpNode('-', $1, $3); }
    | expr MUL expr { $$ = new BinaryOpNode('*', $1, $3); }
    | expr DIV expr { $$ = new BinaryOpNode('/', $1, $3); }
    | expr MOD expr { $$ = new BinaryOpNode('%', $1, $3); }
    | expr EQ expr { $$ = new BinaryOpNode('=', $1, $3); }
    | expr NEQ expr { $$ = new BinaryOpNode('n', $1, $3); }
    | expr LT expr { $$ = new BinaryOpNode('<', $1, $3); }
    | expr LE expr { $$ = new BinaryOpNode('l', $1, $3); }
    | expr GT expr { $$ = new BinaryOpNode('>', $1, $3); }
    | expr GE expr { $$ = new BinaryOpNode('g', $1, $3); }
    | expr AND expr { $$ = new BinaryOpNode('&', $1, $3); }
    | expr OR expr { $$ = new BinaryOpNode('|', $1, $3); }
    | NOT expr { $$ = new BinaryOpNode('!', $2, new BoolNode(false)); /* right node is a dummy value */ }
    | ID { $$ = new IdentifierNode($1);
        if(!symbolTable.variableExists($1)) {
            error_variable_not_found($1);
        }
    }
    | ID '[' expr ']' {
        if(!symbolTable.variableExists($1)) {
            error_variable_not_found($1);
        }
        if($3->type() == ExprType::INT) {
            $$ = new VectorElementNode($1, std::get<int>($3->evaluate()));
        }
        else yyerror("Access number must be integer type");
    }
    | INT { $$ = new IntNode($1); }
    | FLOAT { $$ = new FloatNode($1); }
    | CHAR { $$ = new CharNode($1); }
    | BOOL { $$ = new BoolNode($1); }
    | STRING { $$ = new StringNode(&$1); }
    | function_call { $$ = $1; }
    | ID '.' ID { 
        bool found = false;
        VarInfo variable = symbolTable.getVariableReference($1);
        // search for the user type
        for (const UserType& userType : userTypes) {
            if(userType.getName() == variable.getType()) {
                found = true;
                // check if the variable exists in the user type
                bool foundVar = false;
                for (const VarInfo& var : userType.getVars()) {
                    if (var.getName() == $3) {
                        foundVar = true;
                        int offset = 0;
                        for (const VarInfo& v : userType.getVars()) {
                            if (v.getName() == $3) {
                                break;
                            }
                            offset += v.getSize();
                        }
                        if (var.getType() == "int") {
                            int value = *(int*)((char*)symbolTable.getVariableReference($1).getValueReference() + offset);
                            $$ = new IntNode(value);
                        } else if (var.getType() == "float") {
                            float valuef = *(float*)((char*)symbolTable.getVariableReference($1).getValueReference() + offset);
                            $$ = new FloatNode(valuef);
                        } else if (var.getType() == "bool") {
                            bool valueb = *(bool*)((char*)symbolTable.getVariableReference($1).getValueReference() + offset);
                            $$ = new BoolNode(valueb);
                        } else if (var.getType() == "char") {
                            char valuec = *(char*)((char*)symbolTable.getVariableReference($1).getValueReference() + offset);
                            
                            $$ = new CharNode(valuec);
                        } else if (var.getType() == "string") {
                            char* values = *(char**)((char*)symbolTable.getVariableReference($1).getValueReference() + offset);
                            $$ = new StringNode(&values);
                        } else {
                            yyerror("Unknown type in user type variable");
                        }
                        break;
                    }
                }
                if (!foundVar) {
                    char errorMsg[100];
                    sprintf(errorMsg, "Variable %s not found in user type %s", $3, userType.getName().c_str());
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
    | '(' expr ')' { $$ = $2; }
    ;
special_function: SPECIAL_FUNCTION '(' ')' '{' { symbolTable.enterScope("clean_code_executer"); } statements '}' { symbolTable.exitScope(); }
    ;

%%
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
