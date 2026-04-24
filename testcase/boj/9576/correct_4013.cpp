#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define deb(v) cout << #v << ':' << v

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		int n, m;
		cin >> n >> m;
		vector<int> match(m+n, -1);
		vector<vector<int>> adj(m+n);
		rep(i, m) {
			int a, b;
			cin >> a >> b;
			a--, b--;
			for(int j=m+a; j<=m+b; j++) {
				adj[i].push_back(j);
				adj[j].push_back(i);
			}
		}
		int ans = 0;
		rep(i, m) {
			/* try find augmenting path for each student. Found when reached unmatched book.
			At student: can go to book in range if student->book is NOT a match
			At book: can go to student in range if student->book is a match
			*/
			queue<int> que;
			que.push(i);
			vector<int> from(m+n, -1); // work as visited
			from[i] = -2;
			while(!que.empty()) {
				int q = que.front();
				que.pop();
				for(int a: adj[q]) {
					if(from[a] != -1 || (q < m && match[q] == a) || (q >= m && match[a] != q)) continue;
					from[a] = q;
					if(a >= m && match[a] == -1) {
						ans++;
						int now = a;
						while(now != i) {
							if(now >= m)
								match[from[now]] = now, match[now] = from[now];
							now = from[now];
						}
						goto next;
					}
					que.push(a);
				}
			}
			next:;
		}
		cout << ans << '\n';
	}
}
