#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
using namespace std;


bool myCompStr(string i, string j) {
	return (sz(i) < sz(j)) || (sz(i) == sz(j) && i < j);
}

int main() {
	int n;
	cin >> n;
	vector<string> arr(n);
	rep(i, n) cin >> arr[i];
	sort(arr.begin(), arr.end(), myCompStr);
	rep(i, n) {
		if(i == 0 || (i > 0 && arr[i] != arr[i-1])) cout << arr[i] << '\n';
	}
}
