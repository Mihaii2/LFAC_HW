#include <iostream>
#include <string>
#include <cstring> 
#include <vector>
using namespace std;

union Data {
    int intValue;
    float floatValue;
    char stringValue[20];
};

int main() {
    Data data;
    // aight

    cout << "Integer value: " << data.intValue << endl;

    data.floatValue = 3.14;

    cout << "Float value: " << data.floatValue << endl;

    strcpy(data.stringValue, "Hello, world!");

    cout << "String value: " << data.stringValue << endl;

    return 0;
}
