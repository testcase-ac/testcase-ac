#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <map>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	string str;
	int maxcnt=0;
	map<string, int> bookmap;
	rep(i, n) {
		cin >> str;
		bookmap[str]++;
		if(bookmap[str] > maxcnt)
			maxcnt = bookmap[str];
	}
	for(auto kv: bookmap) {
		if(kv.second == maxcnt) {
			cout << kv.first;
			break;
		}
	}
}
