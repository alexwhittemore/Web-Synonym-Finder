#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>
#include <cmath>
#include "database.h"
#include "NetworkParser.h"
#include "webcrawler.h"
#include <time.h>
using namespace std;

void MarshalString ( String ^ s, std::string& os ) {
   using namespace Runtime::InteropServices;
   const char* chars = 
      (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}

webcrawler::webcrawler(WebSynonymFinder::Form1 ^f, String ^url, int count, String ^myword){
	//srand ( time(NULL) );
	url1 = url;
	pages=count;
	word= myword;
	mainForm = f;
	urlQ = gcnew List <String ^>;
	foundwords = gcnew List <String ^>;
	foundindex = gcnew List <int>;
	startindex = gcnew List <int>;
}

void webcrawler::crawl()
{
sizeword=word->Length;
//Linked list for the qs
mybase = gcnew database(mainForm);
//iterator for list purposes

//std::string stdUrl1;
//MarshalString(url1, stdUrl1);
urlQ->Add(url1);
//it= urlQ->First().GetEnumerator();


ii=0;
while(ii<pages)
{ //Assigns 
	std::string stdStringTextUrl;
	String ^tempString = urlQ[ii];
	MarshalString(tempString, stdStringTextUrl);
	PAGEINFO mydata = getTextUrl(stdStringTextUrl); 
	//PAGEINFO mydata = getTextUrl(it->Current);
	sizeurl= mydata.url.length();
	sizewords= mydata.text.length();

	firstindex=0;
	secondindex=0;
	
	
	//std::string tempString2;
	string myDataUrlString = mydata.url + " "; //Manually add a space so that we can't possibly encounter an index out of bounds below

	while(secondindex <sizeurl-1){ //*****!!!! Note need the string to be terminated with a whitespace as well as a NULL
	//As your looping through the string look for spaces to indicate next words
		while(myDataUrlString[secondindex] != ' '){//If you don't find a space increment the second index
			if (secondindex==sizeurl)
				break;
			secondindex++;
		}
		//When the space is found the loop is broken and a substr from the first index to the second index is pushed to the back of the word list
		String^ tempString2 = gcnew String(myDataUrlString.substr(firstindex,secondindex-firstindex).c_str());
		urlQ->Add(tempString2);
		//First index is moved to where second index left off+1 and the loop continues
		secondindex++;
		firstindex=secondindex;
	}

firstindex=0;
secondindex=0;


	mydata.text.append(" "); //Manually add a space so that we can't possibly encounter an index out of bounds below

	//Loop through until you find the null
	while(secondindex< sizewords-1) //*****!!!! Note need the string to be terminated with a whitespace as well as a NULL
	{//As your looping through the string look for spaces to indicate next words
	while(mydata.text[secondindex] != ' ')
	{//If you don't find a space increment the second index
		secondindex++;
	}
	//When the space is found the loop is broken and a substr from the first index to the second index is pushed to the back of the word list
	String^ tempString3 = gcnew String(mydata.text.substr(firstindex,secondindex-firstindex).c_str());
	foundwords->Add(tempString3);
	//Assigns the starting position of every word in a linked list
	startindex->Add(firstindex);
		//First index is moved to where second index left off+1 and the loop continues
	secondindex++;
	firstindex=secondindex;
	
	}



	found=0;
	//Looks for the word until the word can no longer be found


	std::string stdWord;
	MarshalString(word, stdWord);
	do
	{ 
		if (found==0){
			// IF this is the first found word you are replacing don't use the offset, you want to start from 0
			found=mydata.text.find(stdWord);
			foundindex->Add(found);
		}
		else{
			//Otherwise you want to search from where you found the last word + the size of the word
			found=mydata.text.find(stdWord, found+sizeword);
			foundindex->Add(found);
		}

	} while (mydata.text.find(stdWord, found+sizeword) != -1);
//Initializses iterators for the index list and the found word list
		//it4->Reset();
		//it2->Reset();
		//NOTE FOUND WORDS IS A LIST OF ALL THE WORDS IN THE LIST, NOT THE WORDS YOU ARE SEARCHING FOR
		//it3->Reset();
//This implementation will find the distance between every instance of the words you found, and every other word
		//If you are looking for fox in "The quick brown fox jumped the other fox" You will receive proximities for other with regards to the 1st and 2nd
		//Instance of fox
	itcount=0;
//database mydata;	ask rusty about creating database
	
do
	{
		//it4->System->Collections->IEnumerator->Reset;
		//it2->Reset;
		//it3->Reset;
		it = urlQ->GetEnumerator();
		it3 = foundwords->GetEnumerator();
		it2 = foundindex->GetEnumerator();
		it4 = startindex->GetEnumerator();
		it2->MoveNext();
		it3->MoveNext();
		it4->MoveNext();
		for (int ll=0; ll< int(startindex->Count); ll++){
			//If the start index of the word is equal to the word you are looking for do not pass the proximity
			if (it4->Current==it2->Current)
			{}
			else{
			//Otherwise update the database with the word (iterator3) and the distance between the found word (iterator2) and the given word in the string (iterator4)
			mybase->update( it3->Current, abs(it2->Current-it4->Current) );  //
			}
	it3->MoveNext();
	it4->MoveNext();
	
	
	}
	it2->MoveNext();
	itcount++;
	}
	while (itcount< int(foundindex->Count));

	
	
	ii++;
	
	//mybase->update(word,rand()%10);
}

	//return 1;// Need to return -1 for failure?
}

/*
int main()
{webcrawler mycrawl;
mycrawl.crawl("http://www.asciitable.com/",2, "table");
}*/