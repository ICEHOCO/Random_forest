#include "Randomforest.h"
//随机森林 类成员函数的定义

RandomForest::RandomForest(vector<float>* dataset, vector<int>* labelset, int TreeNum, 
	int maxDepth, int SampleNumPerTree, int minSampleNumPerNode, int featureNumSelected)
{
	this->TreeNum = TreeNum;
	//初始化树   featureNumSelected
	carTreeArray.resize(TreeNum);
	for (int i = 0; i < TreeNum; i++) {
		carTreeArray[i] = new Tree(dataset, labelset, maxDepth, SampleNumPerTree, minSampleNumPerNode, featureNumSelected);
	}
}