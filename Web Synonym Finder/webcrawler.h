#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include "database.h"
#include "NetworkParser.h"
#include "webcrawler.h"

using namespace System;
using namespace std;
using namespace System::Collections::Generic;

namespace WebSynonymFinder{
	ref class Form1;
	ref class database;
}
//Why? http://social.msdn.microsoft.com/Forums/en-IE/Vsexpressvc/thread/de23ed79-a807-4a9a-979b-046976e52ce0

ref class webcrawler
{
public:
	webcrawler(WebSynonymFinder::Form1 ^f, String ^url, int count, String ^myword);
	database ^mybase; 

	void crawl();
private:
	WebSynonymFinder::Form1 ^mainForm;
	int firstindex;
	int secondindex;
	int itcount;
	int sizeurl;
	int sizewords;
	int found;
	int ii;
	List <String ^>  ^urlQ;
	List <String ^>::Enumerator ^it;

	List <String ^> ^foundwords;
	List <String ^>::Enumerator ^it3;

	List <int> ^foundindex;
	List <int>::Enumerator ^it2;

	List <int> ^startindex;
	List <int>::Enumerator ^it4;
	int sizeword;

protected:
	String ^url1;
	String ^word;
	int pages;
};

