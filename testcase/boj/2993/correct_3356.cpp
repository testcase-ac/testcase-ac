#include <bits/stdc++.h>
using namespace std;

char arr[100];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s, ans;
	cin >> s;
	int n = s.size();
	for(int i=1; i<n; i++) {
		for(int j=i+1; j<n; j++) {
			strcpy(arr, s.c_str());
			reverse(arr, arr+i);
			reverse(arr+i, arr+j);
			reverse(arr+j, arr+n);
			string t(arr);
			if(ans.empty() || t < ans)
				ans = t;
			
		}
	}
	cout << ans;
}
