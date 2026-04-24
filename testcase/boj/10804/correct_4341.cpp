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
	int arr[21];
	for(int i=1; i<=20; i++) arr[i] = i;
	for(int i=0; i<10; i++) {
		int a, b;
		cin >> a >> b;
		reverse(arr+a, arr+b+1);
	}
	for(int i=1; i<=20; i++) cout << arr[i] << ' ';
}
