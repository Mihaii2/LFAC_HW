#include <iostream>
using namespace std;

struct mystr {
    int a;
    
    int b = 100;
    
};



int main() {
    struct mystr s;
    cout << s.b << endl;

    return 0;
}