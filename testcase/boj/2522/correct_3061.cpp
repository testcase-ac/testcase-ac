#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	int n;
	cin >> n;
	rep(line, n-1) {
		rep(i, n-line-1) cout << ' ';
		rep(i, line+1) cout << '*';
		cout << '\n'; 
	}
	rep(i, n) cout << '*';
	cout << '\n';
	rep(line, n-1) {
		rep(i, line+1) cout << ' ';
		rep(i, n-line-1) cout << '*';
		cout << '\n';
	}
}
