#include<iostream>
using namespace std;

int main()
{
	int x,i,j,y;
	cin >> x>>y;
	for (; y >= 0; y--)
	{
		for (i = 0; i < x / 2; i++)
		{
			for (j = 0; j < x; j++)
			{
				if (j == x / 2 - i - 1)
				{
					cout << "/";
				}
				if (j == x / 2 + i-1)
				{
					cout << "\\";
				}
				else
				{
					cout << ".";
				}
			}
			cout << endl;
		}
		for (i = 0; i < x / 2; i++)
		{
			for (j = 0; j < x; j++)
			{
				if (j == x - i - 1)
				{
					cout << "/";
				}
				if (j == i)
				{
					cout << "\\";
				}
				else {
					cout << ".";
				}
			}
			cout << endl;
		}

	}
	
	system("pause");
	return 0;
}
