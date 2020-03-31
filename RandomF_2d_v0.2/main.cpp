// main.cpp : 定义控制台应用程序的入口点。

#include "stdafx.h"
#include "Dataprocess.h"	
#include "RandomForest.h"


//训练
#define TRAINNUM    87		//训练样本数
#define FEATURENUM  8		//特征点维数
#define CLASSNUM    3		//分类结果数
//测试
#define TESTNUM		40		//测试样本数
//树的设置
#define TREENUM		100		//树的数量
#define MAXDEPTH	3 		//每棵树最大深度 

int main()
{
	//1、读取数据与标签
	//初始化随机数种子
	srand(static_cast<unsigned int>(time(NULL)));
	bool readFlag = false;
	float** DataSet = ReadData(false, &readFlag, TRAINNUM, FEATURENUM);
	if (readFlag == false) {
		system("pause");
		return -1 ;
	}
	int* LabelSet = ReadLabel(false,TRAINNUM);
	//2、生成随机森林
	const int minSamplePerNode = 10;//必须小于样本总数
	RandomForest* randomforest;
	randomforest = new RandomForest(DataSet, LabelSet, TREENUM, MAXDEPTH, TRAINNUM, minSamplePerNode, FEATURENUM, CLASSNUM, 3);
	//3、训练随机森林
	randomforest->train();

	//4、预测
	float** TestDataSet;//从文件中读取测试数据集
	readFlag = false;
	TestDataSet = ReadTestData(false, &readFlag, TESTNUM, FEATURENUM);
	if (readFlag == false) {
		system("pause");
		return -1;
	}
	Result* testLabel;
	int* answerLabel = ReadTestLabel(false, TESTNUM);
	testLabel = randomforest->predict(TestDataSet, TESTNUM);
	
	int missCount = 0;
	for (int i = 0; i < TESTNUM; i++) {
		cout << "第 " << i << " 个样本的预测结果为:" << testLabel[i].classnum << "\t概率为: " << testLabel[i].prob << endl;;
		if (testLabel[i].classnum != answerLabel[i]) {
			missCount++;
		}
	}
	double correct_Ratio = static_cast<double>(TESTNUM - missCount) / TESTNUM;
	cout << "正确率为:" << correct_Ratio << endl;
	system("pause");
	
	//释放空间，防止内存泄漏
	delete randomforest;
	for (int i = 0; i < TRAINNUM; i++) {
		delete[] DataSet[i];
	}
	delete[] LabelSet;
	return 0;
}

