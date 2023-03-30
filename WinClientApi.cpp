#include "WinClientApi.h"
#include <iostream>

//definition of variables with external linkage
std::mutex mtx;
MouseInfo mouse_info;
std::atomic<bool> ready_to_send(false);

Client::Client() :
	t1(&Client::ReadMousePos, this, std::ref(mouse_info)),
	t2(&Client::ReadMouseClicks, this, std::ref(mouse_info))
{}

Client::~Client()
{}
void Client::ReadMousePos(MouseInfo& mi)
{
	while(1)
	{
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(500ms);
		{
			std::lock_guard<std::mutex> lock(mtx);
			GetMouseCoord(mi);
			mi.code = NONE;
			ready_to_send.store(true);
		}
	}
}

void Client::ReadMouseClicks(MouseInfo& mi)
{
	while (1)
	{
		if (GetAsyncKeyState(VK_LBUTTON) & 1)	// whether left mouse button
		{
			std::lock_guard<std::mutex> lock(mtx);
			GetMouseCoord(mi);
			mi.code = LMB;
			ready_to_send.store(true);
		}
		if (GetAsyncKeyState(VK_RBUTTON) & 1)	//	or right one
		{
			std::lock_guard<std::mutex> lock(mtx);
			GetMouseCoord(mi);
			mi.code = RMB;
			ready_to_send.store(true);
		}
	}
}

void Client::GetMouseCoord(MouseInfo& mi)
{
	POINT p;
	if (GetCursorPos(&p))
	{
		mi.xCoord = p.x;
		mi.yCoord = p.y;
	}
}

