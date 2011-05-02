#pragma once
#include "stdafx.h"
#include "map"

#define dictSize 234936
using namespace System;

namespace WebSynonymFinder{
	ref class Form1;
	ref class database;
}

ref class database{
 public:
  database(WebSynonymFinder::Form1 ^f); // start up the database
  int update(System::String ^word,int prox); // update it
  bool is_word(std::string); //advises if the word is a word
  double prox_mean(std::string word); // finds the average prox
 private:
  std::multimap<std::string,int> *data; // must be pointer
  array<String ^> ^ dictArray;
  WebSynonymFinder::Form1 ^mainForm;
};
