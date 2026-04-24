#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <map>
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	map<int, int> m;
	int sum = 0, maxocc=0, maxoccnum=0;
	rep(i, 10) {
		int inp;
		cin >> inp;
		m[inp]++;
		if(m[inp] > maxocc) {
			maxocc = m[inp];
			maxoccnum = inp;
		}
		sum += inp;
	}
	cout << (sum/10) << ' ' << maxoccnum;
}
