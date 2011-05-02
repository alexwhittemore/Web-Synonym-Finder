#pragma once
using namespace std;

struct PAGEINFO {		// structure declaration and definition
	string text;
	string url;
	int error;
};

PAGEINFO getTextUrl(PAGEINFO);