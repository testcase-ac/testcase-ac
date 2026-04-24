#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	int arr[n];
	rep(i,n) cin >> arr[i];
	sort(arr, arr+n);
	for(int i=n-1; i>=0; i--) cout << arr[i] << '\n';
}
