#include "Sample.h"
void Sample::randomSelectData(int N)
{
//����������ѳ�ʼ��
	SetIndex = new int[N];
	for (int i = 0; i < N; i++) {
		SetIndex[i] = rand() % N;
	}
}

void Sample::randomSelectFeatrue(int N)
{
	if (N >= featureNum) {
		FeatureIndex = new int[featureNum];
		for (int i = 0; i < featureNum; i++) {
			FeatureIndex[i] = i;
		}
	}
	else {
		//TODO:���ѡ���ظ���  ����������
	}
}

void Sample::ReadFromFatherSetIndex(int* Indexarr, int start, int count)
{
	SetIndex = new int[count];
	for (int i = 0; i < count; i++) {
		SetIndex[i] = Indexarr[start + i];
	}
	//���½��������
	this->sampleNum = count;
}

Sample::~Sample()
{
	delete[] SetIndex;
	delete[] FeatureIndex;
}