#include "Randomforest.h"
//随机森林 类成员函数的定义

RandomForest::RandomForest(float** dataset, int* labelset, int TreeNum, int maxDepth,
	int SampleNumPerTree, int minSampleNumPerNode, int featureNum, int classNum, int RandFeatureNum)
{
	this->TreeNum = TreeNum;
	this->classNum = classNum;
	this->AllWeight = 1.0 * TreeNum;
	//初始化树   
	this->carTreeArray.resize(this->TreeNum);
	for (int i = 0; i < TreeNum; i++) {
		this->carTreeArray[i] = new Tree(dataset, labelset, maxDepth, SampleNumPerTree, 
											minSampleNumPerNode, featureNum, this->classNum, RandFeatureNum);
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
		if (i % 10 == 0) {
			cout << "随机森林训练进度： " << i << "/100 ..." << endl;
		}
		carTreeArray[i]->train();
	}
	cout << "训练完成！" << endl;
	return;
}

void RandomForest::pre_predict(float** testSet, int* labelSet, int testNum)
{
	for (int i = 0; i < testNum; i++) {
		for (int j = 0; j < TreeNum; j++) {
			if (labelSet[i] != carTreeArray[j]->predict(testSet[i])) {
				carTreeArray[j]->Punish();
			}
			else {
				carTreeArray[j]->Reward();
			}
		}
	}
	//更新森林总权重值
	this->AllWeight = 0;
	for (int i = 0; i < TreeNum; i++) {
		this->AllWeight += carTreeArray[i]->get_Weight();
	}
}

void RandomForest::pre_predict(float** testSet, int* labelSet, int testNum, float alpha, float beta)
{
	for (int i = 0; i < testNum; i++) {
		for (int j = 0; j < TreeNum; j++) {
			if (labelSet[i] != carTreeArray[j]->predict(testSet[i])) {
				carTreeArray[j]->Punish(alpha);
			}
			else {
				carTreeArray[j]->Reward(beta);
			}
		}
	}
	//更新森林总权重值
	this->AllWeight = 0;
	for (int i = 0; i < TreeNum; i++) {
		this->AllWeight += carTreeArray[i]->get_Weight();
	}
}




Result* RandomForest::predict(float** testSet, int testNum)
{
	Result* testLabelset = new Result[testNum];
	double* resultProb;
	resultProb = new double [classNum];
	for (int i = 0; i < testNum; i++) {
		//初始化
		for (int j = 0; j < classNum; j++) {
			resultProb[j] = 0;
		}
		//每颗树给出结果
		for (int j = 0; j < TreeNum; j++) {
			carTreeArray[j]->predict(testSet[i], &resultProb);
		}

		int max = 0;
		for (int j = 1; j < classNum; j++) {
			if (resultProb[max] < resultProb[j])
				max = j;
		}
		testLabelset[i].classnum = max;
		testLabelset[i].prob = resultProb[max];
	}
	delete[] resultProb;
	return testLabelset;
}