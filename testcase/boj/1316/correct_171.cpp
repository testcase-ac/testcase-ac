#include<iostream>
#include<string>
using namespace std;

int main()
{
	string str;
	int num;
	cin >> num;
	int answer = num;
	for (int i = 0; i < num; i++)
	{
		cin >> str;
		int length = str.length();
		for (int j = 0; j < length; j++)
		{
			char a = str[j];
			string::size_type next = str.find_first_not_of(a, j);
			string::size_type check = str.find(a, next);
			if (a == str[check])
			{
				answer--;
				break;
			}
		}
	}
	cout << answer;
}