#include "Randomforest.h"
//随机森林 类成员函数的定义

RandomForest::RandomForest(float** dataset, int* labelset, int TreeNum, int maxDepth,
	int SampleNumPerTree, int minSampleNumPerNode, int featureNum, int classNum)
{
	this->TreeNum = TreeNum;
	//初始化树   
	this->carTreeArray.resize(this->TreeNum);
	//carTreeArray = new Tree[this->TreeNum * sizeof(Tree)];
	for (int i = 0; i < TreeNum; i++) {
		this->carTreeArray[i] = new Tree(dataset, labelset, maxDepth, SampleNumPerTree, 
											minSampleNumPerNode, featureNum, classNum);
	}
}
RandomForest::~RandomForest()
{
	for (int i = 0; i < this->TreeNum; i++) {
		delete carTreeArray[i];
	}
}
void RandomForest::train()
{
	//调用函数的时候，已经执行过初始化!
	//目前  树的数组  与  每棵树的结点数组  都已经初始化完成
	for (int i = 0; i < this->TreeNum; i++) {
		cout << "当前正在训练第 " << i << " 棵树..." << endl;
		carTreeArray[i]->train();
	}
	cout << "训练完成！" << endl;
	return;
}