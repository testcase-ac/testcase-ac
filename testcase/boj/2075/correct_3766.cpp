#include <bits/stdc++.h>
using namespace std;

struct comp {
	bool operator() (int a, int b) {
		return a > b;
	}
};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	priority_queue<int, vector<int>, comp> pq;
	for(int j=0; j<n; j++) {
		int t;
		cin >> t;
		pq.push(t);
	}
	for(int i=1; i<n; i++) {
		for(int j=0; j<n; j++) {
			int t;
			cin >> t;
			pq.push(t);
			pq.pop();
		}
	}
	cout << pq.top();
}
