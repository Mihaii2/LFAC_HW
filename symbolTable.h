#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include "varInfo.h"
#include "functionInfo.h"

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

#endif // SYMBOLTABLE_H

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