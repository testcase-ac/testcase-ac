#include <bits/stdc++.h>
using namespace std;
int arr[10], n, k;
bool has[10];
vector<int> v;
set<int> st;
void f(int p, int t) {
	if(t == k) {
		int s = 0;
		for(int i: v) {
			if(i >= 10) s *= 100;
			else s *= 10;
			s += i;
		}
		st.insert(s);
		return;
	}
	for(int i=0; i<n; i++) {
		if(!has[i]) {
			has[i] = 1;
			v.push_back(arr[i]);
			f(p+1, t+1);
			v.pop_back();
			has[i] = 0;
		}
	}
	if(p+1+k<=n)
		f(p+1, t);

}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> k;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
	}
	f(0, 0);
	cout << st.size();
}
