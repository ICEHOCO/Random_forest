#include "Node.h"

Node::Node(float** dataset, int* labelset, int classNum, double NGini, 
	bool isLeaf, int featureNum)
{
	//让节点获取总样本, 但未获得样本索引！！
	this->Nsample = new Sample(dataset, labelset, featureNum);
	this->NGini = NGini;
	this->isLeaf = isLeaf;
	this->classNum = classNum;
	//this->probArray = new double[classNum];
}

void Node::calculateInfoGain(vector<Node*>* nodeArray, int curPos)
{
	//1、选择 最优分割点  2、创造 孩子结点 实例
	int sampleNum = Nsample->sampleNum;
	float** dataset = Nsample->dataset;
	int* labelset = Nsample->labelset;
	int* SetIndex = Nsample->SetIndex;
	int* FeatureIndex = Nsample->FeatureIndex;
	int featureNum = Nsample->featureNum;
	//1、声明全局最优变量
	FeatureID = FeatureIndex[0];
	FeatureValue = 0;
	//
	int splitPoint = 0;
	int maxInfoGain = -1;	//最大信息增益 = NGini - LSnum * LGini - RSnum * RGini 
	double LGini = 1;	//左孩子Gini系数
	double RGini = 1;
	//2、循环特征值确定分割点
	//2.1、声明当前特征下最优变量
	int F_splitPoint = 0;
	int F_featureID = 0;
	float F_featureValue = 0;
	int F_maxInfoGain = -1;	//最大信息增益 = NGini - LSnum * LGini - RSnum * RGini 
	double F_LGini = 1.0;	//左孩子Gini系数
	double F_RGini = 1.0;
	//循环
	double* lprobarray = new double[classNum];
	double* rprobarray = new double[classNum];

	for (int i = 0; i < featureNum; i++) {
		//初始化
		for (int j = 0; j < classNum; j++) {
			lprobarray[j] = 0.0;
			rprobarray[j] = 0.0;
		}
		//2.1.1、根据每个样本当前特征值大小进行排序，最终排序的是索引的结果
		sortByFeatureId(FeatureIndex[i]);
		//让右孩子结点拿到所有排序好的索引
		for (int j = 0; j < sampleNum; j++) {
			rprobarray[labelset[SetIndex[j]]]++;
		}
		//2.2、获取当前特征值下， 最优分隔点 及 相关信息
		//不考虑所有样本在一个孩子结点下的情况， 因为那时信息增益为 0 
		//故左样本数：1 - （N-1）  右样本数： （N-1）- 1
		//2.2.2、循环取最优
		for(int j = 0; j < sampleNum - 1; j++){
			int LWeight = j + 1;
			int RWeight = sampleNum - j - 1;
			//先拿样本到左边， 再计算
			lprobarray[labelset[SetIndex[j]]]++;
			rprobarray[labelset[SetIndex[j]]]--;
			//左孩子Gini
			double add_pi_2 = 0;
			for (int k = 0; k < classNum; k++) {
				double pi = (lprobarray[k] / LWeight);
				add_pi_2 += pi * pi;
			}
			double lgini = 1 - add_pi_2;
			//右孩子Gini
			add_pi_2 = 0;
			for (int k = 0; k < classNum; k++) {
				double pi = (rprobarray[k] / RWeight);
				add_pi_2 += pi * pi;
			}
			double rgini = 1 - add_pi_2;
			//计算信息增益
			double curInfoGain = NGini * sampleNum - LWeight * lgini - RWeight * rgini;
			//判断对于当前特征点来说是否是最优的分割
			if (curInfoGain > F_maxInfoGain) {
				//更新相关信息
				F_maxInfoGain = curInfoGain;
				F_splitPoint = j;//分裂点
				F_featureID = Nsample->FeatureIndex[ i ];
				F_featureValue = Nsample->dataset[ SetIndex[j] ][i];
				F_LGini = lgini;
				F_RGini = rgini;
			}
		}
		//2.3、并且与全局比较 最优
		if (F_maxInfoGain > maxInfoGain) {
			//获取一个最优， 更新最优信息
			maxInfoGain = F_maxInfoGain;
			splitPoint = F_splitPoint;
			FeatureID = F_featureID;
			FeatureValue = F_featureValue;
			LGini = F_LGini;
			RGini = F_RGini;
		}
	}

	delete[] lprobarray;
	delete[] rprobarray;
	//3、构造孩子结点实例，注意变量的初始化
	//q_sort(Nsample->SetIndex, Compare); featureIndex[FeatureID]
	sortByFeatureId(FeatureID);
	nodeArray[0][curPos*2+1] = new Node(dataset, labelset, classNum, LGini, false, featureNum);//左
	nodeArray[0][curPos*2+1]->Nsample->ReadFromFatherSetIndex(SetIndex, 0, splitPoint + 1);
	nodeArray[0][curPos*2+2] = new Node(dataset, labelset, classNum, RGini, false, featureNum);//右
	nodeArray[0][curPos*2+2]->Nsample->ReadFromFatherSetIndex(SetIndex, splitPoint + 1, sampleNum-splitPoint-1);
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

void Node::sortByFeatureId(int FeatureId)
{
	int sampleNum = Nsample->sampleNum;
	int* SetIndex = Nsample->SetIndex;
	Pair* pair = new Pair[sampleNum];
	for (int i = 0; i < sampleNum; i++) {
		pair[i].dataIndex = SetIndex[i];
		pair[i].data = Nsample->dataset[SetIndex[i]][Nsample->FeatureIndex[FeatureId]];
	}
	qsort(pair, sampleNum, sizeof(Pair),compare);
	for (int i = 0; i < sampleNum; i++) {
		SetIndex[i] = pair[i].dataIndex;
	}
	delete[] pair;
}

int compare(const void* a, const void* b) 
{
	if ((*(Pair*)a).data > (*(Pair*)b).data) return 1;
	else if ((*(Pair*)a).data == (*(Pair*)b).data) return 0;
	else return -1;
}

void Node::set_AsaLeafNode()
{
	isLeaf = true;
	int* SetIndex = Nsample->SetIndex;
	probArray = new double[classNum];
	//初始化
	for (int i = 0; i < classNum; i++) { probArray[i] = 0; }
	//统计个数
	for (int i = 0; i < Nsample->sampleNum; i++) {
		probArray[Nsample->labelset[SetIndex[i]]]++;
	}
	//计算概率
	for (int i = 0; i < classNum; i++) {
		probArray[i] /= Nsample->sampleNum;
	}
	//以下两数值在叶子结点当中无意义，仅作初始化用。
	FeatureValue = -1;
	FeatureID = -1;
}

Node::~Node()
{
	delete Nsample;
	delete[] probArray;
}