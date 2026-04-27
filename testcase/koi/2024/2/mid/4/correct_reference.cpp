#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

int A[300009], I[300009];
vector<int> G[300009];

int main() {
	int N; scanf("%d", &N);
	for(int i=2; i<=N; i++) {
	    int p; scanf("%d", &p);
	    G[p].push_back(i);
	}
	for(int i=1; i<=N; i++) {
		scanf("%d", &A[i]);
		I[A[i]] = i;
	}
	priority_queue<int> pq;
	for(auto x: G[1]) pq.push(-A[x]);
	printf("%d\n", A[1]);
	while(pq.size()) {
		int x = I[-pq.top()]; pq.pop();
		for(auto y: G[x]) pq.push(-A[y]);
		printf("%d\n", A[x]);
	}
	return 0;
}