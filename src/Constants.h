#pragma once
#ifndef CONSTANTS_H
#define CONSTANTS_H

#define USESETUP 0
#define SETUPNAME 1
#define POSINFOFILENAME 2
#define NEGINFOFILENAME 3
#define CLASSIFIER 4
#define WIDTH 5
#define HEIGHT 6
#define POSPROBES 7
#define NEGPROBES 8
#define STAGES 9

#define PATH_TO_TOPOSITIVE_SAMPLES "Images/ToPositive"
#define PATH_TO_NEGATIVE_SAMPLES "Images/Negative"
#define PATH_TO_POSITIVE_SAMPLES "Images/Positive"
#define PATH_TO_TEST_SAMPLES "Images/Test"
#define PATH_TO_TEST_RESULT "Images/TestResult"
#define PATH_TO_TEST_PLANS "Images/TestPlans"
#define PATH_TO_DATA ""

#define PATH_TO_TRAINED_CLASSIFIERS "Images/Classifiers"

#define SAMPLE_TOOL "opencv_createsamples.exe"
#define TRAIN_TOOL "opencv_traincascade.exe"
#define ANNOTATION "opencv_annotation.exe"
#endif