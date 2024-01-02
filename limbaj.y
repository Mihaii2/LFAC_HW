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
    int size = 0;
    int elements = 0;
    void* memoryLocation = nullptr;

public:

    VarInfo() {}
    VarInfo(string type, string name, bool is_const = false, int arraySize = 1, void* value = nullptr);
    string getName() const { return name; }
    string getType() const { return type; }
    void setElementsCount(int count) { this->elements = count; }
    int getElementsCount() const { return this->elements; }
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
    VarInfo getVariable(const string& name);
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

using ReturnValue = variant<int, float, bool, char*, char>;
using ReturnBool = bool;

class ASTNode {
public:
    using ReturnValue = variant<int, float, bool, char*, char>;
    using ReturnBool = bool;
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
    char* value;
public:
    StringNode(char* val) : value(val) {}

    ReturnValue evaluate() const override { 
        char* copy = new char[strlen(value) + 1];
        strcpy(copy, value);
        //printf("\nI|%s|I\n", copy);
        return ReturnValue(copy);
    }
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
    FunctionCallNode(const std::string& id, std::vector<ASTNode*>* p) : name(id), params(p) {}
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
    BinaryOpNode(char oper, const ASTNode* l, const ASTNode* r)
        : op(oper), left(l), right(r) {}
    ReturnValue evaluate() const override;
    ExprType type() const override;
    string string_type() const override;
};

class boolBinaryOpNode : public ASTNode {
    private:
    char op;
    const ASTNode* left;
    const ASTNode* right;

public:
    boolBinaryOpNode(char oper, const ASTNode* l, const ASTNode* r)
        : op(oper), left(l), right(r) {}
    ReturnValue evaluate() const override;
    ExprType type() const override {return ExprType::BOOLEAN;}
    string string_type() const override {return "bool";}
};

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
%token <string> ID TYPE SPECIAL_FUNCTION
%token IF WHILE FOR  
%token END_USR_TYPES END_USR_TYPE_VARS END_GLOBAL_VARS END_GLOBAL_FUNCS
%token CONST USR_TYPE EVAL TYPEOF
%token NOT EQ NEQ LT LE GT GE ASSIGN PLUS MINUS MUL DIV MOD AND OR GEQ LEQ

%type<vars> usr_type_vars list_param func_param
%type<funcs> usr_type_methods
%type<var> usr_type_var param decl
%type<func> usr_type_method
%type<node> expr function_call
%type<nodes> expressions arguments arg_list

%left CHAR

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
                }
                ;

declarations : decl ';' 
    | declarations  decl ';'
    ;

decl: TYPE ID {
            string to_return = "Variable already exists (";
            to_return += $2;
            to_return += ")";
            if(symbolTable.variableExists($2)) yyerror(to_return.c_str());
            VarInfo* var = new VarInfo($1, $2);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | CONST TYPE ID {
string to_return = "Variable already exists (";
            to_return += $3;
            to_return += ")";
            if(symbolTable.variableExists($3)) yyerror(to_return.c_str());            VarInfo* var = new VarInfo($2, $3, true);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID ASSIGN expr {
            string to_return = "Variable already exists (";
            to_return += $2;
            to_return += ")";
            if(symbolTable.variableExists($2)) yyerror(to_return.c_str());
            if (strcmp($4->string_type().c_str(), $1) != 0){
                string to_return = "";
                to_return += "Different types assignment(";
                to_return += $1;
                to_return += "<-";
                to_return += $4->string_type();
                to_return += ")";
                yyerror(to_return.c_str()); 
            }
            VarInfo* var = new VarInfo($1, $2, false);
            if(strcmp($4->string_type().c_str(), "string") == 0) var->setSize(strlen(std::get<char*>($4->evaluate())));
            else if (strcmp($4->string_type().c_str(), "int") == 0) var->setSize(sizeof(int));
            else if (strcmp($4->string_type().c_str(), "float") == 0) var->setSize(sizeof(float));
            else if (strcmp($4->string_type().c_str(), "bool") == 0) var->setSize(sizeof(bool));
            else if (strcmp($4->string_type().c_str(), "char") == 0) var->setSize(sizeof(char));
            var->assign_expr($4);
            var->setElementsCount(1);
            free($4);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | CONST TYPE ID ASSIGN expr { 
            string to_return = "Variable already exists (";
            to_return += $3;
            to_return += ")";
            if(symbolTable.variableExists($3)) yyerror(to_return.c_str());            VarInfo* var = new VarInfo($2, $3, true);
            var->assign_expr($5);
            free($5);
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID '[' expr ']' {
            if($4->string_type() != "int") yyerror("Array element access number is not an integer");
            string to_return = "Variable already exists (";
            to_return += $2;
            to_return += ")";
            if(symbolTable.variableExists($2)) yyerror(to_return.c_str());
            VarInfo* var = new VarInfo($1, $2, false, get<int>($4->evaluate()));
            $$ = var;
            symbolTable.addVariable(*var);
    }
    | TYPE ID '[' expr ']' ASSIGN '{' expressions '}' {
            if($4->string_type() != "int") yyerror("Array element access number is not an integer");
            string to_return = "Variable already exists (";
            to_return += $2;
            to_return += ")";
            if(symbolTable.variableExists($2)) yyerror(to_return.c_str()); 
            VarInfo* var = new VarInfo($1, $2, false, get<int>($4->evaluate()));
            ReturnValue values[$8->size()];
            //printf("\n{%d} %d - %d\n", (std::get<int>($4->evaluate())) > $8->size(), std::get<int>($4->evaluate()), $8->size());
            if((std::get<int>($4->evaluate())) < $8->size()) yyerror("Too many values");
            for(int i = 0; i < $8->size(); ++i){
                ASTNode* node = (*$8)[i];
                if(strcmp(node->string_type().c_str(), $1) != 0){
                    std::string to_return = "Assignment values type is different from array type (";
                    to_return += $1;
                    to_return += "->";
                    to_return += node->string_type();
                    to_return += ")";
                    yyerror(to_return.c_str());
                }
                values[i] = node->evaluate();
            }
            //printf("\n|%s| == |%s| ? %d\n", "int", $1, strcmp($1, "int"));
            if(strcmp($1, "int") == 0){
                    int* intVals = new int[$8->size()];
                    for(int i = 0; i < $8->size(); ++i){
                        intVals[i] = std::get<int>(values[i]);
                        //printf("\n%d = %d\n",i,intVals[i]);
                    }
                    var->setValue((void*)intVals);
                    //int* someVals = (int*)(var->getValueCopy());
                    //printf("\nI%dI\n", someVals[0]);
                    $$ = var;
                    symbolTable.addVariable(*var);
            }
            else if (strcmp($1, "bool") == 0){
                    bool* boolVals = new bool[$8->size()];
                    for(int i = 0; i < $8->size(); ++i){
                        boolVals[i] = std::get<bool>(values[i]);
                    }
                    var->setValue((void*)boolVals);
                    $$ = var;
                    symbolTable.addVariable(*var);
            }               
            else if (strcmp($1, "char") == 0){
                    char* charVals = new char[$8->size()];
                    for(int i = 0; i < $8->size(); ++i){
                        charVals[i] = std::get<char>(values[i]);
                    }
                    var->setValue((void*)charVals);
                    $$ = var;
                    symbolTable.addVariable(*var);
            }
            else if (strcmp($1, "float") == 0){    
                    float* floatVals = new float[$8->size()];
                    for(int i = 0; i < $8->size(); ++i){
                        floatVals[i] = std::get<float>(values[i]);
                    }
                    var->setValue((void*)floatVals);
                    $$ = var;
                    symbolTable.addVariable(*var);
            }    
            else if (strcmp($1, "string") == 0){
                    char* stringVals[$8->size()];
                    int totalSize = 0;
                    for(int i = 0; i < $8->size(); ++i){
                        stringVals[i] = new char[sizeof(std::get<char*>(values[i]))];
                        strcpy(stringVals[i], std::get<char*>(values[i])); 
                        stringVals[i][strlen(stringVals[i])] = '\0';
                        totalSize += (sizeof(stringVals[i]));
                    }
                    var->setSize(totalSize);
                    var->setElementsCount($8->size());
                    var->setValue((void*)stringVals);         
                    $$ = var;
                    symbolTable.addVariable(*var);
            }    
    }
    // | TYPE ID '[' INT ']' '[' INT ']' {   nu cred ca trebuie sa avem si matrici
    //         VarInfo* var = new VarInfo($1, $2, false, $4 * $7);
    //         $$ = var;
    //         symbolTable.addVariable(*var);}
    // | TYPE ID '[' INT ']' '[' INT ']' ASSIGN '{' expressions '}' {
    //         VarInfo* var = new VarInfo($1, $2, false, $4 * $7);
    //         $$ = var;
    //         symbolTable.addVariable(*var);
    // }

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
    ;

assignment_statement: ID ASSIGN expr ';' {
                        VarInfo temp = symbolTable.getVariable($1);
                        if(strcmp(temp.getType().c_str(), $3->string_type().c_str()) == 0){
                            temp.assign_expr($3);
                        }
                        else{
                            std::string str = "Different types (";
                            str += temp.getType();
                            str += ", ";
                            str += $3->string_type();
                            str += ")";
                            yyerror(str.c_str());
                        }
                    }
                    | ID '[' expr ']' ASSIGN expr ';' {
                        if(strcmp($3->string_type().c_str(), "int") == 0){
                            VarInfo temp = symbolTable.getVariable($1);
                            if(strcmp(temp.getType().c_str(), $6->string_type().c_str()) == 0){
                                if(strcmp(temp.getType().c_str(), "int") == 0){
                                    int* intVals = (int*)(temp.getValueCopy());
                                    intVals[std::get<int>($3->evaluate())] = std::get<int>($6->evaluate());
                                    temp.setValue((void*)intVals);
                                }
                                else if(strcmp(temp.getType().c_str(), "float") == 0){
                                    float* floatVals = (float*)(temp.getValueCopy());
                                    floatVals[std::get<int>($3->evaluate())] = std::get<float>($6->evaluate());
                                    temp.setValue((void*)floatVals);
                                }
                                else if(strcmp(temp.getType().c_str(), "bool") == 0){
                                    bool* boolVals = (bool*)(temp.getValueCopy());
                                    boolVals[std::get<int>($3->evaluate())] = std::get<bool>($6->evaluate());
                                    temp.setValue((void*)boolVals);
                                }
                                else if(strcmp(temp.getType().c_str(), "char") == 0){
                                    char* charVals = (char*)(temp.getValueCopy());
                                    charVals[std::get<int>($3->evaluate())] = std::get<char>($6->evaluate());
                                    temp.setValue((void*)charVals);
                                }
                                else if(strcmp(temp.getType().c_str(), "string") == 0){
                                    char* stringVals = (char*)(temp.getValueCopy());
                                    char* newString = std::get<char*>($6->evaluate());
                                    temp.setSize(sizeof(newString) + temp.getSize());
                                    temp.setElementsCount(1);
                                    //newString[strlen(newString)] = '\0';
                                    strcpy(&stringVals[std::get<int>($3->evaluate())], newString);
                                    temp.setValue((void*)stringVals);
                                }
                            }
                            else{
                                std::string str = "Different types (";
                                str += temp.getType();
                                str += ", ";
                                str += $6->string_type();
                                str += ")";
                                yyerror(str.c_str());
                            }
                        }
                        else yyerror("Array element access number is not an integer");
                    }
                    ;
/*
left_value: ID
    | array_element_access 
    ;

array_element_access: ID '[' expr ']' {
        if($3->string_type() == "int"){
            VarInfo* temp = symbolTable.getVariable($1);
        }
        else yyerror("Array element access number is not an integer");    
    }
    ;
*/

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
    //| IF '(' e_bool ')' '{' statements '}' 
    ;

for_statement: FOR '(' assignment_statement ';' expr ';' assignment_statement ')' '{' { symbolTable.enterScope("for" + std::to_string(forCounter++));} statements '}' {symbolTable.exitScope();}
    ;

while_statement: WHILE '(' expr ')' '{' {symbolTable.enterScope("while" + std::to_string(whileCounter++));} statements '}' {symbolTable.exitScope();}
    ;

function_call: ID '(' arguments ')' {
        FunctionCallNode* func = new FunctionCallNode($1, $3);
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
            printf("Evaluated expression: %d\n", std::get<int>($3->evaluate()));
            break;
        case ExprType::FLOAT:
            printf("Evaluated expression: %f\n", std::get<float>($3->evaluate()));
            break;
        case ExprType::BOOLEAN:
            printf("Evaluated expression: %d\n", std::get<bool>($3->evaluate()));
            break;
        case ExprType::STRING:
        case ExprType::CHAR:
            printf("Evaluated expression: %d\n", 0);
            break;
        default:
            printf("Unknown type\n");
            break;
    }
    free($3); // free the memory allocated for the expression
}
    ;

type_of_statement: TYPEOF '(' expr ')' ';' { 
        switch ($3->type()) {
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
            default:
                printf("Type of expression: unknown\n");
                break;
        }
    free($3); // free the memory allocated for the expression
    }
    ;

expr: expr PLUS expr {
        if(strcmp($1->string_type().c_str(), "bool") == 0 || strcmp($3->string_type().c_str(), "bool") == 0) yyerror("[+] bools are not allowed");
        $$ = new BinaryOpNode('+', $1, $3); }
    | expr MINUS expr {
        if(strcmp($1->string_type().c_str(), "bool") == 0 || strcmp($3->string_type().c_str(), "bool") == 0) yyerror("[-] bools are not allowed");
        $$ = new BinaryOpNode('-', $1, $3);
    }
    | expr MUL expr {
        if(strcmp($1->string_type().c_str(), "bool") == 0 || strcmp($3->string_type().c_str(), "bool") == 0) yyerror("[*] bools are not allowed");
        $$ = new BinaryOpNode('*', $1, $3);
    }
    | expr DIV expr {
        if(strcmp($1->string_type().c_str(), "bool") == 0 || strcmp($3->string_type().c_str(), "bool") == 0) yyerror("[/] bools are not allowed");
        $$ = new BinaryOpNode('/', $1, $3);
    }
    | expr MOD expr {
        if(strcmp($1->string_type().c_str(), "bool") == 0 || strcmp($3->string_type().c_str(), "bool") == 0) yyerror("[MOD] bools are not allowed");
        $$ = new BinaryOpNode('%', $1, $3);
    }
    | expr EQ expr { $$ = new boolBinaryOpNode('=', $1, $3); }
    | expr NEQ expr { $$ = new boolBinaryOpNode('n', $1, $3); }
    | expr LT expr { $$ = new boolBinaryOpNode('<', $1, $3); }
    | expr LE expr { $$ = new boolBinaryOpNode('l', $1, $3); }
    | expr GT expr { $$ = new boolBinaryOpNode('>', $1, $3); }
    | expr GE expr { $$ = new boolBinaryOpNode('g', $1, $3); }
    | expr AND expr {
        if(strcmp($3->string_type().c_str(), "bool") == 0 && strcmp($1->string_type().c_str(), "bool") == 0) $$ = new boolBinaryOpNode('&', $1, $3);
        else{
            std::string str = "[&&] Both operands must be bool (";
            str += $1->string_type();
            str += ",";
            str += $3->string_type();
            str += ')';
            yyerror(str.c_str());
        }
    }
    | expr OR expr {
        if(strcmp($3->string_type().c_str(), "bool") == 0 && strcmp($1->string_type().c_str(), "bool") == 0) $$ = new boolBinaryOpNode('|', $1, $3);
        else yyerror("[||] Both operands must be bool");
    }
    | ID { $$ = new IdentifierNode($1); }
    | ID '[' expr ']' {
        if(strcmp($3->string_type().c_str(), "int") == 0) $$ = new VectorElementNode($1, std::get<int>($3->evaluate()));
        else yyerror("Access number must be integer type");
    }
    | INT { $$ = new IntNode($1); }
    | FLOAT { $$ = new FloatNode($1); }
    | CHAR { $$ = new CharNode($1); }
    | BOOL { $$ = new BoolNode($1); }
    | STRING { $$ = new StringNode($1); }
    | function_call { $$ = $1; }
    | '(' expr ')' { $$ = $2; }
    ;
/*
e_bool: expr EQ expr {
        $$ = new BinaryOpNode('=', $1, $3);
    }
    | expr NEQ expr {
        $$ = new BinaryOpNode('n', $1, $3);
    }
    | expr LT expr {
        $$ = new BinaryOpNode('<', $1, $3);
    }
    | expr LE expr {
        $$ = new BinaryOpNode('l', $1, $3);
    }
    | expr GT expr {
        $$ = new BinaryOpNode('>', $1, $3);
    }
    | expr GE expr {
        $$ = new BinaryOpNode('g', $1, $3);
    }
    | e_bool AND e_bool {$$ = new BinaryOpNode('&', $1, $3);}
    | e_bool OR e_bool {$$ = new BinaryOpNode('|', $1, $3);}
    | '(' e_bool ')'{$$ = $2;}
    ;
*/
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
    //cout << "SCOPE: " << "|" << scope << "|";
    return scope;
}

void SymbolTable::addVariable(VarInfo var) {
    variables[symbolTable.getCurrentScope()][var.getName()] = var;
    //cout << " = " << var.getName() << "\n";
}

void SymbolTable::addFunction(FunctionInfo func) {
    functions[symbolTable.getCurrentScope()][func.getName()] = func;
}

bool SymbolTable::variableExists(const string& name) {
    //if(variables[symbolTable.getCurrentScope()].find(name) != variables[symbolTable.getCurrentScope()].end()) return 1;
    //else if(variables[" "].find(name) != variables[symbolTable.getCurrentScope()].end()) return 1;
    //else return 0;
    return variables[symbolTable.getCurrentScope()].find(name) != variables[symbolTable.getCurrentScope()].end();
}

bool SymbolTable::functionExists(const string& name) {
    return functions[symbolTable.getCurrentScope()].find(name) != functions[symbolTable.getCurrentScope()].end();
}

VarInfo SymbolTable::getVariable(const string& name) {
    //search for variable in current scope
    if (variables[symbolTable.getCurrentScope()].find(name) != variables[symbolTable.getCurrentScope()].end()) {
        return variables[symbolTable.getCurrentScope()][name];
    }
    //search for variable in global scope
    else {
        return variables[""][name];
    }
}

FunctionInfo SymbolTable::getFunction(const string& name) {
    //search for function in global scope
    return functions[""][name];
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
    memcpy(this->memoryLocation, value, this->size);
}

void* VarInfo::getValueCopy(){
    void* copy = malloc(this->size);
    memcpy(copy, this->memoryLocation, this->size);
    return copy;
}

void VarInfo::write_to_string(string& str) const {
    if(this->size == 0) return; // variabila nu exosta
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
        if(this->elements == 1 || this->elements == 0) str += (char*)this->memoryLocation;
        else {
            void* temo = this->memoryLocation;
            char** strins = (char**)temo;
            for(int i = 0; i < this->getElementsCount(); ++i){
                str += strins[i];
                str += " ";
            }
        }
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
    case ExprType::CHAR: {
        this->setSize(sizeof(char));
        void* value = malloc(sizeof(char));
        char temp4 = std::get<char>(expr->evaluate());
        memcpy(value, &temp4, sizeof(char));
        this->setValue(value);
        break;
    }
    case ExprType::STRING: {
        char* value = new char[strlen(std::get<char*>(expr->evaluate())) + 1];
        value = std::get<char*>(expr->evaluate());
        //if(value[strlen(value) - 1] == '\x05') printf("DA\n");//value[strlen(value)] = '\0';
        void* to_set = malloc(strlen(value));
        memcpy(to_set, value, strlen(value));
        this->setValue(to_set);
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

// BINARYOPNODE IMPLEMENTATION

template <typename T>
ASTNode::ReturnValue handleOperation(char op, T leftValue, T rightValue) {
    bool response;
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
        case '=':
            response = (leftValue == rightValue);
            return ASTNode::ReturnValue(response);
        case 'n':
            response = (leftValue != rightValue);
            return ASTNode::ReturnValue(response);
        case '<':
            response = (leftValue < rightValue);
            return ASTNode::ReturnValue(response);
        case 'l':
            response = (leftValue <= rightValue);
            return ASTNode::ReturnValue(response);
        case '>':
            response = (leftValue > rightValue);
            return ASTNode::ReturnValue(response);
        case 'g':
            response = (leftValue >= rightValue);
            return ASTNode::ReturnValue(response);
        case '&':
            response = (leftValue && rightValue);
            return ASTNode::ReturnValue(response);
        case '|':
            response = (leftValue || rightValue);
            return ASTNode::ReturnValue(response);
        default:
            return ASTNode::ReturnValue(0);
    }
    return ASTNode::ReturnValue(0); //safety return
}

ASTNode::ReturnValue boolBinaryOpNode::evaluate() const {
    if(left->type() != right->type()) {
        yyerror("Incompatible types");
    }
    if(strcmp(left->string_type().c_str(), "int") == 0){
        return handleOperation(op, std::get<int>(left->evaluate()), std::get<int>(right->evaluate()));
    }
    else if(strcmp(left->string_type().c_str(), "bool") == 0){
        return handleOperation(op, std::get<bool>(left->evaluate()), std::get<bool>(right->evaluate()));
    }
    else if(strcmp(left->string_type().c_str(), "float") == 0){
        return handleOperation(op, std::get<float>(left->evaluate()), std::get<float>(right->evaluate()));
    }
    else if(strcmp(left->string_type().c_str(), "char") == 0){
        ReturnValue(0); // error?
        //return handleOperation(op, std::get<char>(left->evaluate()), std::get<char>(right->evaluate()));
    }
    else if(strcmp(left->string_type().c_str(), "string") == 0){
        ReturnValue(0); //error?
        //return handleOperation(op, std::get<char*>(left->evaluate()), std::get<char*>(right->evaluate()));
    }
    return ReturnValue(0);
}

ASTNode::ReturnValue BinaryOpNode::evaluate() const {
    // Implement logic to evaluate the binary operation
    // based on the operator and return the result
    if(left->type() != right->type()) {
        yyerror("Incompatible types");
    }
    ExprType type = left->type();
    switch (type) {
        case ExprType::INT:
            //printf("BinaryOpNode: op = %c , leftValue = %d , rightValue = %d\n", op, std::get<int>(left->evaluate()), std::get<int>(right->evaluate()));
            return handleOperation(op, std::get<int>(left->evaluate()), std::get<int>(right->evaluate()));
        case ExprType::FLOAT:
            return handleOperation(op, std::get<float>(left->evaluate()), std::get<float>(right->evaluate()));
        case ExprType::BOOLEAN:
            //printf("|1|\t");
            //printf("BinaryOpNode: type = %s , op = %c , leftValue = %d , rightValue = %d\n", op, std::get<bool>(left->evaluate()), std::get<bool>(right->evaluate()));
            //return handleOperation(op, std::get<bool>(left->evaluate()), std::get<bool>(right->evaluate()));
            //return ReturnValue((bool)((bool)std::get<bool>(left->evaluate()) + (bool)std::get<bool>(right->evaluate())));
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

string BinaryOpNode::string_type() const {
    if(left->type() != right->type()) {
        yyerror("Incompatible typesss");
    }
    return left->string_type();
}

// BINARYOPNODE IMPLEMENTATION ENDS

// FUNCTIONCALLNODE IMPLEMENTATION

ASTNode::ReturnValue FunctionCallNode::evaluate() const {
    FunctionInfo temp = symbolTable.getFunction(name);
    std::vector<VarInfo> p = temp.getParams();
    for(int i = 0; i < p.size(); ++i){
        ASTNode* aParam = (*this->params)[i];
        if (strcmp(aParam->string_type().c_str(), p[i].getType().c_str()) != 0){
            std::string to_return = "Different parameter types [Param: ";
            to_return += to_string(i+1);
            to_return += "](";
            to_return += p[i].getType();
            to_return += "<-";
            to_return += aParam->string_type();
            to_return += ") ";
            yyerror(to_return.c_str());
        }
    }
    switch(temp.getType()[0]) {
        case 'g':
            return ReturnValue(0);
        case 'f':
            return ReturnValue(0.0f);
        case 'b':
            return ReturnValue(false);
        case 'c':
            return ReturnValue('0');
        case 's':
            return ReturnValue('0');
        default:
            return ReturnValue(0);
    }
    return ReturnValue(0); //temp 
}

ExprType FunctionCallNode::type() const {
    FunctionInfo func = symbolTable.getFunction(name);
    switch (func.getType()[0]) {
        case 'g':
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
    VarInfo var = symbolTable.getVariable(name);
    if(strcmp(var.getType().c_str(), "int") == 0){
        void* vals = var.getValueCopy();
        int* intVals = (int*)vals;
        return ReturnValue(intVals[index]);
    }
    else if(strcmp(var.getType().c_str(), "bool") == 0){
        void* vals = var.getValueCopy();
        bool* boolVals = (bool*)vals;
        return ReturnValue(boolVals[index]);
    }
    else if(strcmp(var.getType().c_str(), "float") == 0){
        void* vals = var.getValueCopy();
        float* floatVals = (float*)vals;
        return ReturnValue(floatVals[index]);
    }
    else if(strcmp(var.getType().c_str(), "char") == 0){
        void* vals = var.getValueCopy();
        char* charVals = (char*)vals;
        return ReturnValue(charVals[index]);
    }
    else if(strcmp(var.getType().c_str(), "string") == 0){
        void* vals = var.getValueCopy();
        char** stringVals = (char**)vals;
        char* returnstr = new char[strlen(stringVals[index])];
        strcpy(returnstr, stringVals[index]);
        returnstr[strlen(returnstr)] = '\0';
        return ReturnValue(returnstr);
    }
    return ReturnValue(0);
}

ExprType VectorElementNode::type() const {
    VarInfo var = symbolTable.getVariable(name);
    if(strcmp(var.getType().c_str(), "int") == 0) return ExprType::INT;
    else if(strcmp(var.getType().c_str(), "bool") == 0) return ExprType::BOOLEAN; 
    else if(strcmp(var.getType().c_str(), "float") == 0) return ExprType::FLOAT;
    else if(strcmp(var.getType().c_str(), "char") == 0) return ExprType::CHAR;
    else if(strcmp(var.getType().c_str(), "string") == 0) return ExprType::STRING;
    return ExprType::INT;
}

string VectorElementNode::string_type() const {
    VarInfo var = symbolTable.getVariable(name);
    return var.getType();
}

// VECTORELEMENTNODE IMPLEMENTATION ENDS

// IDENTIFIERNODE IMPLEMENTATION

ASTNode::ReturnValue IdentifierNode::evaluate() const {
    VarInfo var = symbolTable.getVariable(name);
    switch (var.getType()[0]) {
        case 'g':
            return ReturnValue(*(int*)var.getValueCopy());
        case 'f':
            return ReturnValue(*(float*)var.getValueCopy());
        case 'b':
            return ReturnValue(*(bool*)var.getValueCopy());
        case 'c':
            return ReturnValue(*(char*)var.getValueCopy());
        case 's':
            return ReturnValue((char*)var.getValueCopy());
        default:
            return ReturnValue(0);
    }
    return ReturnValue(0);  
}

ExprType IdentifierNode::type() const {
    VarInfo var = symbolTable.getVariable(name);
    switch (var.getType()[0]) {
        case 'g':
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
    VarInfo var = symbolTable.getVariable(name);
    return var.getType();
}

// IDENTIFIERNODE IMPLEMENTATION ENDS

int main(int argc, char** argv){
    yyin=fopen(argv[1],"r");
    yyparse();

//    IntNode intn(128);
//    cout << "|" << std::get<int>(intn.evaluate()) << "|" << endl;

    // Print user types
    // for (UserType& userType : userTypes) {
    //     userType.printMembers();
    // }

    // Print symbol table in file
    symbolTable.saveInFile();
}
