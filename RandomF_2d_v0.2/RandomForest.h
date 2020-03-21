#pragma once
#ifndef RANDOMFOREST_H
#define RANDOMFOREST_H

#include "stdafx.h"
#include "Tree.h"
//随机森林 类 的声明
class RandomForest {
public:
	//构造函数
	RandomForest() {};
	RandomForest(vector<float>* dataset, vector<int>* labelset, int TreeNum,
		int maxDepth, int SampleNumPerTree, int minSampleNumPerNode, int featureNumSelected);
	//析构函数
	~RandomForest() {};
	//训练函数
	void train(Sample sample);//要对树初始化
	//预测函数
	int predict();
	/*成员变量获取函数*/
	int get_TreeNum() { return this->TreeNum; }

	vector<Tree*> carTreeArray;

private:
	int TreeNum;
	int predictResult;
};

#endif // !RANDOMFOREST_H
