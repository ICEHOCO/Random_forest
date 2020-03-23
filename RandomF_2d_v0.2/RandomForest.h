#pragma once
#ifndef RANDOMFOREST_H
#define RANDOMFOREST_H

#include "stdafx.h"
#include "Tree.h"
//���ɭ�� �� ������
class RandomForest {
public:
	//���캯��
	RandomForest() {};
	RandomForest(float** dataset, int* labelset, int TreeNum,
		int maxDepth, int SampleNumPerTree, int minSampleNumPerNode, int featureNum, int classNum);
	//��������
	~RandomForest();
	//ѵ������
	void train();
	//Ԥ�⺯��
	int* predict(float** testSet, int testNum);
	/*��Ա������ȡ����*/
	int get_TreeNum() { return this->TreeNum; }

	vector<Tree*> carTreeArray;

private:
	int TreeNum;
	int predictResult;
	int classNum;
};

#endif // !RANDOMFOREST_H
