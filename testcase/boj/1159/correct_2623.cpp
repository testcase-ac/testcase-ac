#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
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

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	vector<int> arr(26);
	rep(i, n) {
		string s;
		cin >> s;
		arr[s[0]-'a']++;
	}
	bool ok = false;
	rep(i, 26) {
		if(arr[i] >= 5) {
			ok = true;
			cout << (char)(i+'a');
		}
	}
	if(!ok)
		cout << "PREDAJA";
}
