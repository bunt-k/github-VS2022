#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <cstdlib>
#include "MemoryLeakTest.h"

// 메모리 누수 예제 1: 기본적인 메모리 누수
void basicMemoryLeak() {
    int* ptr = new int(42);
    // delete를 호출하지 않고 함수가 종료됨
    // Cppcheck: memory leak - ptr이 해제되지 않음
}

// 메모리 누수 예제 2: 조건문에서의 메모리 누수
void conditionalMemoryLeak(bool condition) {
    int* data = new int[100];
    
    if (condition) {
        // 에러 상황 발생 시 early return
        return; // Cppcheck: memory leak - data가 해제되지 않음
    }
    
    delete[] data;
}

// 메모리 누수 예제 3: 예외 발생 시 메모리 누수
void exceptionMemoryLeak() {
    int* numbers = new int[10];
    
    try {
        throw std::runtime_error("Test exception");
        delete[] numbers; // 이 라인은 실행되지 않음
    }
    catch (const std::exception& e) {
        // 예외 처리 시 메모리 해제를 잊음
        std::cout << "Exception occurred: " << e.what() << std::endl;
        // Cppcheck: memory leak - numbers가 해제되지 않음
    }
}

// 메모리 누수 예제 4: 포인터 재할당으로 인한 메모리 누수
void reassignmentMemoryLeak() {
    int* value = new int(10);
    value = new int(20); // 첫 번째 할당된 메모리가 누수됨
    delete value; // 두 번째 할당된 메모리만 해제됨
}

// 메모리 누수가 없는 올바른 예제 (비교용)
void correctMemoryManagement() {
    int* ptr = new int(42);
    delete ptr; // 올바른 메모리 해제

    int* arr = new int[100];
    delete[] arr; // 배열 메모리 올바르게 해제
}

// ResourceManager 클래스 구현
ResourceManager::ResourceManager() : resource(new int(0)) {}

ResourceManager::~ResourceManager() {
    // delete resource; // 주석 처리하여 메모리 누수 발생
}

/*int main() {
    std::cout << "Starting memory leak test" << std::endl;

    // 각 메모리 누수 시나리오 테스트
    basicMemoryLeak();
    conditionalMemoryLeak(true);
    exceptionMemoryLeak();
    reassignmentMemoryLeak();

    // 메모리 누수가 있는 클래스 사용
    {
        ResourceManager rm;
    } // 스코프를 벗어날 때 소멸자 호출, 하지만 메모리는 해제되지 않음

    std::cout << "Memory leak test completed" << std::endl;
    return 0;
}*/ 
