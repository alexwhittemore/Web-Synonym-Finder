#include "stdafx.h"
#include "database.h"
#include <iostream>
#include <map>
#include <utility>
#include <fstream>
#include <string>
#include "Form1.h"
#include <time.h>

using namespace std;
using namespace System;

void MarshalStringDB ( String ^ s, std::string& os ) {
   using namespace Runtime::InteropServices;
   const char* chars = 
      (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}

string to_lowercase(std::string word)
{
  const int length = word.length();
  for (int ii=0;ii<length;++ii)
    {
      word[ii] = tolower(word[ii]);
    }
  return word;
}

// start with the constructor
database::database(WebSynonymFinder::Form1 ^f)
{
	mainForm = f;
	dictArray = gcnew array<String ^>(dictSize);
	data = new multimap<std::string,int>; // allocates new space for the database

  // create an array for the dictionary
  // I am keeping it as an array in ram for fast searching
  // size read off of line numbers in dictionary.txt
  // should be made more general in case of dictionary change
  ifstream dictFile;
  dictFile.open("dictionary.txt");
  if (!dictFile) // testing if file open
    {
      cout << "Error opening dictionary file" << endl;
    }
  int index = 0; // dictionary must progress start at line 1
  string line;
  while(getline(dictFile,line)&&index<dictSize)
	{
		line=line.substr(0,(int)line.size());
		line = to_lowercase(line);
		String^ cliLine = gcnew String(line.c_str());
		dictArray[index] = cliLine;
		index++;
    }
  dictFile.close();
}

int database::update(System::String ^sysWord,int prox)
{
	//srand ( time(NULL) );
	std::string word;
	MarshalStringDB(sysWord,word);
  word = to_lowercase(word);
  // add another instance of the word to the database
  data->insert( pair<string,int>(word,prox));
  // need to be able to tell if it is a word
  bool isWord = database::is_word(word);
  // find the average proximity

  multimap<std::string, int>::iterator itr;
  multimap<std::string, int>::iterator lastElement;

  itr = data->find(word);
  if (itr == data->end())
    {
      cout << "Error: "<<word<<" not found.";
      // didn't find the word
    }

  // one past the last instance of word
  lastElement = data->upper_bound(word);

  // for each element from itr to lastElement
  double count = 0;
  double runsum = 0;
  for (;itr != lastElement; ++itr)
    {
      if (itr->first==word)
	{
	  count++;
	  runsum += itr->second;
	}
    }
  double ave = runsum/count;
  // tells the gui to updata
  if(count>3)
  {
	mainForm->update(mainForm,sysWord,ave,isWord);
  }
	/*
	//Do the random word
	System::String ^randStr = dictArray[rand()*1000%dictSize];
	std::string randword;
	MarshalStringDB(randStr,randword);
	randword = to_lowercase(randword);
	// add another instance of the word to the database
	data->insert( pair<string,int>(randword,rand()%10));
	// need to be able to tell if it is a word
	bool israndWord = database::is_word(randword);
	// find the average proximity
	double randave = database::prox_mean(randword);

	mainForm->update(mainForm,randStr,randave,israndWord);
  */
  return 0;
}


double database::prox_mean(std::string word)
{
  multimap<std::string, int>::iterator itr;
  multimap<std::string, int>::iterator lastElement;

  itr = data->find(word);
  if (itr == data->end())
    {
      cout << "Error: "<<word<<" not found.";
      return 0; // didn't find the word
    }

  // one past the last instance of word
  lastElement = data->upper_bound(word);

  // for each element from itr to lastElement
  double count = 0;
  double runsum = 0;
  for (;itr != lastElement; ++itr)
    {
      if (itr->first==word)
	{
	  count++;
	  runsum += itr->second;
	}
    }
  double ave = runsum/count;
  return ave;
  
}

bool database::is_word(std::string word)
{
  int ii;
  int comp;
  int min = 0;
  int max = dictSize;
  // this will go into the dictionary and look for the word
  // it uses a binary search pattern
while (min<=max)
    {
      ii = (min+max)/2;

	  std::string nativeString;
	  MarshalStringDB(dictArray[ii], nativeString);
      comp = word.compare(nativeString);
      if (comp==0)
	{
	  cout << word<< " is a word!" << endl;
	  return 1;
	}
      else if (comp < 0)
	{
	  max = ii-1;
	}
      else
	{
	  min = ii+1;
	  }
	  }
	cout<< word <<" is not a word!" << endl;
  return 0;
}

