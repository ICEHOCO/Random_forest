#pragma once
#ifndef  DATAPROCESS_H
#define  DATAPROCESS_H

#include "stdafx.h"

#define DATAHAVE 150 
#define LABELHAVE 150

/***********************************/
float** ReadData(bool display);
int* ReadLabel(bool display);
/***********************************/

vector<float> dateRandGenerate(int count);
vector<int> labelRandGenerate(int count);
static const vector<float> DataSet = dateRandGenerate(DATAHAVE);
static const vector<int> LabelSet = labelRandGenerate(LABELHAVE);

vector<float> readData(int NumtoRead, bool display);
vector<float> readData(int DatatoReadStart, int NumtoRead, bool display);

vector<int> readLabel(int NumtoRead, bool display);
vector<int> readLabel(int LabeltoReadStart, int NumtoRead, bool display);

//需要去保证宏定义的一致性
bool ReadAll(vector<float>* dataset, vector<int>* labelset, int NumtoRead, bool display);
#endif // ! DATAPROCESS_H
