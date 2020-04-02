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

SMOTE_Set SMOTE(float** srcdata, int* srclabel, int length, int classnum, int featurenum)
{
	SMOTE_Set SS;
	//统计每个标签的个数
	int* labelNum = new int[classnum];
	for (int i = 0; i < classnum; i++) { labelNum[i] = 0; }
	for (int i = 0; i < length; i++) { labelNum[srclabel[i]]++; }
	//找出样本数最多的类
	int maxclassNum = 0;
	for (int i = 0; i < classnum; i++) {
		if (maxclassNum < labelNum[i])
			maxclassNum = labelNum[i];
	}
	//开辟新数据存放空间
	length = maxclassNum * classnum;
	float** newdataset = new float*[length];
	int* newlabelset = new int[length];
	//将每个样本数都补充到和最多样本数一样多
	for (int i = 0; i < classnum; i++) {
		//复制旧数据到新数据空间
		int newstart = i * maxclassNum;
		int oldstart = 0;
		for (int j = 0; j < i; j++) {
			oldstart += labelNum[j];
		}
		for (int j = 0; j < labelNum[i]; j++) {	
			newdataset[newstart + j] = srcdata[oldstart + j];
		}
		//扩充
		int needToSynthetic = maxclassNum - labelNum[i];
		if (needToSynthetic <= (labelNum[i]-1) && needToSynthetic != 0) {
			//创建一个表格，存储点与点的欧拉距离
			double** orlaTable = new double*[needToSynthetic+1];
			for (int j = 0; j < needToSynthetic+1; j++) {
				orlaTable[j] = new double[needToSynthetic+1];
				for (int k = 0; k < needToSynthetic+1; k++) {
					orlaTable[j][k] = 0;
				}
			}
			//填充表格
			for (int j = 0; j < needToSynthetic+1; j++) {
				for (int k = j; k < needToSynthetic+1; k++) {
					//对角线0/INF，根据需要最大还是最小选择
					if (k == j){orlaTable[j][k] = 0.0;}
					else {
						//计算点j 与 点k之间的距离
						orlaTable[j][k] = Orladistance(newdataset[newstart+j], newdataset[newstart+k], featurenum);
					}
				}
				//对称复制就行,从右下遍历到左上
				for (int j = needToSynthetic; j >= 0; j--) {
					for (int k = j; k >= 0; k--) {
						if (k == j)orlaTable[j][k] = 0.0;
						else { orlaTable[j][k] = orlaTable[k][j]; }
					}
				}
			}
			//表格已经完成，根据表格找最小值对应的点作为辅助结点
			int cur_labelnum = labelNum[i];
			for (int j = 0; j < needToSynthetic; j++) {
				//找到最小值，然后选择对应的点作为辅助结点
				int sp_index = 0;
				double maxdis = orlaTable[j][0];
				for (int k = 1; k < needToSynthetic+1; k++) {
					if (maxdis < orlaTable[j][k]) {
						maxdis = orlaTable[j][k];
						sp_index = k;
					}
				}
				//扩充
				float* newpoint = new float[featurenum];
				float gama = static_cast<float>(rand()) / RAND_MAX;//γ：0-1
				for (int k = 0; k < featurenum; k++) {
					newpoint[k] = newdataset[newstart+j][k] + 0.38 * gama * (newdataset[newstart+j][k] - newdataset[newstart+sp_index][k]);
				}
				newdataset[newstart + cur_labelnum] = newpoint;
				cur_labelnum++;
			}
			//释放表格空间
			for (int j = 0; j < needToSynthetic; j++) {
				delete[] orlaTable[j];
			}
			delete[] orlaTable;
		}
		else if(needToSynthetic > (labelNum[i] - 1) && needToSynthetic != 0){
			//TODO:原有样本数小于扩充需要的样本数，需要另行操作
			cout<<"原有样本数小于待扩充样本数，尚未实现"<<endl;
			system("pause");
		}
	}
	for (int i = 0; i < classnum; i++) {
		int temp = i*maxclassNum;
		for (int j = 0; j < maxclassNum; j++) {
			newlabelset[temp + j] = i;
		}
	}

	SS.data = newdataset;
	SS.label = newlabelset;
	SS.length = length;
	//没必要删除旧样本数据空间，释放标签空间就行
	delete[] srcdata;
	delete[] srclabel;
	srcdata = NULL;
	srclabel = NULL;
	return SS;
}
//计算欧拉距离
double Orladistance(float* A, float* B, int featurenum)
{
	double result = 0;
	for (int i = 0; i < featurenum; i++) {
		double temp = static_cast<double>(A[i] - B[i]);
		temp *= temp;
		result += temp;
	}
	result = sqrt(result);
	return result;
}

void OutputDataFile(float** dataset)
{
	fstream datafile;
	datafile.open("traindataout.txt", ios::out);
	for (int i = 0; i < 120; i++) {
		for (int j = 0; j < 8; j++) {
			datafile << dataset[i][j] << "\t";
		}
		datafile << endl;
	}
	datafile.close();
	return;
}
//splitNum:每个类中随机取 splitNum 个数据
Split_Set PreSplit(float** srcdata, int* srclabel, int length, int classnum, int splitNum)
{
	Split_Set SS;
	int pre_length = classnum * splitNum;
	int* labelNum = new int[classnum];
	for (int i = 0; i < classnum; i++) {
		labelNum[i] = 0;
	}
	//统计每一类的个数
	for (int i = 0; i < length; i++) {
		labelNum[srclabel[i]]++;
	}
	//不放回随机抽取
	float** dataSet;
	int* labelSet;
	float** Pre_dataSet;
	int* Pre_labelSet;
	dataSet = new float* [length - pre_length];
	labelSet = new int[length - pre_length];
	Pre_dataSet = new float* [pre_length];
	Pre_labelSet = new int[pre_length];
	for (int i = 0; i < classnum; i++) {
		int start = 0;
		for (int j = 0; j < i; j++) { start += labelNum[j]; }
		//随机抽取splitNum个数据放入到Pre_dataSet
		int j = splitNum;
		do {
			int temp = rand() % (labelNum[i] - j + 1);
			if (srcdata[start + temp] != NULL) {
				Pre_dataSet[(i+1)*splitNum - j] = srcdata[start + temp];
				srcdata[start + temp] = NULL;
				j--;
			}
			else {
				Pre_dataSet[(i+1)*splitNum - j] = srcdata[start + labelNum[i] - j];
				srcdata[start + labelNum[i] - j] = NULL;
				j--;
			}
		} while (j > 0);
		//更新 标签集
		for (j = 0; j < labelNum[i] - splitNum; j++) {
			labelSet[start + j - i*splitNum] = i;
		}
		//更新 预预测标签集
		for (j = 0; j < splitNum; j++) {
			Pre_labelSet[i*splitNum + j] = i;
		}
	}
	//更新 数据集
	for (int i = 0, j = 0; i < length; i++) {
		if (srcdata[i] == NULL) { continue; }
		else {
			dataSet[j] = srcdata[i];
			j++;
		}
	}
	SS.length = length - pre_length;
	SS.data = dataSet;
	SS.label = labelSet;

	SS.pre_data = Pre_dataSet;
	SS.pre_label = Pre_labelSet;
	SS.pre_length = pre_length;
	delete[] srcdata;
	delete[] srclabel;
	return SS;
}

/***********************************/


vector<float> dateRandGenerate(int count)
{
	//初始化随机数种子
	//srand(static_cast<unsigned int>(time(NULL)));
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