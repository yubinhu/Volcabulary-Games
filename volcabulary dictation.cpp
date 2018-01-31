#include <iostream>
#include <fstream>
using namespace std;
struct word{
	char English[100];
	char Chinese[100];
	int wrongtimes;
};
int clasify(char a);
void read(word lists[1000]);
int main()
{
	word list[100] = {};
	read(list);
	for (int i = 0; i < 100; i++)
	{
		if (clasify(list[i].Chinese[0]) != 2)
		{
			cout << list[i].Chinese;
		}
	}
	system("pause"); 
	return 0;
}
void read(word lists[1000])
{
	ifstream fin("words.txt");
	char buf = '\0';
	int wordnumbers = 0;
	int i = 0;
	int flag = 0;//0 means English, 1 means Chinese
	while (fin >> buf)
	{
		if (clasify(buf) == 3)
		{
			if (flag == 0)
			{
				lists[wordnumbers].English[i] = buf;
				i++;
				continue;
			}
			if (flag == 1)
			{
				lists[wordnumbers].Chinese[i] = buf;
				i++;
				continue;
			}
		}
		if (clasify(buf) == 0)
		{
			i = 0;
			flag = 1;
			continue;
		}
		if (clasify(buf) == 1)
		{
			i = 0;
			flag = 0;
			wordnumbers++;
		}
	}
}
int clasify(char a)//0 for " ", 1 for enter, 2 for NULL, 3 for others
{
	if (a ==' ')
	{
		return 0;
	}
	if (a == '\n' || a == '\r')
	{
		return 1;
	}
	if (a == '\0')
		return 2;
	return 3;
}