#include <iostream>
#include <string>
#include <limits> 

using namespace std;

int A = 0, B = 0; 

int safeInput() {
    int num;
    while (!(cin >> num)) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Ошибка! Введите целое число: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    return num;
}

void enter_A() {
    cout << "Введите число A: ";
    A = safeInput();
    cout << "Число А: " << A << endl;
}

void enter_B() {
    cout << "Введите число B: ";
    B = safeInput();
    cout << "Число B: " << B << endl;
}

void proizv() {
    cout << "Результат умножения: " << A * B << endl;
}

void delen() {
    if (B == 0) {
        do {
            cout << "Ошибка! Деление на ноль. Введите новое значение B: ";
            B = safeInput();
        } while (B == 0);
    }
    cout << "Результат деления: " << A / B << endl;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int ch;

    do {
        cout << "\nМеню: " << endl;
        cout << "1. Ввести А" << endl;
        cout << "2. Ввести В" << endl;
        cout << "3. Выполнить операцию '*' (A*B)" << endl;
        cout << "4. Выполнить операцию '/' (A/B)" << endl;
        cout << "0. Выход" << endl;

        cout << "Выберите пункт меню: ";
        ch = safeInput();

        switch (ch) {
            case 1:
                enter_A();
                break;
            case 2:
                enter_B();
                break;
            case 3:
                if (A == 0 || B == 0) {
                    cout << "Одно из чисел равно 0. Умножение даст 0" << endl;
                }
                proizv();
                break;
            case 4:
                delen();
                break;
            case 0:
                cout << "Выход из программы..." << endl;
                break;
            default: 
                cout << "Неверный ввод, повторите ввод." << endl;
        }

    } while (ch != 0);

    return 0;
}