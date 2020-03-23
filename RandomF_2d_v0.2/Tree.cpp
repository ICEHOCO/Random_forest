#include "Tree.h"

Tree::Tree(float** dataset, int* labelset, int maxDepth, 
	int SampleNumPerTree, int minSampleNumPerNode, int featureNum, int classNum)
{
	//��ֵ
	this->maxDepth = maxDepth;
	this->SampleNumPerTree = SampleNumPerTree;
	this->minSampleNumPerNode = minSampleNumPerNode;
	this->FeatureSelected = featureNum;//�ж���������Ҫ����������
	//��������ʼ��
	nodeNum = static_cast<int>( pow(2.0, maxDepth) - 1.0 );//��� n �� �����������ܽ����
	nodeArray.resize(this->nodeNum);
	//��ʼ�����ڵ�
	nodeArray[0] = new Node(dataset, labelset, classNum, 1.0, false, featureNum);
	this->RootNodeInitial();
}

Tree::~Tree()
{
	for (int i = 0; i < this->nodeNum; i++) {
		delete nodeArray[i];
	}
}

//���ڵ��ʼ��
void Tree::RootNodeInitial()
{
	Node* root = nodeArray[0];
	int classNum = root->get_classNum();
	int* probArray = new int[classNum];
	//���ڵ�������
	root->Nsample->sampleNum = this->SampleNumPerTree;
	//���ڵ㣡 ����ѡ��: �����ݼ��� �зŻصأ���ȡ N ������
	root->Nsample->randomSelectData(this->SampleNumPerTree);
	//��ʼ�� �������� �Լ� ����Giniϵ��
	for (int i = 0; i < classNum; i++) { probArray[i] = 0; }
	//ͳ�Ƹ���
	int* dataIndex = root->Nsample->SetIndex;
	int* labelset = root->Nsample->labelset;
	for (int i = 0; i < this->SampleNumPerTree; i++) {
		probArray[labelset[dataIndex[i]]]++;
	}
	//���������Giniϵ��
	double add_pi_2 = 0;
	for (int i = 0; i < classNum; i++) {
		double p = probArray[i];
		p = p / this->SampleNumPerTree;
		probArray[i] = p;
		add_pi_2 += p * p;
	}
	root->set_NGini(1 - add_pi_2);
	delete[] probArray;

	return;
}

/*
�������ݵ�����£�����ֹ�(��ϣ�)
ѵ��ʱ����ĳ������Giniϵ��Ϊ0ʱ��Ӧ���øý��ΪҶ�ӽ��
*/
void Tree::train()
{
 	for (int i = 0; i < nodeNum; i++) {
		int parentPos = (i - 1) / 2;	//�����λ��
		//�жϸ�����Ƿ����
		if (nodeArray[parentPos] == NULL) { continue; }
		//�жϸ�����Ƿ�ΪҶ��
		if (nodeArray[parentPos]->get_isLeaf()) { continue; }
		//�ж������Ƿ�ΪҶ��
		if ( (i * 2 + 1) >= nodeNum) {
			//ע�⣡��ǰ���������ڸ�����Ҹ���㲻ΪҶ��
			//��ô��ǰ����һ����������  ʵ�� ����
			nodeArray[i]->set_AsaLeafNode();
		}
		else {
			if (nodeArray[i]->Nsample->sampleNum < minSampleNumPerNode) { 
				nodeArray[i]->set_AsaLeafNode();//����ΪҶ�ӽ��
			}
			else {
				//���ѡ�������㣨!��ǰȫѡ!��
				nodeArray[i]->Nsample->randomSelectFeatrue( FeatureSelected );
				//������Ϣ����
				nodeArray[i]->calculateInfoGain(&nodeArray, i);
				//�ͷ� ��ǰ��� ������ռ�õĿռ�
				nodeArray[i]->releaseIndex();
			}
		}
	}
}

//����һ�����������ط����� 0 - 2 ����
void Tree::predict(float* testSet, double** resultProb)
{
	/*�и���㣬�жϽ��ֵ��һֱ�����ߣ����ΪҶ�ӣ���������
	*/
	int curPos = 0;
	int classNum = nodeArray[0]->get_classNum();
	while (!nodeArray[curPos]->get_isLeaf()) {
		if (testSet[nodeArray[curPos]->get_featureId()] <= nodeArray[curPos]->get_featureValue()) {
			//�ߵ�����
			curPos = 2 * curPos + 1;
		}
		else
			curPos = 2 * curPos + 2;//�����ҽ��
	}
	//�ߵ�Ҷ��
	for (int i = 0; i < classNum; i++)
	{
		resultProb[0][i] += nodeArray[curPos]->probArray[i];
	}
	return;
}
