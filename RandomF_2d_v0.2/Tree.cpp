#include "Tree.h"

Tree::Tree(vector<float>* dataset, vector<int>* labelset, int maxDepth, 
	int SampleNumPerTree, int minSampleNumPerNode, int featureNumSelected)
{
	//��ֵ
	this->maxDepth = maxDepth;
	this->SampleNumPerTree = SampleNumPerTree;
	this->minSampleNumPerNode = minSampleNumPerNode;
	//��������ʼ��
	nodeNum = static_cast<int>( pow(2.0, maxDepth) - 1.0 );//��� n �� �����������ܽ����
	nodeArray.resize(this->nodeNum);
	for (int i = 0; i < nodeNum; i++) {
		nodeArray[i] = new Node(1.0, false);
	}
	//���ڵ㣡 ����ѡ��: �����ݼ��� �зŻصأ���ȡ N ������
	nodeArray[0]->Nsample = new Sample(dataset, labelset, featureNumSelected);//�ø��ڵ��ȡ������
	nodeArray[0]->Nsample->randomSelect(SampleNumPerTree);
}