//
// Created by lenovo on 06/05/2026.
//

#include <iostream>
#include <fstream>
using namespace std;

void read(int *&arr_size, int &size) {

    char waste[10];
    ifstream input("input.txt");
    if (!input) {
        cout << "file not opened error" << endl;
        return;                          // void function: just return, no value
    }

    input.getline(waste, 10, '=');
    input >> size;                       // writes directly into main's size via reference

    arr_size = new int[size];            // writes directly into main's pointer via reference
    for (int i = 0; i < size; i++) {
        input >> arr_size[i];            // was "fin" — should be "input"
    }

    input.close();
    // no return needed — references did the work
}

int main() {
    int size = 0;                        // must declare variables in main first
    int *arr_size = nullptr;

    read(arr_size, size);                // pass directly, no & needed (already ref in function)

    for (int i = 0; i < size; i++) {
        cout << arr_size[i] << " ";
    }
    cout << endl;

    delete[] arr_size;                   // always free dynamic memory
    return 0;
}