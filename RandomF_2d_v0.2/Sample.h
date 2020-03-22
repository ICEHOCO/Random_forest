#pragma once
#ifndef SAMPLE_H
#define SAMPLE_H

#include "stdafx.h"

class Sample {
public:
	/*��������������*/
	Sample() {  }
	Sample(vector<float>* dataset, vector<int>* labelset, int featureNumSelected)
		:dataset(dataset), labelset(labelset), featureNum(featureNum){	}
	//������ ��Ҫ���� ��ֹ�ڴ�й©
	~Sample();
	/*���ܺ���*/
	void randomSelectData(int N);
	void randomSelectFeatrue(int N);

	//const������ָ�� ���ı����ݼ�
	const vector<float>* dataset;
	const vector<int>* labelset;
	//Ӧ�ð������е��������ṩ����������ʹ��
	int* SetIndex;
	int* FeatureIndex;
	int sampleNum;
	int featureNum;
};

#endif
