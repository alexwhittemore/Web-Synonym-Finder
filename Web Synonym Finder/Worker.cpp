#include "StdAfx.h"
#include "Worker.h"
#include "Form1.h"
//Worker::Worker(void){
//}
Worker::Worker(WebSynonymFinder::Form1 ^f){
	mainForm = f;
}
void Worker::doStuff(){
	System::Threading::Thread::Sleep(1000);
	mainForm->update(mainForm, "foo", 1.2, true);
	System::Threading::Thread::Sleep(1000);
	mainForm->update(mainForm, "bartokthedestroyelakjsdlfkjasdljalkjelelkjefarandall", 1.3, false);
	System::Threading::Thread::Sleep(1000);
	mainForm->update(mainForm, "foo", 1.5, true);
}