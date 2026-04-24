#include <bits/stdc++.h>
using namespace std;
int arr[8];
set<int> st;
int get() {
	int mn = INT_MAX;
	for(int i=0; i<4; i++) {
		int n = 0;
		for(int j=0; j<4; j++) {
			n *= 10;
			n += arr[i+j];
		}
		mn = min(n, mn);
	}
	return mn;
}
void f(int p) {
	if(p == 4) {
		st.insert(get());
		return;
	}
	for(int i=1; i<=9; i++) {
		arr[p] = arr[p+4] = i;
		f(p+1);
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	f(0);
	for(int i=0; i<4; i++) {
		cin >> arr[i];
		arr[i+4] = arr[i];
	}
	int t = get(), ans = 1;
	auto it = st.begin();
	while(*it != t) {
		ans++;
		it++;
	}
	cout << ans;
}
