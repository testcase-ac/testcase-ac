#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <functional>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))
#define def function
#define deb(v) cout << #v << ':' << v << '\n';
using namespace std;

string s = "CAMBRIDGE";

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string inp;
	cin >> inp;
	for(char c: inp) {
		for(char t: s) {
			if(c == t) goto next;
		}
		cout << c;
		next:;
	} 
}
