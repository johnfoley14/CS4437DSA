#ifndef INDEXBOOKS_H
#define INDEXBOOKS_H

#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

using namespace std;

string toLowerCase(const string &str);
string removePunctuation(const string &str);
void createCSVs();

#endif