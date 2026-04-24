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
	while(n--) {
		int arr[5];
		rep(i,5) cin >> arr[i];
		sort(arr, arr+5);
		if(arr[3]-arr[1] >= 4)
			cout << "KIN\n";
		else
			cout << arr[1]+arr[2]+arr[3] << '\n'; 
	}
}
