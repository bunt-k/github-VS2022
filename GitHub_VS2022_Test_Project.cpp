// GitHub_VS2022_Test_Project.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS // strcpy 보안 경고를 비활성화합니다.

#include <iostream>
#include <cstdlib> // calloc을 위해 추가
#include <cstring> // strcpy를 위해 추가
#include "MemoryLeakTest.h"
#include "MemoryOverrunTest.h"


void MemoryLeakTest()
{
	std::cout << "MemoryLeakTest begin\n" << std::endl;
	// 메모리 해제 하지 않도록 테스트
	int* p = new int[100];
	for (int i = 0; i < 100; i++)
	{
		p[i] = i;
		std::cout << p[i] << " ";
	}
	std::cout << "\n";
	//delete[] p; // 메모리 해제 일부러 하지 않음

	p[100] = 200; // 메모리 접근 오류 발생

	std::cout << "MemoryLeakTest end\n" << std::endl;
}

int main()
{
    std::cout << "GitHub_VS2022_Test_Project!\n";
	std::cout << "GitHub_Cppcheck_Test_Project!\n";
	std::cout << "Google_Test_Project!\n";
	std::cout << "modify uniclode!\n";

	MemoryLeakTest();

    // 메모리 해제 하지 않도록 테스트
	// 아래코드를 calloc 방식으로 수정해서 테스트 하도록 변경해줘.
	int* p = (int*)calloc(sizeof(int), 100); // calloc 방식으로 메모리 할당
	if (p != nullptr) { // nullptr 체크 추가
		for (int i = 0; i < 100; i++)
		{
			p[i] = i;
			std::cout << p[i] << " ";
		}
		std::cout << "\n";
		// free(p); // 메모리 누수 테스트를 위해 의도적으로 해제하지 않음
	}

	// CodeQL이 감지하는 버퍼 오버플로우 코드 추가
	char buffer[10];
	const char* source_string = "0123456789ABCDEF"; // 버퍼보다 긴 문자열
	
	strcpy(buffer, source_string); // 이 줄은 그대로 유지하며, _CRT_SECURE_NO_WARNINGS로 인해 컴파일 오류가 발생하지 않습니다.

	// 수동 문자열 복사 루프를 사용하여 버퍼 오버플로우 유도
	// 이 코드는 컴파일되며, CodeQL은 버퍼 오버플로우를 감지해야 합니다 (CWE-120 또는 CWE-787).
	for (int i = 0; i < 15; ++i) { // buffer의 크기는 10이지만, 15번 반복하여 오버플로우 발생 시도
		if (source_string[i] == '\0') { // 소스 문자열이 예상보다 짧을 경우 루프 종료
			buffer[i] = '\0'; // 현재 위치에 널 문자 삽입 (만약 버퍼 내라면)
			break;
		}
		// i가 9를 초과하면 buffer의 경계를 벗어나 쓰기를 시도합니다.
		buffer[i] = source_string[i]; 
	}
	// 루프가 완료된 후 buffer는 오버플로우되었을 가능성이 높습니다.
	// 또한, source_string의 길이가 15보다 짧다면, 루프는 source_string의 경계를 넘어 읽으려고 시도할 수도 있습니다 (CWE-125).
	// 이 예제에서는 source_string이 충분히 길어 주로 버퍼 쓰기 오버플로우가 발생합니다.
	
	// 오버플로우된 버퍼를 사용하려고 하면 예기치 않은 동작이나 충돌이 발생할 수 있습니다.
	// std::cout << "Buffer content (potentially overflowed): " << buffer << std::endl; // 이 줄은 주석 처리하거나 주의해서 사용

	std::cout << "Buffer overflow test added using manual loop." << std::endl;

	//===================================================================
	std::cout << "Memory leak test started" << std::endl;
	std::cout << "----------------------------------------" << std::endl;

	// 각 메모리 누수 시나리오 테스트
	std::cout << "1. Basic memory leak test" << std::endl;
	basicMemoryLeak();
	
	std::cout << "\n2. Conditional memory leak test" << std::endl;
	conditionalMemoryLeak(true);
	
	std::cout << "\n3. Exception handling memory leak test" << std::endl;
	exceptionMemoryLeak();
	
	std::cout << "\n4. Pointer reassignment memory leak test" << std::endl;
	reassignmentMemoryLeak();

	std::cout << "\n5. Class destructor memory leak test" << std::endl;
	{
		ResourceManager rm;
		std::cout << "ResourceManager object created" << std::endl;
	}
	std::cout << "ResourceManager object destroyed" << std::endl;

	std::cout << "\n6. Correct memory management example" << std::endl;
	correctMemoryManagement();

	std::cout << "\n----------------------------------------" << std::endl;
	std::cout << "Memory leak test completed" << std::endl;
	std::cout << "Program terminated normally, but memory leaks can be detected using Cppcheck." << std::endl;
	
	// 메모리 오버런 테스트 실행
	std::cout << "\n=== Memory overrun test started ===\n" << std::endl;
	
	arrayBoundsOverrun();
	std::cout << std::endl;
	
	dynamicMemoryOverrun();
	std::cout << std::endl;
	
	stackBufferOverflow();
	std::cout << std::endl;
	
	heapBufferOverflow();
	std::cout << std::endl;
	
	stringBufferOverrun();
	std::cout << std::endl;
	
	std::cout << "=== Memory overrun test completed ===\n" << std::endl;

	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
