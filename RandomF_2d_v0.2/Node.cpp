#include "Node.h"

Node::Node(float** dataset, int* labelset, int classNum, double NGini, 
	bool isLeaf, int featureNumSelected)
{
	//�ýڵ��ȡ������, ��δ���������������
	this->Nsample = new Sample(dataset, labelset, featureNumSelected);
	this->NGini = NGini;
	this->isLeaf = isLeaf;
	this->classNum = classNum;
	this->probArray = new double[classNum];
}

void Node::calculateInfoGain()
{
	//1��ѡ�� ���ŷָ��  2������ ���ӽ�� ʵ��
	int sampleNum = Nsample->sampleNum;
	//1������ȫ�����ű���
	int featureID = Nsample->FeatureIndex[0];
	int maxInfoGain = -1;	//�����Ϣ���� = NGini - LSnum * LGini - RSnum * RGini 
	double LGini = 1;	//����Giniϵ��
	double* LprobArray = new double[classNum];	//���ӵĸ�������:ͳ�Ƹ�����������ʣ�����Gini
	vector<int> LSetIndex;		//�����е���������
	double RGini = 1;
	double* RprobArray = new double[classNum];
	vector<int> RSetIndex;
	//2��ѭ������ֵȷ���ָ��
	for (int i = 0; i < Nsample->featureNum; i++) {
		//2.1��������ǰ���������ű���
		int F_maxInfoGain = -1;	//�����Ϣ���� = NGini - LSnum * LGini - RSnum * RGini 
		double F_LGini = 1.0;	//����Giniϵ��
		double* F_LprobArray = new double[classNum];	//���ӵĸ�������:ͳ�Ƹ�����������ʣ�����Gini
		double F_RGini = 1.0;
		double* F_RprobArray = new double[classNum];
		//��ʼ��
		for (int j = 0; j < classNum; j++) {
			F_LprobArray[j] = 0;
			F_RprobArray[j] = 0;
		}
		//2.1.1������ÿ��������ǰ����ֵ��С������������������������Ľ��
		//q_sort(Sample->SetIndex, Compare); 
		/*compare:
			if(Sample->dataSet[SetIndex[ a ]][ i ] < Sample->dataSet[SetIndex[ b ]][ i ])
				return -1;
			else if( a == b )return 0;
			else
				return 1;
		*/
		//���������Sample->SetIndex ������õģ����ݵ�ǰ�������ֵ
		//���Һ��ӽ���õ���������õ�����
		const int* labelset = Nsample->labelset;
		int* SetIndex = Nsample->SetIndex;
		for (int j = 0; j < sampleNum; j++) {
			F_RprobArray[ labelset[SetIndex[j]] ]++;
		}
		//2.2����ȡ��ǰ����ֵ�£� ���ŷָ��� �� �����Ϣ
		//����������������һ�����ӽ���µ������ ��Ϊ��ʱ��Ϣ����Ϊ 0 
		//������������1 - ��N-1��  ���������� ��N-1��- 1
		//��һ�����������ݣ�����
		//2.2.2��ѭ��ȡ����
		for(int j = 0; j < sampleNum - 1; j++){
			int LWeight = j + 1;
			int RWeight = sampleNum - j - 1;
			//������������ߣ� �ټ���
			F_LprobArray[labelset[SetIndex[j]]]++;
			F_RprobArray[labelset[SetIndex[j]]]--;
			//����Gini
			double add_pi_2 = 0;
			for (int k = 0; k < classNum; k++) {
				double pi = (F_LprobArray[i] / LWeight);
				add_pi_2 += pi * pi;
			}
			F_LGini = 1 - add_pi_2;
			//�Һ���Gini
			add_pi_2 = 0;

			for (int k = 0; k < classNum; k++) {
				double pi = (F_RprobArray[i] / RWeight);
				add_pi_2 += pi * pi;
			}
			F_RGini = 1 - add_pi_2;
			//������Ϣ����
			double curInfoGain = NGini * sampleNum - LWeight * F_LGini - RWeight * F_RGini;
			//�ж϶��ڵ�ǰ��������˵�Ƿ������ŵķָ�
			if (curInfoGain > F_maxInfoGain) {
				//���������Ϣ
			}
		};
		//2.3��������ȫ�ֱȽ� ����
		if (F_maxInfoGain > maxInfoGain) {
			//��ȡһ�����ţ� ����������Ϣ
		}
	}
	//3�����캢�ӽ��ʵ����ע������ĳ�ʼ��
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

void Node::set_AsaLeafNode()
{

}

Node::~Node()
{
	delete Nsample;
	delete[] probArray;
}