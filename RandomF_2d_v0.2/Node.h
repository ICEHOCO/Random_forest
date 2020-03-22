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
	/*��ȡ��Ա��������*/
	bool get_isLeaf() { return this->isLeaf; }
	double get_NGini() { return this->NGini; }
	int get_classNum() { return this->classNum; }
	/*����*/
	void set_NGini(double NGini) { this->NGini = NGini; return; }
	void set_isLeaf(bool isLeaf) { this->isLeaf = isLeaf; return; }
	/*���ܺ���*/
	void set_AsaLeafNode();
	void calculateInfoGain(vector<Node*>* nodeArray, int curPos);
	void releaseIndex();
	//��ǰ��������е�����
	Sample* Nsample;
	double* probArray;

private:
	int classNum;
	bool isLeaf;
	double NGini;
	int FeatureID;//��ǰ���ѡ���������
	float FeatureValue;	//Ҷ�ӽڵ�������ֵ
};

#endif // !NODE_H
