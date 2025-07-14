#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <memory>
#include <cstdlib>

// 메모리 누수 테스트를 위한 함수 선언
void basicMemoryLeak();
void conditionalMemoryLeak(bool condition);
void exceptionMemoryLeak();
void reassignmentMemoryLeak();
void correctMemoryManagement();

// 메모리 누수 테스트를 위한 클래스 선언
class ResourceManager {
private:
    int* resource;

public:
    ResourceManager();
    ~ResourceManager();
}; 