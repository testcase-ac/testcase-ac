#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> bits;
	for(int i=0; i<30; i++) {
		if(n&(1<<i)) bits.push_back(1);
		else bits.push_back(0);
	}
	while(!bits.back()) bits.pop_back();
	int ans = 0, factor = (1<<(bits.size()-1));
	for(int b: bits) {
		ans += factor*b;
		factor >>= 1;
	}
	cout << ans;
}
