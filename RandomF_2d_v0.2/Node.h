#pragma once
#ifndef NODE_H
#define NODE_H

#include "stdafx.h"
#include "Sample.h"

struct Pair {
	float data;
	int dataIndex;
};

int compare(const void* a, const void* b);

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
	int get_featureId() { return this->FeatureID; }
	float get_featureValue() { return this->FeatureValue; }
	/*����*/
	void set_NGini(double NGini) { this->NGini = NGini; return; }
	void set_isLeaf(bool isLeaf) { this->isLeaf = isLeaf; return; }
	/*���ܺ���*/
	void set_AsaLeafNode();
	void calculateInfoGain(vector<Node*>* nodeArray, int curPos);
	void releaseIndex();
	void sortByFeatureId(int FeatureId);
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
