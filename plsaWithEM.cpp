#include <iostream>
#include <fstream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
using namespace std;

int M = 2246;
int K = 10;
int N = 10473;
double **ndw;
double **pwz;
double **pzd;
double ***qzdw;
double *mult;

void loadData()
{
	ifstream in("ap.dat");
	char node[10];
	int n, i = 0;
	int wordNum;
	int temp;
	string line;

	if (!in)
	{
		cout << "no such file!" << endl;
		exit(0);
	}

	ndw = new double*[M];
	for (i = 0; i < M; i++)
	{
		ndw[i] = new double[N];
	}

	pzd = new double*[K];
	for (i = 0; i < K; i++)
	{
		pzd[i] = new double[M];
	}

	pwz = new double*[N];
	for (i = 0; i < N; i++)
	{
		pwz[i] = new double[K];
	}

	qzdw = new double**[K];
	for (i = 0; i < K; i++)
	{
		qzdw[i] = new double*[M];
		for (int j = 0; j<M; j++)
			qzdw[i][j] = new double[N];
	}

	i = 0;
	while (in >> n)
	{
		for (int j = 0; j<n; j++)
		{
			in >> node;
			sscanf(node, "%d:%d", &wordNum, &temp);
			ndw[i][wordNum] = temp;
		}
		i++;
	}
}

void initialize()
{
	cout << endl << "pLSA initializing..." << endl;
	int max = 5000;
	double sum1 = 0, sum2 = 0;

	for (int i = 0; i < M; i++)
	{
		for (int k = 0; k < K; k++)
		{
			pzd[k][i] = (rand()%max)+10;
			sum1 = sum1 + pzd[k][i];
		}
		for (int k = 0; k < K; k++)
			pzd[k][i] = pzd[k][i] / sum1;
		sum1 = 0;
	}

	for (int k = 0; k < K; k++)
	{
		for (int j = 0; j < N; j++)
		{
			pwz[j][k] = (rand()%max)+10;
			sum2 = sum2 + pwz[j][k];
		}
		for (int j = 0; j < N; j++)
			pwz[j][k] = pwz[j][k] / sum2;
		sum2 = 0;
	}
	cout << endl << "pLSA initialized" << endl;
}

void calculatePzd()
{
	double sum1 = 0, sum2 = 0;
	cout << "calculatePzd for:" << endl;
	for (int i = 0; i<M; i++)
	{
		for (int k = 0; k<K; k++)
		{
			for (int j = 0; j<N; j++)
			{
				sum1 = sum1 + ndw[i][j] * qzdw[k][i][j];
				sum2 = sum2 + ndw[i][j] * qzdw[k][i][j];
			}
			pzd[k][i] = sum1;
			sum1 = 0;
		}
		for (int k = 0; k<K; k++)
		{
			pzd[k][i] = pzd[k][i] / sum2;
		}
		if (i % 1000 == 0)
		{
			cout << "document" << i << endl;
		}
		sum2 = 0;
	}

}

void calculatePwz()
{
	double sum1 = 0, sum2 = 0;
	cout << "calculatePwz for:" << endl;
	for (int k = 0; k<K; k++)
	{
		for (int j = 0; j<N; j++)
		{
			for (int i = 0; i<M; i++)
			{
				sum1 = sum1 + ndw[i][j] * qzdw[k][i][j];
				sum2 = sum2 + ndw[i][j] * qzdw[k][i][j];
			}
			pwz[j][k] = sum1;
			sum1 = 0;
		}
		for (int j = 0; j<N; j++)
		{
			pwz[j][k] = pwz[j][k] / sum2;
		}
		if (k % 3 == 0)
		{
			cout << "Topic" << k << endl;
		}
		sum2 = 0;
	}
}

void calculateQzdw()
{
	cout << "calculateQzdw for:" << endl;
	double sum = 0;

	for (int i = 0; i<M; i++)
	{
		for (int j = 0; j<N; j++)
		{
			for (int k = 0; k<K; k++)
			{
				sum = sum + pwz[j][k] * pzd[k][i];
			}
			for (int k = 0; k<K; k++)
			{
				qzdw[k][i][j] = pwz[j][k] * pzd[k][i] / sum;
			}
			sum = 0;
		}
		if (i % 1000 == 0)
		{
			cout << "document" << i << endl;
		}
	}
}

void em()
{
	initialize();	
	for (int n = 0; n<100; n++)
	{
		cout << endl << "iteration" << n << endl;
		calculateQzdw();
		calculatePwz();
		calculatePzd();
	}
}

void printResult()
{
	ofstream out("output.txt");
	for (int k = 0; k<K; k++)
	{
		for (int j = 0; j<N; j++)
			out << pwz[j][k] << " ";
		out << endl;
	}
	out.close();
}

int main()
{
	loadData();
	em();
	printResult();
	return 0;
}