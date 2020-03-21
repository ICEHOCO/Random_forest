#pragma once
#ifndef SAMPLE_H
#define SAMPLE_H

#include "stdafx.h"

class Sample {
public:
	/*��������������*/
	Sample() {  }
	Sample(vector<float>* dataset, vector<int>* labelset, int featureNumSelected)
		:dataset(dataset), labelset(labelset), featureNumSelected(featureNumSelected){	}
	//������ ��Ҫ���� ��ֹ�ڴ�й©
	~Sample();

	void randomSelect(int N);

	//const������ָ�� ���ı����ݼ�
	const vector<float>* dataset;
	const vector<int>* labelset;
	//Ӧ�ð������е��������ṩ����������ʹ��
	int* dataIndex;
	int* featureIndex;

	int featureNumSelected;
};

#endif
