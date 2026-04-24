#include <bits/stdc++.h>
using namespace std;
char arr[1001];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		for(int i=0; i<n; i++) {
			cin >> arr[i];
		}
		vector<int> stk;
		for(int i=n-1; i>=0; i--) {
			while(!stk.empty() && arr[stk.back()] > arr[i])
				stk.pop_back();
			stk.push_back(i);
		}
		for(int i: stk)
			cout << arr[i];
		int j = stk.size()-1;
		for(int i=0; i<n; i++) {
			if(j >= 0 && stk[j] == i) {
				j--;
				continue;
			}
			cout << arr[i];
		}
		cout << '\n';
	}
}
