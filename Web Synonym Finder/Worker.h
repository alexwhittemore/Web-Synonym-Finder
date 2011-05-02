#pragma once

namespace WebSynonymFinder{
	ref class Form1;
}
//Why? http://social.msdn.microsoft.com/Forums/en-IE/Vsexpressvc/thread/de23ed79-a807-4a9a-979b-046976e52ce0

ref class Worker
{
public:
//	Worker(void);
	Worker(WebSynonymFinder::Form1 ^f);
	void doStuff();
private:

	WebSynonymFinder::Form1 ^mainForm;
};

