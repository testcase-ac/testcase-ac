#include <bits/stdc++.h>
using namespace std;
const int MX = 300000;
bool seen[MX];
int last[MX];
int main() {
	int n, k;
	cin >> n >> k;
	if(n == k) return !(cout << "0\n" << n << ' ');
	memset(last, -1, sizeof last);
	seen[n] = true;
	queue<int> que;
	que.push(n);
	int t = 0;
	while(1) {
		int s = que.size();
		while(s--) {
			int q = que.front();
			que.pop();
			if(q == k) {
				cout << t << '\n';
				vector<int> ans = {q};
				while(last[q] != -1) {
					ans.push_back(last[q]);
					q = last[q];
				}
				reverse(ans.begin(), ans.end());
				for(int a: ans) cout << a << ' ';
				return 0;
			}
			for(int i: {q-1, q+1, q*2}) {
				if(i < 0 || i >= MX) continue;
				if(!seen[i]) {
					seen[i] = true;
					que.push(i);
					last[i] = q;
				}
			}
		}
		t++;
	}
}
