#include<stdio.h>
#include<algorithm>
#include<map>
// 제 코드가 아니며, 제가 해당 문제를 클리어한 후 실행 속도가 가장 빠른 코드 위주로 퍼와 추가하고 있습니다.
using namespace std;
int n, m, p;
int a[11][11];
map<int, int> d[11][101];
int e[11][1025];
int ccount[1024];
int klist[1024];
int kl;
int main() {
	int i, j, k, l;
	scanf("%d %d %d", &n, &m, &p);
	for (k = 0; k < (1 << m); k++) {
		if (k & (k << 1))continue;
		klist[kl++] = k;
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			scanf("%d", &a[i][j]);
		}
		for (int ki = 0; ki < kl; ki++) {
			k = klist[ki];
			int cur = 0;
			for (j = 0; j < m; j++) {
				if (k & (1 << j)) {
					cur += a[i][j];
				}
			}
			e[i][k] = cur;
		}
	}
	for (i = 1; i < (1 << m); i++) {
		ccount[i] = ccount[i & (i - 1)] + 1;
	}

	//baseline
	for(int ki=0; ki<kl; ki++){
		k = klist[ki];
		if(ccount[k] <= p)
			d[0][ccount[k]][k] = e[0][k];
	}
	for (i = 0; i < n - 1; i++) {
		for (j = 0; j <= p; j++) {
			for (auto it : d[i][j]) {
				for(int ki = 0; ki < kl; ki++) {
					k = klist[ki];
					if (it.first & k)continue;
					if (j + ccount[k] <= p) {
						int tj = j + ccount[k];
						int cur = e[i+1][k];
						if (d[i + 1][tj].find(k) == d[i + 1][tj].end()) {
							d[i + 1][tj][k] = it.second + cur;
						}
						else if (d[i + 1][tj][k] < it.second + cur) {
							d[i + 1][tj][k] = it.second + cur;
						}
					}
				}
			}
		}
	}
	int res = -1000000009;
	for (auto it : d[n - 1][p]) {
		res = max(res, it.second);
	}
	printf("%d\n", res);
}
