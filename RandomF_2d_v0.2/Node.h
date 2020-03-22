#pragma once
#ifndef NODE_H
#define NODE_H

#include "stdafx.h"
#include "Sample.h"

class Node {
public:
	Node() {};
	Node(float** dataset, int* labelset, int classNum, double NGini,
		bool isLeaf, int featureNum);
	~Node();
	/*获取成员变量函数*/
	bool get_isLeaf() { return this->isLeaf; }
	double get_NGini() { return this->NGini; }
	int get_classNum() { return this->classNum; }
	/*设置*/
	void set_NGini(double NGini) { this->NGini = NGini; return; }
	void set_isLeaf(bool isLeaf) { this->isLeaf = isLeaf; return; }
	/*功能函数*/
	void set_AsaLeafNode();
	void calculateInfoGain(vector<Node*>* nodeArray, int curPos);
	void releaseIndex();
	//当前结点所持有的样本
	Sample* Nsample;
	double* probArray;

private:
	int classNum;
	bool isLeaf;
	double NGini;
	int FeatureID;//当前结点选择的特征点
	float FeatureValue;	//叶子节点无特征值
};

#endif // !NODE_H
