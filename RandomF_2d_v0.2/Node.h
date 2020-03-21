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
	/*��ȡ��Ա��������*/
	bool get_isLeaf() { return this->isLeaf; }
	double get_NGini() { return this->NGini; }
	/*����*/
	void set_NGini(double NGini) { this->NGini = NGini; return; }
	void set_isLeaf(bool isLeaf) { this->isLeaf = isLeaf; return; }
	//����ǰ�������ΪҶ�ӽڵ�
	void set_AsaLeafNode();

	//��ǰ��������е�����
	Sample* Nsample;
private:
	bool isLeaf;
	double NGini;
};

#endif // !NODE_H
