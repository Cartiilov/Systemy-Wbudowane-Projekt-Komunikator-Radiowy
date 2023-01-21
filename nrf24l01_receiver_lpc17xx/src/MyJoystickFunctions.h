#include "Board_Joystick.h"             // ::Board Support:Joystick
#include <stdbool.h>

#ifndef MY_JOYSTICK_FUNCTIONS
#define MY_JOYSTICK_FUNCTIONS

struct GUI{
	void (*guiPointer)(int);
	bool opt1;
	bool opt2;
};

void innitGUI();

void resetOptions();

void changeOptions();

void JoystickManage();

#endif