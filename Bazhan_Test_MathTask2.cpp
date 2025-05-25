#include "CUTE/cute/cute.h"
#include "CUTE/cute/ide_listener.h"
#include "CUTE/cute/cute_runner.h"

#include <sstream>
#include <iostream>
#include <limits>

using namespace std;

// Тестируемые функции (должны быть вынесены в отдельный заголовочный файл)
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
}

void enter_B() {
    cout << "Введите число B: ";
    B = safeInput();
}

int proizv() { return A * B; }
int delen() { return (B != 0) ? A / B : 0; }

void test_safeInput_correct() {
    istringstream input("42\n");
    streambuf* orig = cin.rdbuf(input.rdbuf());
    
    int result = safeInput();
    cin.rdbuf(orig);
    
    ASSERT_EQUAL(42, result);
}

void test_safeInput_recovery() {
    istringstream input("abc\n42\n");
    streambuf* orig = cin.rdbuf(input.rdbuf());
    
    int result = safeInput();
    cin.rdbuf(orig);
    
    ASSERT_EQUAL(42, result);
}

void test_safeInput_zero() {
    istringstream input("0\n");
    streambuf* orig = cin.rdbuf(input.rdbuf());
    
    int result = safeInput();
    cin.rdbuf(orig);
    
    ASSERT_EQUAL(0, result);
}

// Тесты вычислительных операций
void test_proizv() {
    A = 5; B = 4;
    ASSERT_EQUAL(20, proizv());
}

void test_delen() {
    A = 10; B = 2;
    ASSERT_EQUAL(5, delen());
}

void test_delen_by_zero() {
    A = 10; B = 0;
    ASSERT_EQUAL(0, delen());
}

// Запуск тестов
void runAllTests(int argc, char const *argv[]) {
    cute::suite s;
    
    // Добавляем тесты
    s.push_back(CUTE(test_safeInput_correct));
    s.push_back(CUTE(test_safeInput_recovery));
    s.push_back(CUTE(test_safeInput_zero));
    s.push_back(CUTE(test_proizv));
    s.push_back(CUTE(test_delen));
    s.push_back(CUTE(test_delen_by_zero));
    
    cute::ide_listener<> lis;
    cute::makeRunner(lis)(s, "Тесты калькулятора");
}

int main(int argc, char const *argv[]) {
    runAllTests(argc, argv);
    return 0;
}