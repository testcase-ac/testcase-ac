#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <cassert>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

inline int D(int x) {
	return (2*x) % 10000;
}
inline int S(int x) {
	return (x+9999)%10000;
}
inline int L(int x) {
	return (x % 1000)*10+x/1000;
}
inline int R(int x) {
	return (x / 10) + (x % 10)*1000;
}

bool visited[10000];
char chararr[] = {'D','S','L','R'};
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
    assert(T <= 10000);
	while(T--) {
		int a, b;
		cin >> a >> b;
		set0(visited);
		queue<pair<int,string>> que;
		que.emplace(a, "");
		visited[a] = true;
		while(!que.empty()) {
			auto pr = que.front();
			int n = pr.first;
			if(n == b) {
				cout << pr.second << '\n';
				break;
			}
			que.pop();
			int narr[] = {D(n), S(n), L(n), R(n)};
			rep(i, 4) {
				if(!visited[narr[i]]) {
					visited[narr[i]] = true;
					que.emplace(narr[i], pr.second+chararr[i]);
				}
			}
		}
	}
}