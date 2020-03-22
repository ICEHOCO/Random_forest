#pragma once
#ifndef NODE_H
#define NODE_H

#include "stdafx.h"
#include "Sample.h"

class Node {
public:
	Node() {};
	Node(float** dataset, int* labelset, int classNum, double NGini,
		bool isLeaf, int featureNumSelected);
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
	void calculateInfoGain();
	void releaseIndex();
	//当前结点所持有的样本
	Sample* Nsample;
	double* probArray;

private:
	int classNum;
	bool isLeaf;
	double NGini;
};

#endif // !NODE_H
