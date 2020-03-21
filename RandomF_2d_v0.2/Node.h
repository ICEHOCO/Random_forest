#pragma once
#ifndef NODE_H
#define NODE_H

#include "stdafx.h"
#include "Sample.h"

class Node {
public:
	Node() {};
	Node(double NGini, bool isLeaf) :NGini(NGini), isLeaf(isLeaf){}
	~Node();
	/*获取成员变量函数*/
	bool get_isLeaf() { return this->isLeaf; }
	double get_NGini() { return this->NGini; }
	/*设置*/
	void set_NGini(double NGini) { this->NGini = NGini; return; }
	void set_isLeaf(bool isLeaf) { this->isLeaf = isLeaf; return; }
	//将当前结点设置为叶子节点
	void set_AsaLeafNode();

	//当前结点所持有的样本
	Sample* Nsample;
private:
	bool isLeaf;
	double NGini;
};

#endif // !NODE_H
