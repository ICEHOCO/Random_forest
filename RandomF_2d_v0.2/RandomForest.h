#pragma once
#ifndef RANDOMFOREST_H
#define RANDOMFOREST_H

#include "stdafx.h"
#include "Tree.h"

struct Result {
	int classnum;
	float prob;
};

//���ɭ�� �� ������
class RandomForest {
public:
	//���캯��
	RandomForest() {};
	RandomForest(float** dataset, int* labelset, int TreeNum,
		int maxDepth, int SampleNumPerTree, int minSampleNumPerNode, int featureNum, int classNum, int RandFeatureNum);
	//��������
	~RandomForest();
	//ѵ������
	void train();
	//Ԥ-Ԥ����ݽ���޸�Ȩ��
	void pre_predict(float** testSet, int* labelSet, int testNum);
	void pre_predict(float** testSet, int* labelSet, int testNum, float alpha, float beta);
	//Ԥ�⺯��
	Result* predict(float** testSet, int testNum);
	/*��Ա������ȡ����*/
	int get_TreeNum() { return this->TreeNum; }
	float get_AllWeight() { return this->AllWeight; }
	vector<Tree*> carTreeArray;

private:
	int TreeNum;
	int predictResult;
	int classNum;
	float AllWeight;
};

#endif // !RANDOMFOREST_H
