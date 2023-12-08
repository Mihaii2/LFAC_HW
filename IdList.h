#include <iostream>
#include <vector>
#include <string>

using namespace std;
struct IdInfo {
    string type;
    string name;
};


class IdList {
    vector<IdInfo> vars;
   
    public:
    bool existsVar(const char* s);
    void addVar(const char* type, const char* name );
    void printVars();
    ~IdList();
};

struct StructInfo {
    string name;
    vector<IdInfo> vars;
};

class StructList {
    vector<StructInfo> structs;
   
    public:
    bool existsStruct(const char* s);
    void addStruct(const char* name, IdList* vars);
    void printStructs();
    ~StructList();
};