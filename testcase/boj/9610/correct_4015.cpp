#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
int q1, q2, q3, q4, axis;
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	while(n--) {
		int x, y;
		cin >> x >> y;
		if(!x || !y) axis++;
		else {
			if(x > 0)
				if(y > 0) q1++;
				else q4++;
			else {
				if(y > 0) q2++;
				else q3++;			
			}
		}
	}
	printf("Q1: %d\nQ2: %d\nQ3: %d\nQ4: %d\nAXIS: %d", q1, q2, q3, q4, axis);
}
