#pragma once
#ifndef CREATESAMPLE_H
#define CREATESAMPLE_H
#include <string>

#include "Setuper.h"

using namespace std;

void CreateInfoFile(string, string, string);
void CreateInfoFiles(bool automatic = false);
void CreateSamples(Setuper*);
void TrainClassifier(Setuper*);

#endif