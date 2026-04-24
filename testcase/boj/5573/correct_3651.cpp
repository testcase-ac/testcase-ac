#include <bits/stdc++.h>
using namespace std;
int a[1001][1001], cnt[1001][1001], di[] = {1, 0}, dj[] = {0, 1};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int R, C, n;
	cin >> R >> C >> n;
	for(int i=0; i<R; i++) {
		for(int j=0; j<C; j++) {
			cin >> a[i][j];
			if(!i && !j)
				cnt[i][j] = n-1;
			int t = a[i][j], c = cnt[i][j];
			cnt[i+di[t]][j+dj[t]] += (c+1)/2;
			cnt[i+di[t^1]][j+dj[t^1]] += c/2;
			a[i][j] += c;
			a[i][j] %= 2;
		}
	}
	int i = 0, j = 0;
	while(i != R && j != C) {
		i += di[a[i][j]];
		j += dj[a[i][j]];
	}
	cout << (i+1) << ' ' << (j+1);
}
