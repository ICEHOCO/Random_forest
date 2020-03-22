// main.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include "Dataprocess.h"	
#include "RandomForest.h"

//训练
#define TRAINNUM    150		//训练样本数
#define FEATURENUM  2		//特征点维数
#define CLASSNUM    3		//分类结果数
//测试
#define TESTNUM		50		//测试样本数
//树的设置
#define TREENUM		100		//树的数量
#define MAXDEPTH	5		//每棵树最大深度

int main()
{
	vector<float> dataset;
	vector<int> labelset;
	//1、读取数据与标签
	if (!ReadAll(&dataset, &labelset, TRAINNUM, false)) { system("pause"); return -1; };
	float** DataSet = ReadData(true);
	int* LabelSet = ReadLabel(false);
	//2、生成随机森林
	RandomForest* randomforest;
	randomforest = new RandomForest(DataSet, LabelSet, TREENUM, MAXDEPTH, TRAINNUM, 10, FEATURENUM, CLASSNUM);
	//3、训练随机森林
	randomforest->train();
	
	system("pause");
	
	//释放空间，防止内存泄漏
	int point_num = TRAINNUM / FEATURENUM;
	for (int i = 0; i < point_num; i++) {
		delete[] DataSet[i];
		DataSet[i] = NULL;
	}
	delete[] LabelSet;
	LabelSet = NULL;

	return 0;
}

