#include "Node.h"

Node::Node(float** dataset, int* labelset, int classNum, double NGini, 
	bool isLeaf, int featureNum)
{
	//�ýڵ��ȡ������, ��δ���������������
	this->Nsample = new Sample(dataset, labelset, featureNum);
	this->NGini = NGini;
	this->isLeaf = isLeaf;
	this->classNum = classNum;
	//this->probArray = new double[classNum];
}

void Node::calculateInfoGain(vector<Node*>* nodeArray, int curPos)
{
	//1��ѡ�� ���ŷָ��  2������ ���ӽ�� ʵ��
	int sampleNum = Nsample->sampleNum;
	float** dataset = Nsample->dataset;
	int* labelset = Nsample->labelset;
	int* SetIndex = Nsample->SetIndex;
	int* FeatureIndex = Nsample->FeatureIndex;
	int featureNum = Nsample->featureNum;
	//1������ȫ�����ű���
	FeatureID = FeatureIndex[0];
	FeatureValue = 0;
	//
	int splitPoint = 0;
	int maxInfoGain = -1;	//�����Ϣ���� = NGini - LSnum * LGini - RSnum * RGini 
	double LGini = 1;	//����Giniϵ��
	double RGini = 1;
	//2��ѭ������ֵȷ���ָ��
	//2.1��������ǰ���������ű���
	int F_splitPoint = 0;
	int F_featureID = 0;
	float F_featureValue = 0;
	int F_maxInfoGain = -1;	//�����Ϣ���� = NGini - LSnum * LGini - RSnum * RGini 
	double F_LGini = 1.0;	//����Giniϵ��
	double F_RGini = 1.0;
	//ѭ��
	double* lprobarray = new double[classNum];
	double* rprobarray = new double[classNum];

	for (int i = 0; i < featureNum; i++) {
		//��ʼ��
		for (int j = 0; j < classNum; j++) {
			lprobarray[j] = 0.0;
			rprobarray[j] = 0.0;
		}
		//2.1.1������ÿ��������ǰ����ֵ��С������������������������Ľ��
		sortByFeatureId(FeatureIndex[i]);
		//���Һ��ӽ���õ���������õ�����
		for (int j = 0; j < sampleNum; j++) {
			rprobarray[labelset[SetIndex[j]]]++;
		}
		//2.2����ȡ��ǰ����ֵ�£� ���ŷָ��� �� �����Ϣ
		//����������������һ�����ӽ���µ������ ��Ϊ��ʱ��Ϣ����Ϊ 0 
		//������������1 - ��N-1��  ���������� ��N-1��- 1
		//2.2.2��ѭ��ȡ����
		for(int j = 0; j < sampleNum - 1; j++){
			int LWeight = j + 1;
			int RWeight = sampleNum - j - 1;
			//������������ߣ� �ټ���
			lprobarray[labelset[SetIndex[j]]]++;
			rprobarray[labelset[SetIndex[j]]]--;
			//����Gini
			double add_pi_2 = 0;
			for (int k = 0; k < classNum; k++) {
				double pi = (lprobarray[k] / LWeight);
				add_pi_2 += pi * pi;
			}
			double lgini = 1 - add_pi_2;
			//�Һ���Gini
			add_pi_2 = 0;
			for (int k = 0; k < classNum; k++) {
				double pi = (rprobarray[k] / RWeight);
				add_pi_2 += pi * pi;
			}
			double rgini = 1 - add_pi_2;
			//������Ϣ����
			double curInfoGain = NGini * sampleNum - LWeight * lgini - RWeight * rgini;
			//�ж϶��ڵ�ǰ��������˵�Ƿ������ŵķָ�
			if (curInfoGain > F_maxInfoGain) {
				//���������Ϣ
				F_maxInfoGain = curInfoGain;
				F_splitPoint = j;//���ѵ�
				F_featureID = Nsample->FeatureIndex[ i ];
				F_featureValue = Nsample->dataset[ SetIndex[j] ][i];
				F_LGini = lgini;
				F_RGini = rgini;
			}
		}
		//2.3��������ȫ�ֱȽ� ����
		if (F_maxInfoGain > maxInfoGain) {
			//��ȡһ�����ţ� ����������Ϣ
			maxInfoGain = F_maxInfoGain;
			splitPoint = F_splitPoint;
			FeatureID = F_featureID;
			FeatureValue = F_featureValue;
			LGini = F_LGini;
			RGini = F_RGini;
		}
	}

	delete[] lprobarray;
	delete[] rprobarray;
	//3�����캢�ӽ��ʵ����ע������ĳ�ʼ��
	//q_sort(Nsample->SetIndex, Compare); featureIndex[FeatureID]
	sortByFeatureId(FeatureID);
	nodeArray[0][curPos*2+1] = new Node(dataset, labelset, classNum, LGini, false, featureNum);//��
	nodeArray[0][curPos*2+1]->Nsample->ReadFromFatherSetIndex(SetIndex, 0, splitPoint + 1);
	nodeArray[0][curPos*2+2] = new Node(dataset, labelset, classNum, RGini, false, featureNum);//��
	nodeArray[0][curPos*2+2]->Nsample->ReadFromFatherSetIndex(SetIndex, splitPoint + 1, sampleNum-splitPoint-1);
}

void Node::releaseIndex()
{
	//�ͷŵ�ǰ���������ռ�õĿռ�
	//���ݼ�����  �Լ�  ����������
	delete[] Nsample->SetIndex;
	delete[] Nsample->FeatureIndex;
	Nsample->SetIndex = NULL;
	Nsample->FeatureIndex = NULL;
}

void Node::sortByFeatureId(int FeatureId)
{
	int sampleNum = Nsample->sampleNum;
	int* SetIndex = Nsample->SetIndex;
	Pair* pair = new Pair[sampleNum];
	for (int i = 0; i < sampleNum; i++) {
		pair[i].dataIndex = SetIndex[i];
		pair[i].data = Nsample->dataset[SetIndex[i]][Nsample->FeatureIndex[FeatureId]];
	}
	qsort(pair, sampleNum, sizeof(Pair),compare);
	for (int i = 0; i < sampleNum; i++) {
		SetIndex[i] = pair[i].dataIndex;
	}
	delete[] pair;
}

int compare(const void* a, const void* b) 
{
	if ((*(Pair*)a).data > (*(Pair*)b).data) return 1;
	else if ((*(Pair*)a).data == (*(Pair*)b).data) return 0;
	else return -1;
}

void Node::set_AsaLeafNode()
{
	isLeaf = true;
	int* SetIndex = Nsample->SetIndex;
	probArray = new double[classNum];
	//��ʼ��
	for (int i = 0; i < classNum; i++) { probArray[i] = 0; }
	//ͳ�Ƹ���
	for (int i = 0; i < Nsample->sampleNum; i++) {
		probArray[Nsample->labelset[SetIndex[i]]]++;
	}
	//�������
	for (int i = 0; i < classNum; i++) {
		probArray[i] /= Nsample->sampleNum;
	}
	//��������ֵ��Ҷ�ӽ�㵱�������壬������ʼ���á�
	FeatureValue = -1;
	FeatureID = -1;
}

Node::~Node()
{
	delete Nsample;
	delete[] probArray;
}