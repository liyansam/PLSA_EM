#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class pTopicWord
{
public:
	double pwz;
	int wordIndex;
	pTopicWord(double a, int b)
	{
		pwz =a;
		wordIndex =b;
	}
	bool operator < (pTopicWord &a) const
	{
		return this->pwz > a.pwz;
	}
};
int main()
{
	// pTopicWord * a = new pTopicWord(1,2);
	// pTopicWord * b = new pTopicWord(2,2);
	// if(*a<*b)
	// 	cout<<"haha"<<endl;
	ifstream inWords("vocab.txt");
	vector<string> words = new std::vector<string>;
	for( int i = 0; i < 10474; i++ ){
		string str;
		inWords >> str;
		words.push_back( str );
	}


	pTopicWord *a;
	string line;
	ifstream in("output.txt");
	for(int i=0;i<2;i++)
	{
		vector<pTopicWord> vec = new std::vector<pTopicWord>();
		for(int j=0;j<10474;j++)
		{
			double dou;
			in >> dou;
			a = new pTopicWord(dou, j);
			vec.push_back(a);
		}
		sort(vec.begin(), vec.end());
		for( int j = 0; j < 10; j++ ){
			cout << words[vec[j]->wordIndex];	
		}
		
	}
	return 0;
}