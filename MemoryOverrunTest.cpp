#define _CRT_SECURE_NO_WARNINGS
#include "MemoryOverrunTest.h"
#include <cstring>
#include <iostream> 

void arrayBoundsOverrun() {
    std::cout << "Starting array bounds overrun test\n";
    int arr[5] = {1, 2, 3, 4, 5};
    
    // Cppcheck가 감지해야 할 배열 범위 초과 접근
    for(int i = 0; i <= 5; i++) {  // 의도적으로 배열 크기를 초과하는 접근
        arr[i] = i * 2;  // i가 5일 때 배열 범위를 벗어남
    }
    
    std::cout << "Array bounds overrun test completed\n";
}

void dynamicMemoryOverrun() {
    std::cout << "Starting dynamic memory overrun test\n";
    int* ptr = new int[10];
    
    // 할당된 크기를 초과하여 메모리 접근
    for(int i = 0; i < 15; i++) {  // 의도적으로 할당된 크기보다 큰 범위 접근
        ptr[i] = i;  // 배열 크기(10)를 초과하는 접근
    }
    
    delete[] ptr;
    std::cout << "Dynamic memory overrun test completed\n";
}

void stackBufferOverflow() {
    std::cout << "Starting stack buffer overflow test\n";
    char smallBuffer[5];
    const char* largeString = "This is a very long string";
    
    // 작은 버퍼에 큰 문자열을 복사하여 오버플로우 발생
    strcpy(smallBuffer, largeString);  // 버퍼 크기(5)보다 큰 문자열(23) 복사
    
    std::cout << "Stack buffer overflow test completed\n";
}

void heapBufferOverflow() {
    std::cout << "Starting heap buffer overflow test\n";
    char* buffer = new char[10];
    
    // 할당된 버퍼 크기를 초과하여 데이터 쓰기
    for(int i = 0; i < 20; i++) {  // 의도적으로 할당된 크기보다 큰 범위 접근
        buffer[i] = 'A' + i;  // 버퍼 크기(10)를 초과하는 쓰기
    }
    
    delete[] buffer;
    std::cout << "Heap buffer overflow test completed\n";
}

void stringBufferOverrun() {
    std::cout << "Starting string buffer overrun test\n";
    char dest[10];
    const char* source = "This string is too long for destination";
    
    // 문자열 복사 시 버퍼 오버런
    for(size_t i = 0; i < strlen(source); i++) {  // strlen(source)는 목적지 버퍼 크기보다 큼
        dest[i] = source[i];  // 목적지 버퍼 크기(10)를 초과하는 쓰기
    }
    
    std::cout << "String buffer overrun test completed\n";
} 