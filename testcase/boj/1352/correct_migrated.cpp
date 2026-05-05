#include <stdio.h>
// 제 코드가 아니며, 저가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
bool valid[54];
int n;

int back(int i, int len)
{
	if (len == n)	return 1;
	if (len + i > n)	return 0;
	valid[i - 1] = 1;
	for (int t = i; t > 0; --t)
	{
		if (back(i + t, len + i))	return 1;
	}
	valid[i - 1] = 0;
	return 0;
}

int main()
{
	char alpha = 'A', res[104] = { 0 };
	scanf("%d", &n);
	if (!back(1, 0))
	{
		printf("-1");
		return 0;
	}
	for (int t = 0; t < 54; ++t)
	{
		if (valid[t])
		{
			res[t] = alpha;
			++alpha;
		}
	}
	alpha = 'A';
	for (int t = 1; t < 54; ++t)
	{
		if (!valid[t])	continue;
		int ptr = t, cnt = t;
		++alpha;
		while (cnt)
		{
			if (!res[ptr])
			{
				res[ptr] = alpha;
				--cnt;
			}
			++ptr;
		}
	}
	printf("%s", res);
	return 0;
}
