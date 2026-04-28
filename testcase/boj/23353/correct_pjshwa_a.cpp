#include<iostream>
#include<algorithm>
using namespace std;
 
int n;
int arr[1010][1010];
int prefix[1010][1010][4];
int suffix[1010][1010][4];
 
int main()
{
	int i, j;
	int ans;
	
	cin.tie(NULL);
	ios::sync_with_stdio(false);
 
	cin >> n;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			cin >> arr[i][j];
		}
	}
 
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (arr[i][j] == 1)
			{
				prefix[i][j][0] = prefix[i - 1][j][0] + 1;
				prefix[i][j][1] = prefix[i][j - 1][1] + 1;
				prefix[i][j][2] = prefix[i - 1][j - 1][2] + 1;
				prefix[i][j][3] = prefix[i - 1][j + 1][3] + 1;
			}
		}
	}
 
	for (i = n; i >= 1; i--)
	{
		for (j = n; j >= 1; j--)
		{
			if (arr[i][j] == 1)
			{
				suffix[i][j][0] = suffix[i + 1][j][0] + 1;
				suffix[i][j][1] = suffix[i][j + 1][1] + 1;
				suffix[i][j][2] = suffix[i + 1][j + 1][2] + 1;
				suffix[i][j][3] = suffix[i + 1][j - 1][3] + 1;
			}
		}
	}
 
	ans = 0;
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			ans = max(ans, prefix[i][j][0]);
			ans = max(ans, prefix[i][j][1]);
			ans = max(ans, prefix[i][j][2]);
			ans = max(ans, prefix[i][j][3]);
		}
	}
 
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (arr[i][j] == 2)
			{
			int mans = ans;
				ans = max(ans, prefix[i - 1][j][0] + suffix[i + 1][j][0] + 1);
				ans = max(ans, prefix[i][j - 1][1] + suffix[i][j + 1][1] + 1);
				ans = max(ans, prefix[i - 1][j - 1][2] + suffix[i + 1][j + 1][2] + 1);
				ans = max(ans, prefix[i - 1][j + 1][3] + suffix[i + 1][j - 1][3] + 1);
				if (mans != ans && ans == 15) cout << "i: " << i << " j: " << j << " ans: " << ans << " mans: " << mans << endl;
			}
		}
	}
 
	cout << ans;
}
