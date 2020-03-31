#include "Sample.h"
void Sample::randomSelectData(int N)
{
//随机数种子已初始化
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
		FeatureIndex = new int[N];
		for (int i = 0; i < N; i++) {
			FeatureIndex[i] = -1;
		}
		for (int i = featureNum - N; i < featureNum; i++) {
			int temp = rand() % i;
			bool flag = false;
			for (int j = 0; j < N; j++) {
				if (temp == FeatureIndex[j]) {
					flag = true;
					break;
				}
			}
			if (flag == true) {
				FeatureIndex[i - featureNum + N] = i;
			}
			else
				FeatureIndex[i - featureNum + N] = temp;
		}
		featureNum = N;
	}
}

void Sample::ReadFromFatherSetIndex(int* Indexarr, int start, int count)
{
	SetIndex = new int[count];
	for (int i = 0; i < count; i++) {
		SetIndex[i] = Indexarr[start + i];
	}
	//更新结点样本数
	this->sampleNum = count;
}

Sample::~Sample()
{
	delete[] SetIndex;
	delete[] FeatureIndex;
}