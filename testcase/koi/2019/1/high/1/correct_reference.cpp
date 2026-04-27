#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
typedef pair<int, int> pii;
int n, K, T[110000];
priority_queue<pii>PQ;
struct point {
	int num, c;
}w[110000];
struct AA {
	int num, c, ori;
	bool operator <(const AA &p)const {
		return c != p.c ? c <p.c : num > p.num;
	}
}End[110000];
int main() {
	int i, j;
	scanf("%d%d", &n, &K);
	for (i = 1; i <= n; i++) {
		scanf("%d%d", &w[i].num, &w[i].c);
	}
	for (i = 1; i <= K; i++) {
		PQ.push({ -T[i],-i });
	}
	for (i = 1; i <= n; i++) {
		pii tp = PQ.top();
		int t = -tp.first;
		int x = -tp.second;
		t += w[i].c;
		End[i] = { x, t, i };
		T[x] = t;
		PQ.pop();
		PQ.push({ -T[x],-x });
	}
	sort(End + 1, End + n + 1);
	long long sum = 0;
	for (i = 1; i <= n; i++) {
		sum += 1LL * w[End[i].ori].num * i;
	}
	printf("%lld\n",sum);
  return 0;
}