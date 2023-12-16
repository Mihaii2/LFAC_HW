#ifndef FUNCTIONINFO_H
#define FUNCTIONINFO_H

#include <string>
#include <vector>
using namespace std;

class FunctionInfo {
public:
    string type;
    string name;
    string scope;
    vector<VarInfo> params;
};

#endif // FUNCTIONINFO_H