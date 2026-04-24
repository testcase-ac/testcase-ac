#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <chrono>
#include <string>
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
#define deb(v) cout << #v << ':' << v << '\n';
#define ldb long double
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n,m;
	cin >> n >> m;
	if(n == 1) {
		cout << 1;
	} else if(n == 2) {
		cout << min((m+1)/2, 4);
	} else if(m <= 6) {
		cout << min(m, 4);
	} else {
		cout << m-2;
	}
}
