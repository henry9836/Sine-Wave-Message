#include <iostream>
#include <windows.h>
#include <string>
#include <stdio.h>     
#include <math.h>       
#include <conio.h>

#define PI 3.1415926

using namespace std;

void GotoXY(int _iX, int _iY, string msg)
{
	COORD point;
	point.X = _iX;
	point.Y = _iY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}
void ClearScreen()
{
	COORD coordScreen = { 0, 0 };
	DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD dwConSize;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
	SetConsoleCursorPosition(hConsole, coordScreen);
}


void find_and_replace(string& source, string const& find, string const& replace)
{
	for (string::size_type i = 0; (i = source.find(find, i)) != string::npos;)
	{
		source.replace(i, find.length(), replace);
		i += replace.length();
	}
}

int main() {

	HWND console = GetConsoleWindow();
	RECT w;
	GetWindowRect(console, &w);

	MoveWindow(console, w.left, w.top, 1000, 700, TRUE); //Resize console window

	float _amplitude, _period, _direction, _speed, resultx, resulty, xpos;
	string _text, _temp;
	int count, iT, colorcount, fancy_mode;

	colorcount = 0;
	_amplitude = -1;
	_period = -1;
	_direction = -1;
	_speed = -1;
	fancy_mode = -1;

	while (_amplitude <= 0)
	{
		cout << "Amplitude of wave: ";
		cin >> _amplitude;
		if (_amplitude <= 0) {
			cout << "Invalid Input" << endl;
		}
	}
	while (_period <= 0)
	{
		cout << "Period of wave: ";
		cin >> _period;
		if (_period <= 0) {
			cout << "Invalid Input" << endl;
		}
	}
	cout << "Direction of wave (1 = right-left, 2=left-right): ";
	cin >> _direction;
	while (_speed <= 0)
	{
		cout << "Speed of wave (the lower the number the faster): ";
		cin >> _speed;
		if (_speed <= 0) {
			cout << "Invalid Input" << endl;
		}
	}
	cout << "Message (spaces are not allowed): ";
	cin >> _text;
	cout << "Enable Fancy Mode? (0 - None, 1-Fancy): ";
	cin >> fancy_mode;


	count = -1;

	while (_text.length() < 110){
		_temp = _text;
		_text = " ";
		for (int k = 0; k < (110 - _temp.length()); k++) {
			_text.append(" ");
		}
		_text.append(_temp);
		
	}

	_speed += 20;

	while (true)
	{
		ClearScreen();
		xpos = 0;
		count += 1;

		if (_direction == 1) {

			for (int i = 0; i < 110; i++) {
				resultx = xpos;
				resulty = _amplitude * sin(((2 * PI)*xpos) / _period);
				COORD coordScreen = { resultx, resulty + 15 };
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleCursorPosition(hConsole, coordScreen);

				int charIndex = (i + count) % _text.length();
				cout << _text[charIndex];

				
				
				/*
				//LEL RAM GETS PULLED
				if (i <= _text.length()) {
					if ((count) <= _text.length()) {
						cout << _text[i + count];
					}
					else {
						count = -1;
					}
				}
				else {

				}*/

				xpos += 1;
			}
		}
		if (_direction == 2) {

			for (int i = 0; i > -110; i--) {
				resultx = xpos;
				resulty = _amplitude * sin(((2 * PI)*xpos) / _period);
				COORD coordScreen = { resultx, resulty + 15 };
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleCursorPosition(hConsole, coordScreen);

				int charIndex = (i + count) % _text.length();
				cout << _text[charIndex];

				xpos += 1;
			}
		}
		GotoXY(0, 0, "");
		cout << "Made By Henry Oliver";
		if (fancy_mode == 1) {
			if (_text.find(" ") != std::string::npos) {
				find_and_replace(_text, " ", "+");
			}
			if (_text.find("+") != std::string::npos) {
				find_and_replace(_text, "+", "*");
			}
			if (_text.find("x") != std::string::npos) {
				find_and_replace(_text, "x", "+");
			}
			if (_text.find("*") != std::string::npos) {
				find_and_replace(_text, "*", "x");
			}
			if (colorcount == 0) {
				system("COLOR 0C");
			}
			if (colorcount == 1) {
				system("COLOR 06");
			}
			if (colorcount == 2) {
				system("COLOR 0E");
			}
			if (colorcount == 3) {
				system("COLOR 0A");
			}
			if (colorcount == 4) {
				system("COLOR 09");
			}
			if (colorcount == 5) {
				system("COLOR 05");
			}
			if (colorcount == 6) {
				system("COLOR 0F");
				colorcount = -1;
			}
			colorcount += 1;
			Beep(1000, _speed);
		}
		else {
			Sleep(_speed);
		}

	}

	return 0;
}