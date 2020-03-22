#include "Sample.h"
void Sample::randomSelectData(int N)
{
	//初始化随机数种子
	srand(static_cast<unsigned int>(time(NULL)));
	SetIndex = new int[N];
	for (int i = 0; i < N; i++) {
		SetIndex[i] = rand() % N;
	}
}

void Sample::randomSelectFeatrue(int N)
{
	if (N >= featureNum) {
		FeatureIndex = new int[featureNum];
		for (int i = 0; i < featureNum; i++) {
			FeatureIndex[i] = i;
		}
	}
	else {
		//TODO:随机选择不重复的  特征点索引
	}
}

void Sample::ReadFromFatherSetIndex(int* Indexarr, int start, int count)
{
	SetIndex = new int[count];
	for (int i = 0; i < count; i++) {
		SetIndex[i] = Indexarr[start + i];
	}
}

Sample::~Sample()
{
	delete[] SetIndex;
	delete[] FeatureIndex;
}