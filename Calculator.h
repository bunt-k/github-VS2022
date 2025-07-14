#pragma once

class Calculator {
public:
    // 두 수를 더하는 함수
    int Add(int a, int b) {
        return a + b;
    }

    // 두 수를 빼는 함수
    int Subtract(int a, int b) {
        return a - b;
    }

    // 두 수를 곱하는 함수
    int Multiply(int a, int b) {
        return a * b;
    }

    // 두 수를 나누는 함수
    double Divide(int a, int b) {
        if (b == 0) {
            throw "0으로 나눌 수 없습니다!";
        }
        return static_cast<double>(a) / b;
    }
}; 