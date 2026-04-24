#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;
#define MAXN 100000
bool visited[MAXN];
int visitorder[MAXN], adj[MAXN];


int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		rep(i, n) {
			cin >> adj[i];
			adj[i]--;
		}
		int ans = 0;
		set0(visited);
		set0(visitorder);
		int t = 1, startt = t;
		rep(i, n) {
			if(visited[i]) continue;
			if(adj[i] == i) {
				visited[i] = true;
				ans++;
			} else {
				//printf("traversing start from i=%d\n", i);
				int now = adj[i];
				startt = t;
				while(!visited[now]) {
					visitorder[now] = t;
					visited[now] = true;
					now = adj[now];
					t++;
				}
				if(visitorder[now] && visitorder[now] >= startt)
					ans += (t - visitorder[now]);
			}
		}
		cout << (n-ans) << '\n';
	}
}
