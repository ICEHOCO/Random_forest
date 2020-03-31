#pragma once
#ifndef RANDOMFOREST_H
#define RANDOMFOREST_H

#include "stdafx.h"
#include "Tree.h"

struct Result {
	int classnum;
	float prob;
};

//随机森林 类 的声明
class RandomForest {
public:
	//构造函数
	RandomForest() {};
	RandomForest(float** dataset, int* labelset, int TreeNum,
		int maxDepth, int SampleNumPerTree, int minSampleNumPerNode, int featureNum, int classNum, int RandFeatureNum);
	//析构函数
	~RandomForest();
	//训练函数
	void train();
	//预测函数
	Result* RandomForest::predict(float** testSet, int testNum);
	/*成员变量获取函数*/
	int get_TreeNum() { return this->TreeNum; }

	vector<Tree*> carTreeArray;

private:
	int TreeNum;
	int predictResult;
	int classNum;
};

#endif // !RANDOMFOREST_H
