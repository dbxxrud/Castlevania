#include "GameEngineTime.h"
#include <Windows.h>


GameEngineTime GameEngineTime::MainTimer;

GameEngineTime::GameEngineTime() 
{
	QueryPerformanceFrequency(&Count); // 1초에 이 컴퓨터는 천만을 셀 수 있다
	// 8바이트를 넘겨서 8바이트 메모리를 수정해줌
	Reset();
}

GameEngineTime::~GameEngineTime() 
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Cur);
	Prev = Cur;
}

// 프레임 사이에서 실행되어야할 함수들은 다 업데이트라고 이름을 지을 것이다.
// 얘는 매프레임 마다 돌면서 그 사이에서 실행되는것을 목적으로 하는 함수다
void GameEngineTime::Update()
{
	QueryPerformanceCounter(&Cur);
	Tick = Cur.QuadPart - Prev.QuadPart;

	// 8바이트 실수형                  사이값        /          셀수있는 시간
	DoubleDelta = static_cast<double>(Tick) / static_cast<double>(Count.QuadPart);
	Prev.QuadPart = Cur.QuadPart;
	FloatDelta = static_cast<float>(DoubleDelta);
}

