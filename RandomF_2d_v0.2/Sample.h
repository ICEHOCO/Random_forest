#pragma once
#ifndef SAMPLE_H
#define SAMPLE_H

#include "stdafx.h"

class Sample {
public:
	/*��������������*/
	Sample() {  }
	Sample(float** dataset, int* labelset, int featureNum)
		:dataset(dataset), labelset(labelset), featureNum(featureNum){	}
	//������ ��Ҫ���� ��ֹ�ڴ�й©
	~Sample();
	/*���ܺ���*/
	void randomSelectData(int N);
	void randomSelectFeatrue(int N);
	void ReadFromFatherSetIndex(int* Indexarr, int start, int count);
	float** dataset;
	int* labelset;
	//Ӧ�ð������е��������ṩ����������ʹ��
	int* SetIndex;
	int* FeatureIndex;
	int sampleNum;
	int featureNum;
};

#endif
