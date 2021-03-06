#pragma once
#ifndef SAMPLE_H
#define SAMPLE_H

#include "stdafx.h"

class Sample {
public:
	/*构造与析构函数*/
	Sample() {  }
	Sample(float** dataset, int* labelset, int featureNum)
		:dataset(dataset), labelset(labelset), featureNum(featureNum){	}
	//析构， 重要！！ 防止内存泄漏
	~Sample();
	/*功能函数*/
	void randomSelectData(int N);
	void randomSelectFeatrue(int N);
	void ReadFromFatherSetIndex(int* Indexarr, int start, int count);
	float** dataset;
	int* labelset;
	//应该包含所有的索引，提供给结点或者树使用
	int* SetIndex;
	int* FeatureIndex;
	int sampleNum;
	int featureNum;
};

#endif
