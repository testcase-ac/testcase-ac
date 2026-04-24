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
	string s;
	cin >> s;
	int arr[] = {1,0,0};
	for(char c: s) {
		if(c == 'A') swap(arr[0], arr[1]);
		else if(c == 'B') swap(arr[1], arr[2]);
		else swap(arr[0], arr[2]);
	}
	rep(i,3) {
		if(arr[i]) cout << i+1;
	}
}
