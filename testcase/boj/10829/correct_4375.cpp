#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	long long n;
	cin >> n;
	vector<int> v;
	while(n) {
		v.push_back(n&1);
		n /= 2;
	}
	reverse(v.begin(), v.end());
	for(int i: v) cout << i;
}
