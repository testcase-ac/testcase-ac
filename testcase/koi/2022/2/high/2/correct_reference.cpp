#include <vector>
#include <queue>
#include <cstdio>

using namespace std;

vector<int> P = {-1};
queue<int> S[300009];
int A[300009], C[300009], X[300009], L;
bool used[300009];

void del(int a) {
	X[C[a]--] ^= a;
	X[C[a]] ^= a;
	int i = S[a].front();
	used[i] = true;
	P.push_back(i);
	S[a].pop();
	--L;
}

int main() {
	int N;
	scanf("%d", &N);
	L = N;
	for(int i=1; i<=N; i++) {
		scanf("%d", &A[i]);
		++C[A[i]];
		S[A[i]].push(i);
	}
	for(int i=1; i<=N; i++) X[C[i]] ^= i;

	int i = 1, c = 0, a = -1;
	while(i <= N) {
		if(used[i]) {
			++i;
			continue;
		}
		if(c == 0) a = A[i], c = 1, ++i;
		else if(a == A[i]) ++c, ++i;
		else {
			int hx = X[L / 2 + 1];
			if(L % 2 && hx) {
				if(a == hx) --c;
				del(hx);
			}
			else {
				if(A[P.back()] != a) {
					--c;
					del(a);
				}
				else del(A[i++]);
			}
		}
	}
	while(c--) del(a);
	for(int i=2; i<=N; i++) if(A[P[i-1]] == A[P[i]]) {
		printf("-1");
		return 0;
	}
	for(int i=1; i<=N; i++) printf("%d ", P[i]);
	return 0;
}