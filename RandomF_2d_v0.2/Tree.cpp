#include "Tree.h"

Tree::Tree(float** dataset, int* labelset, int maxDepth, 
	int SampleNumPerTree, int minSampleNumPerNode, int featureNum, int classNum)
{
	//赋值
	this->maxDepth = maxDepth;
	this->SampleNumPerTree = SampleNumPerTree;
	this->minSampleNumPerNode = minSampleNumPerNode;
	this->FeatureSelected = featureNum;//有多少特征点要多少特征点
	//结点数组初始化
	nodeNum = static_cast<int>( pow(2.0, maxDepth) - 1.0 );//深度 n 的 满二叉树的总结点数
	nodeArray.resize(this->nodeNum);
	//初始化根节点
	nodeArray[0] = new Node(dataset, labelset, classNum, 1.0, false, featureNum);
	this->RootNodeInitial();
}

Tree::~Tree()
{
	for (int i = 0; i < this->nodeNum; i++) {
		delete nodeArray[i];
	}
}

//根节点初始化
void Tree::RootNodeInitial()
{
	Node* root = nodeArray[0];
	int classNum = root->get_classNum();
	int* probArray = new int[classNum];
	//根节点样本数
	root->Nsample->sampleNum = this->SampleNumPerTree;
	//根节点！ 样本选择: 从数据集中 有放回地！抽取 N 个样本
	root->Nsample->randomSelectData(this->SampleNumPerTree);
	//初始化 概率数组 以及 计算Gini系数
	for (int i = 0; i < classNum; i++) { probArray[i] = 0; }
	//统计个数
	int* dataIndex = root->Nsample->SetIndex;
	int* labelset = root->Nsample->labelset;
	for (int i = 0; i < this->SampleNumPerTree; i++) {
		probArray[labelset[dataIndex[i]]]++;
	}
	//计算概率与Gini系数
	double add_pi_2 = 0;
	for (int i = 0; i < classNum; i++) {
		double p = probArray[i];
		p = p / this->SampleNumPerTree;
		probArray[i] = p;
		add_pi_2 += p * p;
	}
	root->set_NGini(1 - add_pi_2);
	delete[] probArray;

	return;
}

/*
线性数据的情况下，会出现过(拟合？)
训练时，当某个结点的Gini系数为0时，应设置该结点为叶子结点
*/
void Tree::train()
{
 	for (int i = 0; i < nodeNum; i++) {
		int parentPos = (i - 1) / 2;	//父结点位置
		//判断父结点是否存在
		if (nodeArray[parentPos] == NULL) { continue; }
		//判断父结点是否为叶子
		if (nodeArray[parentPos]->get_isLeaf()) { continue; }
		//判断自身是否为叶子
		if ( (i * 2 + 1) >= nodeNum) {
			//注意！当前结点如果存在父结点且父结点不为叶子
			//那么当前结点就一定被创建了  实例 ！！
			nodeArray[i]->set_AsaLeafNode();
		}
		else {
			if (nodeArray[i]->Nsample->sampleNum < minSampleNumPerNode) { 
				nodeArray[i]->set_AsaLeafNode();//设置为叶子结点
			}
			else {
				//随机选择特征点（!当前全选!）
				nodeArray[i]->Nsample->randomSelectFeatrue( FeatureSelected );
				//计算信息增益
				nodeArray[i]->calculateInfoGain(&nodeArray, i);
				//释放 当前结点 索引所占用的空间
				nodeArray[i]->releaseIndex();
			}
		}
	}
}

//输入一个向量，返回分类结果 0 - 2 三种
void Tree::predict(float* testSet, double** resultProb)
{
	/*有个结点，判断结点值，一直往下走，结点为叶子，则输出结果
	*/
	int curPos = 0;
	int classNum = nodeArray[0]->get_classNum();
	while (!nodeArray[curPos]->get_isLeaf()) {
		if (testSet[nodeArray[curPos]->get_featureId()] <= nodeArray[curPos]->get_featureValue()) {
			//走到左结点
			curPos = 2 * curPos + 1;
		}
		else
			curPos = 2 * curPos + 2;//否则右结点
	}
	//走到叶子
	for (int i = 0; i < classNum; i++)
	{
		resultProb[0][i] += nodeArray[curPos]->probArray[i];
	}
	return;
}
