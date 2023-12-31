#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    bool b1 = true;
    bool b2 = true;
    std::cout <<(bool)((bool)b1 / (bool)b2);
    return 0;
}
