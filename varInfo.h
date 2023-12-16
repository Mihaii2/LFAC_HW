#ifndef VAR_INFO_H
#define VAR_INFO_H

#include <string>

class VarInfo {
public:
    std::string type;
    std::string name;
    std::string scope;
    int size = 0;
    void* memoryLocation;
};

#endif // VAR_INFO_H