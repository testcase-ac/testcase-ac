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
#define ldb long double
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, m, k;
	cin >> n >> m >> k;
	if(m+k-1 > n || n > m*k) return !(cout << -1);
	int arr[n];
	rep(i, n) arr[i] = i+1;
	reverse(arr, arr+k);
	rep(i, m-1) reverse(arr+k+(i*(n-k))/(m-1), arr+k+((i+1)*(n-k))/(m-1));
	rep(i, n) cout << arr[i] << ' ';
}
