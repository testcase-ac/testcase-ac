#include <bits/stdc++.h>
using namespace std;

int main(){
	int n;
	cin >> n;
	vector<int> v(n);
	for(int i=0; i<n; i++) cin >> v[i];
	int mxv = -1;
	int dap = 0;
	for(int i=n-1; i>=0; i--){
		if(mxv < v[i]){
			mxv = v[i];
			dap++;
		}
	}
	cout << dap << endl;
	return 0;
}
