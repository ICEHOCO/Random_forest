#include "Dataprocess.h"

vector<float> dateRandGenerate(int count)
{
	//��ʼ�����������
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
	//��ʼ�����������
	srand(static_cast<unsigned int>(time(NULL)));
	vector<int> OutLabelSet;
	for (int i = 0; i < count; i++) {
		//OutDataSet.push_back(rand()/float(RAND_MAX));
		OutLabelSet.push_back(static_cast<float>(rand() % 3));
	}
	return OutLabelSet;
}

vector<float> readData(int NumtoRead, bool display)
{
	vector<float> OutDataSet;
	if (NumtoRead > DATAHAVE) { cout << "��ȡ���������У�" << endl; return OutDataSet; }

	for (int i = 0; i < NumtoRead; i++) {
		OutDataSet.push_back(DataSet[i]);
	}

	if (display) {
		cout << "���ζ�ȡ�����У�" << endl;
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
	if (DatatoReadEnd > DATAHAVE) { cout << "��ȡ���������У�" << endl; return OutDataSet; }

	for (int i = DatatoReadStart - 1; i < DatatoReadEnd; i++) {
		OutDataSet.push_back(DataSet[i]);
	}

	if (display) {
		cout << "���ζ�ȡ�����У�" << endl;
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
	if (NumtoRead > LABELHAVE) { cout << "��ȡ���������У�" << endl; return OutLabelSet; }

	for (int i = 0; i < NumtoRead; i++) {
		OutLabelSet.push_back(LabelSet[i]);
	}

	if (display) {
		cout << "���ζ�ȡ��ǩ�У�" << endl;
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
	if (LabeltoReadStart > LABELHAVE) { cout << "��ȡ���������У�" << endl; return OutLabelSet; }

	for (int i = LabeltoReadStart - 1; i < LabeltoReadEnd; i++) {
		OutLabelSet.push_back(LabelSet[i]);
	}

	if (display) {
		cout << "���ζ�ȡ�����У�" << endl;
		for (int i = 0; i < NumtoRead; i++) {
			cout << OutLabelSet[i] << '\t';
		}
		cout << endl;
	}
	return OutLabelSet;
}

bool ReadAll(vector<float>* dataset, vector<int>* labelset, int NumtoRead, bool display)
{
	if (NumtoRead != DATAHAVE || NumtoRead != LABELHAVE) { cout << "�궨�岻һ�£�" << endl; return false; }
	*dataset = readData(DATAHAVE, display);

	*labelset = readLabel(LABELHAVE, display);
	return true;
}