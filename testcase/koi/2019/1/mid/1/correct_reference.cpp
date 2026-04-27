#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <math.h>
#include <assert.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <iostream>
#include <functional>
#include <unordered_set>
#include <bitset>
#include <time.h>
#include <limits.h>

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define Fi first
#define Se second
#define pb push_back
#define szz(x) (int)x.size()
#define rep(i,n) for(int i=0;i<n;i++)
#define all(x) x.begin(),x.end()
typedef tuple<int, int, int> t3;

int n, a[20];
int L[2000000*15];

void dfs(int x, int s) {
	if(x == n) {
		if(s >= 1) L[s] = 1;
	}
	else {
		dfs(x+1, s);
		dfs(x+1, s+a[x]);
		dfs(x+1, s-a[x]);
	}
}

int main() {
	scanf("%d", &n);
	for(int i=0;i<n;i++) scanf("%d", a + i);
	dfs(0, 0);
	int sum = 0, ans = 0;
	for(int i=0;i<n;i++) sum += a[i];
	for(int i=1;i<=sum;i++) if(L[i] == 0) ++ans;
	printf("%d\n", ans);
	return 0;
}
