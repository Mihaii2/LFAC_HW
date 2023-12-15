#include <iostream>
#include <unordered_map>
#include <string>

// Symbol structure to represent information about a variable
struct Symbol {
    std::string name;
    std::string type;
    std::string scope; // Added for dynamic scoping with a simple string

    Symbol(const std::string& n, const std::string& t, const std::string& s) : name(n), type(t), scope(s) {}
};

// SymbolTable class to manage symbols and dynamic scopes
class SymbolTable {
private:
    std::unordered_map<std::string, Symbol> symbols;
    std::string currentScope;

public:
    // Add a symbol to the current dynamic scope
    void addSymbol(const std::string& name, const std::string& type) {
        Symbol symbol(name, type, currentScope);
        symbols[name] = symbol;
    }

    // Enter a new dynamic scope
    void enterScope(const std::string& scopeName) {
        currentScope += "::" + scopeName;
    }

    // Exit the current dynamic scope
    void exitScope() {
        size_t lastScopePos = currentScope.rfind("::");
        if (lastScopePos != std::string::npos) {
            currentScope.erase(lastScopePos);
        } else {
            currentScope.clear(); // Reset to the global scope
        }
    }

    // Lookup a symbol in the current dynamic scope
    Symbol lookupSymbol(const std::string& name) const {
        auto symbolIt = symbols.find(name);
        if (symbolIt != symbols.end()) {
            return symbolIt->second; // Found the symbol
        } else {
            return Symbol("NOT_FOUND", "NOT_FOUND", "NOT_FOUND"); // Symbol not found
        }
    }
};

// Function to demonstrate dynamic scoping
void innerFunction(SymbolTable& symbolTable) {
    symbolTable.addSymbol("x", "int");

    // Lookup 'x' in the current dynamic scope
    Symbol result = symbolTable.lookupSymbol("x");
    if (result.type != "NOT_FOUND") {
        std::cout << "Symbol found: " << result.name << " (" << result.type << ") in scope " << result.scope << "\n";
    } else {
        std::cout << "Symbol not found.\n";
    }
}

// Another function to demonstrate dynamic scoping
void outerFunction(SymbolTable& symbolTable) {
    symbolTable.addSymbol("y", "float");

    // Enter a new dynamic scope
    symbolTable.enterScope("Function");

    // Call inner function, creating a new dynamic scope
    innerFunction(symbolTable);

    // Lookup 'x' in the current dynamic scope
    Symbol result = symbolTable.lookupSymbol("x");
    if (result.type != "NOT_FOUND") {
        std::cout << "Symbol found: " << result.name << " (" << result.type << ") in scope " << result.scope << "\n";
    } else {
        std::cout << "Symbol not found.\n";
    }

    // Lookup 'y' in the current dynamic scope
    result = symbolTable.lookupSymbol("y");
    if (result.type != "NOT_FOUND") {
        std::cout << "Symbol found: " << result.name << " (" << result.type << ") in scope " << result.scope << "\n";
    } else {
        std::cout << "Symbol not found.\n";
    }

    // Exit the current dynamic scope
    symbolTable.exitScope();
}

int main() {
    SymbolTable symbolTable;

    // Call outer function, creating a new dynamic scope
    outerFunction(symbolTable);

    return 0;
}
