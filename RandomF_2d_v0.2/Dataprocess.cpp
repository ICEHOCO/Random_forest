#include "Dataprocess.h"
#include "fstream"

float** ReadData(bool display, bool* success, int numofdata_to_read, int featurenum)
{
	fstream datafile("traindatasetNew.txt");
	float** dataset = new float*[numofdata_to_read];
	for (int i = 0; i < numofdata_to_read; i++) {
		dataset[i] = new float[featurenum];
		for (int j = 0; j < featurenum; j++) {
			if (!datafile.eof())
				datafile >> dataset[i][j];
			else {
				datafile.close();
				cout << "数据读取失败" << endl;
				cout << "位置：" << i << ":" << j+1 << endl;
				*success = false;
				return NULL;
			}
		}
	}
	datafile.close();
	*success = true;
	if (display) {
		cout << "前10个数据集数据:" << endl;
		for (int i = 0; i < 10; i++) {
			cout << "x:" << dataset[i][0] << '\t';
			cout << "y:" << dataset[i][1] << '\t';
			cout << endl;
		}
	}

	return dataset;
}

int* ReadLabel(bool display, int numofdata_to_read)
{
	int* labelset = new int[numofdata_to_read];
	for (int i = 0; i < 21; i++) {
		labelset[i] = 0;
	}
	for (int i = 21; i < 61; i++) {
		labelset[i] = 1;
	}
	for (int i = 61; i < 87; i++) {
		labelset[i] = 2;
	}

	if (display) {
		cout << "标签数据:" << endl;
		for (int i = 0; i < 60; i++) {
			cout << labelset[i] << '\t';
		}
		cout << endl;
	}

	return labelset;
}

float** ReadTestData(bool display, bool* success, int numofdata_to_read, int featurenum)
{
	fstream datafile("testdatasetNew.txt");
	float** dataset = new float* [numofdata_to_read];
	for (int i = 0; i < numofdata_to_read; i++) {
		dataset[i] = new float[featurenum];
		for (int j = 0; j < featurenum; j++) {
			if (!datafile.eof())
				datafile >> dataset[i][j];
			else {
				datafile.close();
				cout << "数据读取失败" << endl;
				cout << "位置：" << i << ":" << j + 1 << endl;
				*success = false;
				return NULL;
			}
		}
	}
	datafile.close();
	*success = true;
	if (display) {
		cout << "前10个数据集数据:" << endl;
		for (int i = 0; i < 5; i++) {
			cout << "x:" << dataset[i][0] << '\t';
			cout << "y:" << dataset[i][1] << '\t';
			cout << endl;
		}
	}
	return dataset;
}
int* ReadTestLabel(bool display, int numofdata_to_read)
{
	int* labelset = new int[numofdata_to_read];
	for (int i = 0; i < 10; i++) {
		labelset[i] = 0;
	}
	for (int i = 10; i < 30; i++) {
		labelset[i] = 1;
	}
	for (int i = 30; i < 40; i++) {
		labelset[i] = 2;
	}

	if (display) {
		cout << "标签数据:" << endl;
		for (int i = 0; i < numofdata_to_read; i++) {
			cout << labelset[i] << '\t';
		}
		cout << endl;
	}

	return labelset;
}



vector<float> dateRandGenerate(int count)
{
	//初始化随机数种子
	srand(static_cast<unsigned int>(time(NULL)));
	vector<float> OutDataSet;
	for (int i = 0; i < count; i++) {
		//OutDataSet.push_back(rand()/float(RAND_MAX));
		OutDataSet.push_back(static_cast<float>(rand() % 10));
	}
	return OutDataSet;
}
vector<int> labelRandGenerate(int count)
{
	//初始化随机数种子
	srand(static_cast<unsigned int>(time(NULL)));
	vector<int> OutLabelSet;
	for (int i = 0; i < count; i++) {
		//OutDataSet.push_back(rand()/float(RAND_MAX));
		OutLabelSet.push_back(static_cast<int>(rand() % 3));
	}
	return OutLabelSet;
}

vector<float> readData(int NumtoRead, bool display)
{
	vector<float> OutDataSet;
	if (NumtoRead > DATAHAVE) { cout << "读取量超出现有！" << endl; return OutDataSet; }

	for (int i = 0; i < NumtoRead; i++) {
		OutDataSet.push_back(DataSet[i]);
	}

	if (display) {
		cout << "本次读取数据有：" << endl;
		for (int i = 0; i < NumtoRead; i++) {
			cout << OutDataSet[i] << '\t';
		}
		cout << endl;
	}
	return OutDataSet;
}

vector<float> readData(int DatatoReadStart, int NumtoRead, bool display)
{
	vector<float> OutDataSet;
	int DatatoReadEnd = DatatoReadStart - 1 + NumtoRead;
	if (DatatoReadEnd > DATAHAVE) { cout << "读取量超出现有！" << endl; return OutDataSet; }

	for (int i = DatatoReadStart - 1; i < DatatoReadEnd; i++) {
		OutDataSet.push_back(DataSet[i]);
	}

	if (display) {
		cout << "本次读取数据有：" << endl;
		for (int i = 0; i < NumtoRead; i++) {
			cout << OutDataSet[i] << '\t';
		}
		cout << endl;
	}
	return OutDataSet;
}

vector<int> readLabel(int NumtoRead, bool display)
{
	vector<int> OutLabelSet;
	if (NumtoRead > LABELHAVE) { cout << "读取量超出现有！" << endl; return OutLabelSet; }

	for (int i = 0; i < NumtoRead; i++) {
		OutLabelSet.push_back(LabelSet[i]);
	}

	if (display) {
		cout << "本次读取标签有：" << endl;
		for (int i = 0; i < NumtoRead; i++) {
			cout << OutLabelSet[i] << '\t';
		}
		cout << endl;
	}
	return OutLabelSet;
}
vector<int> readLabel(int LabeltoReadStart, int NumtoRead, bool display)
{
	vector<int> OutLabelSet;
	int LabeltoReadEnd = LabeltoReadStart - 1 + NumtoRead;
	if (LabeltoReadStart > LABELHAVE) { cout << "读取量超出现有！" << endl; return OutLabelSet; }

	for (int i = LabeltoReadStart - 1; i < LabeltoReadEnd; i++) {
		OutLabelSet.push_back(LabelSet[i]);
	}

	if (display) {
		cout << "本次读取数据有：" << endl;
		for (int i = 0; i < NumtoRead; i++) {
			cout << OutLabelSet[i] << '\t';
		}
		cout << endl;
	}
	return OutLabelSet;
}

bool ReadAll(vector<float>* dataset, vector<int>* labelset, int NumtoRead, bool display)
{
	if (NumtoRead != DATAHAVE || NumtoRead != LABELHAVE) { cout << "宏定义不一致！" << endl; return false; }
	*dataset = readData(DATAHAVE, display);

	*labelset = readLabel(LABELHAVE, display);
	return true;
}