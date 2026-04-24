#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define debug(var) cout << #var << ':' << var
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	bool arr[21]; set0(arr);
	int t;
	cin >> t;
	while(t--) {
		string str;
		int i;
		cin >> str;
		if(str == "add") {
			cin >> i;
			arr[i] = true;
		} else if(str == "remove") {
			cin >> i;
			arr[i] = false;
		} else if(str == "check") {
			cin >> i;
			cout << arr[i] << '\n';
		} else if(str == "toggle") {
			cin >> i;
			arr[i] = !arr[i];
		} else if(str == "all") {
			for(int j=1; j<=20; j++)
				arr[j] = true;
		} else if(str == "empty") {
			for(int j=1; j<=20; j++)
				arr[j] = false;
		}
	}
}
