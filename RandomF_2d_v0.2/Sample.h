#pragma once
#ifndef SAMPLE_H
#define SAMPLE_H

#include "stdafx.h"

class Sample {
public:
	/*构造与析构函数*/
	Sample() {  }
	Sample(vector<float>* dataset, vector<int>* labelset, int featureNumSelected)
		:dataset(dataset), labelset(labelset), featureNumSelected(featureNumSelected){	}
	//析构， 重要！！ 防止内存泄漏
	~Sample();

	void randomSelect(int N);

	//const：常量指针 不改变数据集
	const vector<float>* dataset;
	const vector<int>* labelset;
	//应该包含所有的索引，提供给结点或者树使用
	int* dataIndex;
	int* featureIndex;

	int featureNumSelected;
};

#endif
