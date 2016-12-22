#include<iostream>
#include<vector>
#include<Windows.h>
#include<Windowsx.h>

#define ABSOLUTE_X 65535
#define ABSOLUTE_Y 65535


//Returns an input to move the mouse to the specified x and y coordinates
//x and y are specified by their screen coordinates
INPUT moveMouse(int x, int y) {
	INPUT input = {0};

	std::cout << x << " " << y << std::endl;

	//Get screen information
	int screenX = GetSystemMetrics(SM_CXVIRTUALSCREEN);
	int screenY = GetSystemMetrics(SM_CYVIRTUALSCREEN);

	//Get current mouse position information
	//POINT mouseP;
	//GetCursorPos(&mouseP);

	//Set action information
	input.type = INPUT_MOUSE;
	input.mi.dx = x * ABSOLUTE_X / screenX;
	input.mi.dy = y * ABSOLUTE_Y / screenY;
	input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE;
	
	return input;
}

//Clicks the mouse
void clickMouse() {
	INPUT input = { 0 };
	INPUT input2 = { 0 };
	input.type = INPUT_MOUSE;
	input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
	input2.type = INPUT_MOUSE;
	input2.mi.dwFlags = MOUSEEVENTF_LEFTUP;
	SendInput(1, &input, sizeof INPUT);
	SendInput(1, &input2, sizeof INPUT);
}

std::vector<POINT> memorizeClicks(int numberOfClicks) {
	POINT mouseP;
	std::vector<POINT> v(numberOfClicks);
	for(int i = 0; i < numberOfClicks; i++) {
		while (true) {
			if ((GetKeyState(VK_LBUTTON) & 0x80) != 0) {
				GetCursorPos(&mouseP);
				v[i] = mouseP;
				Sleep(500);
				break;
			}
		}
	}

	return v;
}

int main(int arc, char* argv[]) {
	//Set 1 time variables
	std::cout << "AutoClicker Test" << std::endl;
	Sleep(1000);

	//Ask user for input
	int delay;
	int numberOfClicks;
	std::cout << "Enter Delay (ms): ";
	std::cin >> delay;
	std::cout << "NumberOfClicks: ";
	std::cin >> numberOfClicks;

	std::vector<POINT> v = memorizeClicks(numberOfClicks);

	INPUT input;
	for (int i = 0; i < v.size(); i++) {
		Sleep(delay);
		input = moveMouse(v[i].x, v[i].y);
		SendInput(1, &input, sizeof INPUT);
		clickMouse();
	}

	return 0;
}