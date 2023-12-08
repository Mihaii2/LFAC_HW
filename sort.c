#include <stdio.h>

struct student {
    char name[20];
    int score;
};


int main() {
    struct student myStudent = {"John", 100};
    return 0;
}