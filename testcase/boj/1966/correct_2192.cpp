#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>
#include <functional>

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
		int n, m, input;
		cin >> n >> m;
		queue<pair<int, bool>> que;
		map<int, int, greater<int>> mp;
		rep(i, n) {
			cin >> input;
			que.emplace(input, i==m);
			mp[input]++;
		}
		int ans = 1;
		while(!que.empty()) {
			auto p = que.front();
			que.pop();
			if((*mp.begin()).first > p.first)
				que.push(p);
			else {
				if(p.second) {
					cout << ans << '\n';
					break;
				}
				ans++;
				mp[p.first]--;
				if(!mp[p.first]) mp.erase(mp.begin());
			}
		}
	}

}
