#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <set>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m;
	cin >> n >> m;
	set<string> nameset, ans;
	string input;
	rep(i, n) {
		cin >> input;
		nameset.insert(input);
	}
	rep(i, m) {
		cin >> input;
		if(nameset.find(input) != nameset.end()) {
			ans.insert(input);
		}
	}
	cout << sz(ans) << '\n';
	for(string name: ans) {
		cout << name << '\n';
	}

}
