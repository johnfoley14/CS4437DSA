#ifndef PROCESSINPUT_H
#define PROCESSINPUT_H

#include <cctype>
#include <string>

#include "LinkedList.h"

LinkedList<string> sanitizeLine(string str);

#endif