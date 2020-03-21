// main.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include "Dataprocess.h"	
#include "RandomForest.h"

#define TRAINNUM    200		//训练样本数
#define FEATURENUM  2		//特征点维数
#define TESTNUM		50		//测试样本数
#define TREENUM		100		//树的数量
#define MAXDEPTH	5		//每棵树最大深度
int main()
{
	vector<float> dataset;
	vector<int> labelset;
	//dataset = readData(TRAINNUM, true);
	//labelset = readLabel(TRAINNUM, true);
	//读取数据与标签
	if (!ReadAll(&dataset, &labelset, TRAINNUM, true)) { system("pause"); return -1; };
	//生成随机森林
	RandomForest* randomforest;
	randomforest = new RandomForest(&dataset, &labelset, TREENUM, MAXDEPTH, TRAINNUM, 10, FEATURENUM);
	
	
	system("pause");

	return 0;
}

