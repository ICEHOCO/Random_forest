#pragma once
#ifndef TREE_H
#define TREE_H

#include "stdafx.h"
#include "Node.h"

class Tree {
public:
	/*构造与析构*/
	Tree() {};
	Tree(float** dataset, int* labelset, int maxDepth,
		int SampleNumPerTree, int minSampleNumPerNode, int featureNum, int classNum);
	~Tree();
	/**训练与预测**/
	void train();
	int predict();
	/*成员变量获取函数*/
	int get_maxdepth() { return this->maxDepth; }
	int get_SampleNumPerTree() { return this->SampleNumPerTree; }
	int get_minSampleNumPerNode() { return this->minSampleNumPerNode; };
	double get_AGini() { return this->AGini; }
	/*功能函数*/
	void RootNodeInitial();
	
	//结点数组
	vector<Node*> nodeArray;

private:
	int maxDepth;//根据深度可以算出结点数
	int nodeNum;
	int SampleNumPerTree;
	int minSampleNumPerNode;//每个结点最小样本数
	int FeatureSelected;
	double AGini;//所有叶子结点按权重算出的Gini系数
};

#endif // !TREE_H
