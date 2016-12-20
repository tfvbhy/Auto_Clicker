#include<iostream>
#include<windows.h>

#define ABSOLUTE_X 65535
#define ABSOLUTE_Y 65535

int main(int arc, char* argv[]) {
	
	//action being done
	INPUT input = {0};
	
	//Get screen information
	int screenX = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int screenY = GetSystemMetrics(SM_CYVIRTUALSCREEN);
	
	//Set 1 time variables
	int loopCount = 5;
	std::cout << "AutoClicker Test" << std::endl;
	Sleep(1000);

	//Get current information
	POINT mouseP;
	GetCursorPos(&mouseP);

	std::cout << mouseP.x << std::endl;
	
	//Set action information
	//In this case mouse position is being set (to where it current is)
	input.type = INPUT_MOUSE;
	input.mi.dx = mouseP.x * ABSOLUTE_X / screenX;
	input.mi.dy = mouseP.y * ABSOLUTE_Y / screenY;
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	SendInput(1, &input, sizeof INPUT);

	//Need to rewrite legacy code for clicking

	/*
	while (loopCount--) {
		Sleep(1000);
		mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
		mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
		mouse_event(MOUSEEVENTF_ABSOLUTE, 5000,  5000, 0, 0);
		std::cout << x << " " << y << std::endl;
	}
	*/

	return 0;
}