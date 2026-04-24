#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, inp;
	cin >> n;
	priority_queue<int, vector<int>, greater<int>> que;
	rep(i, n) {
		cin >> inp;
		if(!inp) {
			if(que.empty()) {
				cout << 0 << '\n';
			} else {
				cout << que.top() << '\n';
				que.pop();
			}
		} else {
			que.push(inp);
		}
	}
}
