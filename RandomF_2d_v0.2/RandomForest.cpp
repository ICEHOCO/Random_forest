#include "Randomforest.h"
//���ɭ�� ���Ա�����Ķ���

RandomForest::RandomForest(float** dataset, int* labelset, int TreeNum, int maxDepth,
	int SampleNumPerTree, int minSampleNumPerNode, int featureNum, int classNum)
{
	this->TreeNum = TreeNum;
	//��ʼ����   
	this->carTreeArray.resize(this->TreeNum);
	//carTreeArray = new Tree[this->TreeNum * sizeof(Tree)];
	for (int i = 0; i < TreeNum; i++) {
		this->carTreeArray[i] = new Tree(dataset, labelset, maxDepth, SampleNumPerTree, 
											minSampleNumPerNode, featureNum, classNum);
	}
}
RandomForest::~RandomForest()
{
	for (int i = 0; i < this->TreeNum; i++) {
		delete carTreeArray[i];
	}
}
void RandomForest::train()
{
	//���ú�����ʱ���Ѿ�ִ�й���ʼ��!
	//Ŀǰ  ��������  ��  ÿ�����Ľ������  ���Ѿ���ʼ�����
	for (int i = 0; i < this->TreeNum; i++) {
		cout << "��ǰ����ѵ���� " << i << " ����..." << endl;
		carTreeArray[i]->train();
	}
	cout << "ѵ����ɣ�" << endl;
	return;
}