#include <stdio.h>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

int res = 0;
int arr[3000];
int temp[3000];

void f(int s, int e)
{
	if(s == e) return;

	int m = (s + e) / 2;
	f(s, m);
	f(m + 1, e);

	int l = s, r = m + 1;
	for(int i = 0; i <= e - s; ++i)
	{
		if(e < r || (l <= m && arr[l] < arr[r]))
		{
			res += e - r + 1;
			temp[i] = arr[l++];
		}
		else
		{
			temp[i] = arr[r++];
		}
	}

	for(int i = s; i <= e; ++i)
	{
		arr[i] = temp[i - s];
	}
}

int main()
{
	map<string, int> M;
	int idx = 0;

	int n;
	scanf("%d", &n);

	for(int i = 0; i < n; ++i)
	{
		char buf[20];
		scanf("%s", buf);
		M[buf] = idx++;
	}

	for(int i = 0; i < n; ++i)
	{
		char buf[20];
		scanf("%s", buf);
		arr[i] = M[buf];
	}

	f(0, n - 1);
	printf("%d/%d\n", res, n * (n - 1) / 2);

	return 0;
}
