#include "StdAfx.h"
#include "Gui.h"
#include <string>


Gui::Gui(Form1 *formPointer){
	mainForm = formPointer;
}
Gui::setForm(Form1 *form){
	mainform=form;
}
void Gui::update(string word, int count){
}
