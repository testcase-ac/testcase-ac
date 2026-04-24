#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

string arr[14] = {"baby", "sukhwan", "tururu", "turu", "very", "cute", "tururu", "turu", "in", "bed", "tururu", "turu", "baby", "sukhwan"};
int cnt[14] = {0,0,2,1,0,0,2,1,0,0,2,1,0,0};
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	n--;
	int cycle = n / 14;
	int index = n % 14;
	if(!cnt[index])
		cout << arr[index];
	else {
		int t = cnt[index] + cycle;
		if(t >= 5)
			cout << "tu+ru*" << t;
		else {
			cout << "tu";
			rep(i,t) cout << "ru";
		}
	}
}
