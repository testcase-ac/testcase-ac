#include <bits/stdc++.h>
using namespace std;
int arr[10000000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	while(n--) {
		int t;
		cin >> t;
		if(arr[t])
			return !(cout << t);
		arr[t]++;
	}
}
