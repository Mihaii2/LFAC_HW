#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct IdInfo {
    string type;
    string name;
};

struct StructInfo {
    string name;
    vector<IdInfo> vars;
};

class StructList {
    vector<StructInfo> structs;
   
    public:
    bool existsStruct(const char* s);
    // void addStruct(const char* name, IdList* vars);
    void printStructs();
    ~StructList();
};