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
	//1、读取与数据预处理
	//初始化随机数种子
	srand(static_cast<unsigned int>(time(NULL)));
	bool readFlag = false;
	float** DataSet = ReadData(false, &readFlag, TRAINNUM, FEATURENUM);
	if (readFlag == false) {
		system("pause");
		return -1;
	}
	int* LabelSet = ReadLabel(false,TRAINNUM);
	/*SMOTE:扩充少数样本
	注意：1、某一个类的样本数 至少要比 待扩充样本数 多 1，否则TODO：
	2、Xnew = Xi + 0.38 * γ * (Xi - Xij); Xij为最远的点（欧拉距离）
	*/
	SMOTE_Set p = SMOTE(DataSet, LabelSet, TRAINNUM, CLASSNUM, FEATURENUM);
	DataSet = p.data;
	LabelSet = p.label;
	//扩充后注意更改训练样本数
	int trainNum = p.length;
	OutputDataFile(DataSet);

	//分割集合：训练集-> 训练 + 预预测
	float** Pre_DataSet;
	int* Pre_LabelSet;
	Split_Set q = PreSplit(DataSet, LabelSet, trainNum, CLASSNUM, 3);
	DataSet = q.data;
	LabelSet = q.label;
	trainNum = q.length;
	Pre_DataSet = q.pre_data;
	Pre_LabelSet = q.pre_label;
	int testNum = q.pre_length;
	//2、生成随机森林与预-预测
	const int minSamplePerNode = 10;//必须小于样本总数
	RandomForest* randomforest;
	randomforest = new RandomForest(DataSet, LabelSet, TREENUM, MAXDEPTH, trainNum, minSamplePerNode, FEATURENUM, CLASSNUM, 3);

	//3、训练随机森林
	randomforest->train();

	//3.5、预预测
	randomforest->pre_predict(Pre_DataSet, Pre_LabelSet, testNum, 0.88, 1.05);

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
	//随机森林预测
	testLabel = randomforest->predict(TestDataSet, TESTNUM);
	
	//5、结果分析
	int missCount = 0;
	for (int i = 0; i < TESTNUM; i++) {
		float correct_prob = testLabel[i].prob / randomforest->get_AllWeight();
		cout << "第 " << i << " 个样本的预测结果为:" << testLabel[i].classnum << "\t概率为: " << correct_prob*100 << endl;;
		if (testLabel[i].classnum != answerLabel[i]) {
			missCount++;
		}
	}
	float correct_Ratio = static_cast<double>((TESTNUM - missCount)) / TESTNUM;
	cout << "正确率为:" << correct_Ratio << endl;
	cout << "总权重为:" << randomforest->get_AllWeight() << endl;
	system("pause");
	
	//释放空间，防止内存泄漏
	delete randomforest;
	for (int i = 0; i < TRAINNUM; i++) {
		delete[] DataSet[i];
	}
	delete[] DataSet;
	delete[] LabelSet;
	return 0;
}

