#include "Sample.h"
void Sample::randomSelect(int N)
{
	//��ʼ�����������
	srand(static_cast<unsigned int>(time(NULL)));
	dataIndex = new int[N];
	for (int i = 0; i < N; i++) {
		dataIndex[i] = rand() % N;
	}
}