#include <stdio.h>


int main() {
    void* data;
    data = malloc(sizeof(int));
    int * dataV = (int*) data;
    *dataV = 10;
    printf("%d\n", (int*)data);
}