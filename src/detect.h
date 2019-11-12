#pragma once
#ifndef DETECT_H
#define DETECT_H
#include <string>

#include "Setuper.h"

using namespace std;

void detectAndSave(string, string, string);
void TestCampaign(Setuper*);
void singleDetection(string, string);

#endif