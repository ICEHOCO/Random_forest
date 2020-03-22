#include "Node.h"

Node::Node(float** dataset, int* labelset, int classNum, double NGini, 
	bool isLeaf, int featureNumSelected)
{
	//让节点获取总样本, 但未获得样本索引！！
	this->Nsample = new Sample(dataset, labelset, featureNumSelected);
	this->NGini = NGini;
	this->isLeaf = isLeaf;
	this->classNum = classNum;
	this->probArray = new double[classNum];
}

void Node::calculateInfoGain()
{
	//1、选择 最优分割点  2、创造 孩子结点 实例
	int sampleNum = Nsample->sampleNum;
	//1、声明全局最优变量
	int featureID = Nsample->FeatureIndex[0];
	int maxInfoGain = -1;	//最大信息增益 = NGini - LSnum * LGini - RSnum * RGini 
	double LGini = 1;	//左孩子Gini系数
	double* LprobArray = new double[classNum];	//左孩子的概率数组:统计个数，计算概率，计算Gini
	vector<int> LSetIndex;		//左孩子有的样本索引
	double RGini = 1;
	double* RprobArray = new double[classNum];
	vector<int> RSetIndex;
	//2、循环特征值确定分割点
	for (int i = 0; i < Nsample->featureNum; i++) {
		//2.1、声明当前特征下最优变量
		int F_maxInfoGain = -1;	//最大信息增益 = NGini - LSnum * LGini - RSnum * RGini 
		double F_LGini = 1.0;	//左孩子Gini系数
		double* F_LprobArray = new double[classNum];	//左孩子的概率数组:统计个数，计算概率，计算Gini
		double F_RGini = 1.0;
		double* F_RprobArray = new double[classNum];
		//初始化
		for (int j = 0; j < classNum; j++) {
			F_LprobArray[j] = 0;
			F_RprobArray[j] = 0;
		}
		//2.1.1、根据每个样本当前特征值大小进行排序，最终排序的是索引的结果
		//q_sort(Sample->SetIndex, Compare); 
		/*compare:
			if(Sample->dataSet[SetIndex[ a ]][ i ] < Sample->dataSet[SetIndex[ b ]][ i ])
				return -1;
			else if( a == b )return 0;
			else
				return 1;
		*/
		//排序结束后，Sample->SetIndex 是排序好的，根据当前特征点的值
		//让右孩子结点拿到所有排序好的索引
		const int* labelset = Nsample->labelset;
		int* SetIndex = Nsample->SetIndex;
		for (int j = 0; j < sampleNum; j++) {
			F_RprobArray[ labelset[SetIndex[j]] ]++;
		}
		//2.2、获取当前特征值下， 最优分隔点 及 相关信息
		//不考虑所有样本在一个孩子结点下的情况， 因为那时信息增益为 0 
		//故左样本数：1 - （N-1）  右样本数： （N-1）- 1
		//差一个结点分类数据，还有
		//2.2.2、循环取最优
		for(int j = 0; j < sampleNum - 1; j++){
			int LWeight = j + 1;
			int RWeight = sampleNum - j - 1;
			//先拿样本到左边， 再计算
			F_LprobArray[labelset[SetIndex[j]]]++;
			F_RprobArray[labelset[SetIndex[j]]]--;
			//左孩子Gini
			double add_pi_2 = 0;
			for (int k = 0; k < classNum; k++) {
				double pi = (F_LprobArray[i] / LWeight);
				add_pi_2 += pi * pi;
			}
			F_LGini = 1 - add_pi_2;
			//右孩子Gini
			add_pi_2 = 0;

			for (int k = 0; k < classNum; k++) {
				double pi = (F_RprobArray[i] / RWeight);
				add_pi_2 += pi * pi;
			}
			F_RGini = 1 - add_pi_2;
			//计算信息增益
			double curInfoGain = NGini * sampleNum - LWeight * F_LGini - RWeight * F_RGini;
			//判断对于当前特征点来说是否是最优的分割
			if (curInfoGain > F_maxInfoGain) {
				//更新相关信息
			}
		};
		//2.3、并且与全局比较 最优
		if (F_maxInfoGain > maxInfoGain) {
			//获取一个最优， 更新最优信息
		}
	}
	//3、构造孩子结点实例，注意变量的初始化
}

void Node::releaseIndex()
{
	//释放当前结点索引所占用的空间
	//数据集索引  以及  特征点索引
	delete[] Nsample->SetIndex;
	delete[] Nsample->FeatureIndex;
	Nsample->SetIndex = NULL;
	Nsample->FeatureIndex = NULL;
}

void Node::set_AsaLeafNode()
{

}

Node::~Node()
{
	delete Nsample;
	delete[] probArray;
}