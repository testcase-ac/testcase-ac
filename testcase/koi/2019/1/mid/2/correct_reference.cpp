#include <bits/stdc++.h>

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

const int MAXN = 1e5 + 10;
const int MAXL = 1e6 + 10;

pii p[MAXN];
int lx[MAXL], ly[MAXL];

int main() {
	int n; scanf("%d", &n);
	for(int i=1;i<=n;i++) {
		int x, y; scanf("%d%d", &x, &y);
		x += MAXL / 2;
		y += MAXL / 2;
		p[i] = pii(x, y);
	}
	for(int i=1;i<=n;i++) {
		int j = i%n + 1;
		if(p[i].Fi == p[j].Fi) {
			int y1 = p[i].Se, y2 = p[j].Se;
			if(y1 > y2) swap(y1, y2);
			ly[y1]++, ly[y2]--;
		}
		else {
			int x1 = p[i].Fi, x2 = p[j].Fi;
			if(x1 > x2) swap(x1, x2);
			lx[x1]++, lx[x2]--;
		}
	}
	for(int i=1;i<MAXL;i++) lx[i] += lx[i-1];
	for(int i=1;i<MAXL;i++) ly[i] += ly[i-1];
	int ans = max(*max_element(lx, lx+MAXL), *max_element(ly, ly+MAXL));
	printf("%d\n", ans);
	return 0;
}
