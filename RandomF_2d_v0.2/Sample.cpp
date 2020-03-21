#include "Sample.h"
void Sample::randomSelect(int N)
{
	//初始化随机数种子
	srand(static_cast<unsigned int>(time(NULL)));
	dataIndex = new int[N];
	for (int i = 0; i < N; i++) {
		dataIndex[i] = rand() % N;
	}
}