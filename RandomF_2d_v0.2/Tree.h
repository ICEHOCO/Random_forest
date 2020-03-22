#pragma once
#ifndef TREE_H
#define TREE_H

#include "stdafx.h"
#include "Node.h"

class Tree {
public:
	/*����������*/
	Tree() {};
	Tree(float** dataset, int* labelset, int maxDepth,
		int SampleNumPerTree, int minSampleNumPerNode, int featureNum, int classNum);
	~Tree();
	/**ѵ����Ԥ��**/
	void train();
	int predict();
	/*��Ա������ȡ����*/
	int get_maxdepth() { return this->maxDepth; }
	int get_SampleNumPerTree() { return this->SampleNumPerTree; }
	int get_minSampleNumPerNode() { return this->minSampleNumPerNode; };
	double get_AGini() { return this->AGini; }
	/*���ܺ���*/
	void RootNodeInitial();
	
	//�������
	vector<Node*> nodeArray;

private:
	int maxDepth;//������ȿ�����������
	int nodeNum;
	int SampleNumPerTree;
	int minSampleNumPerNode;//ÿ�������С������
	int FeatureSelected;
	double AGini;//����Ҷ�ӽ�㰴Ȩ�������Giniϵ��
};

#endif // !TREE_H
