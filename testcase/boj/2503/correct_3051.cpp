#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';
using namespace std;
bool fail[10][10][10];
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	while(n--) {
		int num, st, ball;
		cin >> num >> st >> ball;
		int n1 = num % 10, n2 = (num/10)%10, n3 = (num/100);
		for (int i = 1; i < 10; i++) {
			for(int j=1; j<10; j++) {
				for(int k=1; k<10; k++) {
					if(i == j || j == k || i == k || fail[i][j][k]) continue;
					int s=0, b=0;
					if(i == n1) s++;
					else if(n1 == j || n1 == k) b++;
					if(j == n2) s++;
					else if(n2 == i || n2 == k) b++;
					if(k == n3) s++;
					else if(n3 == i || n3 == j) b++;
					if(s != st || b != ball) fail[i][j][k] = true;
				}
			}
		}
	}
	int ans = 0;
	for (int i = 1; i < 10; i++) {
		for(int j=1; j<10; j++) {
			for(int k=1; k<10; k++) {
				if(i == j || j == k || i == k) continue;
				if(!fail[i][j][k]) ans++;
			}
		}
	}
	cout << ans;
}
