#include <iostream>
#include <string>
#include <cstring> // Для работы с функцией memcpy
#include <vector>
using namespace std;

int main() {
    // Предположим, у вас есть массив в переменной типа void*
    int arr[] = {1, 2, 3, 4, 5}; // Пример массива целых чисел
    void* voidPtr = static_cast<void*>(arr); // Приведение указателя на массив int в тип void*

    // Размер массива в байтах
    size_t size = sizeof(arr); // Длина массива в байтах

    // Создание строки и копирование данных из массива void* в строку string
    std::string str;
    str.resize(size); // Изменение размера строки до размера массива данных
    memcpy(&str[0], voidPtr, size); // Копирование данных из массива void* в строку

    // Вывод строки для проверки
    std::cout << "String: " << str << std::endl;

    return 0;
}
