#pragma once
#include <string>
#include "Form1.h"
ref class Gui
{
public:
	Gui(Form1 *formPointer);
	void update(string word, int count);
	void setForm(Form1 *form);
private:
	Form1 *mainForm;
};

