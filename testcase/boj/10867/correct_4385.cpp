#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <set>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	set<int> s;
	int n;
	cin >> n;
	rep(i, n) {
		int inp;
		cin >> inp;
		s.insert(inp);
	}
	for(int i: s) {
		cout << i << ' ';
	}

}
