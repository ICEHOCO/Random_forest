#include "Randomforest.h"
//���ɭ�� ���Ա�����Ķ���

RandomForest::RandomForest(vector<float>* dataset, vector<int>* labelset, int TreeNum, 
	int maxDepth, int SampleNumPerTree, int minSampleNumPerNode, int featureNumSelected)
{
	this->TreeNum = TreeNum;
	//��ʼ����   featureNumSelected
	carTreeArray.resize(TreeNum);
	for (int i = 0; i < TreeNum; i++) {
		carTreeArray[i] = new Tree(dataset, labelset, maxDepth, SampleNumPerTree, minSampleNumPerNode, featureNumSelected);
	}
}