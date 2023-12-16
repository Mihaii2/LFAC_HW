#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    cout<<"Hello World"<<endl;
    int qqq = 15;
    void* data = malloc(sizeof(int)*4);
    int* intData = (int*) data;
    intData[0] = 1;
    //intData[1] = 58;
    intData[2] = -8;
    //intData[3] = 12;
    std::cout << intData[0] << "\n" << intData[1] << "\n" << intData[2] << "\n" << intData[3] << std::endl;  
    return 0;
}
