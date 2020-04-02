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
		int SampleNumPerTree, int minSampleNumPerNode, int featureNum, int classNum, int RandFeatureNum);
	~Tree();
	/**ѵ����Ԥ��**/
	void train();
	void predict(float* testSet, double** resultProb);
	int predict(float* testSet);
	/*��Ա������ȡ/���ú���*/
	int get_maxdepth() { return this->maxDepth; }
	int get_SampleNumPerTree() { return this->SampleNumPerTree; }
	int get_minSampleNumPerNode() { return this->minSampleNumPerNode; };
	double get_AGini() { return this->AGini; }
	float get_Weight() { return this->Weight; }
	/*���ܺ���*/
	void RootNodeInitial();
	void Punish() { this->Weight *= 1.08; }
	void Punish(float alpha) { this->Weight *= alpha; }
	void Reward() { this->Weight *= 0.88; }
	void Reward(float beta) { this->Weight *= beta; }
	//�������
	vector<Node*> nodeArray;

private:
	int maxDepth;//������ȿ�����������
	int nodeNum;
	int SampleNumPerTree;
	int minSampleNumPerNode;//ÿ�������С������
	int FeatureSelected;
	double AGini;//����Ҷ�ӽ�㰴Ȩ�������Giniϵ��
	float Weight;
};

#endif // !TREE_H
