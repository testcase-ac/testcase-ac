#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		vector<int> next(n);
		rep(i, n) {
			cin >> next[i];
			next[i]--;
		}
		vector<bool> visited(n);
		int ans = 0;
		rep(i, n) {
			if(!visited[i]) {
				visited[i] = true;
				ans++;
				int visiting = next[i];
				while(!visited[visiting]) {
					visited[visiting] = true;
					visiting = next[visiting];
				}
			}
		}
		cout << ans << '\n';
	}
}
