#include <bits/stdc++.h>
using namespace std;
char dq[500000];
int b, e;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	string s;
	cin >> n >> k >> s;
	for(int i=0; i<n; i++) {
		while(b != e && dq[e-1] < s[i]) e--;
		dq[e++] = s[i];
		if(i >= k)
			cout << dq[b++];
	}

}
