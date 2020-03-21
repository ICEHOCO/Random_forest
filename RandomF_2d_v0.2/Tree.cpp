#include "Tree.h"

Tree::Tree(vector<float>* dataset, vector<int>* labelset, int maxDepth, 
	int SampleNumPerTree, int minSampleNumPerNode, int featureNumSelected)
{
	//赋值
	this->maxDepth = maxDepth;
	this->SampleNumPerTree = SampleNumPerTree;
	this->minSampleNumPerNode = minSampleNumPerNode;
	//结点数组初始化
	nodeNum = static_cast<int>( pow(2.0, maxDepth) - 1.0 );//深度 n 的 满二叉树的总结点数
	nodeArray.resize(this->nodeNum);
	for (int i = 0; i < nodeNum; i++) {
		nodeArray[i] = new Node(1.0, false);
	}
	//根节点！ 样本选择: 从数据集中 有放回地！抽取 N 个样本
	nodeArray[0]->Nsample = new Sample(dataset, labelset, featureNumSelected);//让根节点获取总样本
	nodeArray[0]->Nsample->randomSelect(SampleNumPerTree);
}