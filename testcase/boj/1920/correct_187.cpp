#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m, temp;
	cin >> n;
	vector<int> arr(n);
	rep(i, n) cin >> arr[i];
	sort(arr.begin(), arr.end());
	cin >> m;
	rep(i, m) {
		cin >> temp;
		if(binary_search(arr.begin(), arr.end(), temp)) 
			cout << "1\n";
		else
			cout << "0\n";
	}


}
