#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

struct pt{
	int a, b, c, i;
	bool operator< (const pt& p) const {
		if(a+2*b+3*c == p.a+2*p.b+3*p.c) {
			if(c == p.c) {
				if(b == p.b) {
					return a < p.a;
				} else return b < p.b;
			} else return c < p.c;
		} else
			return a+2*b+3*c < p.a+2*p.b+3*p.c;
	}
};
pt arr[3];
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	rep(i,3) arr[i].i = i+1;
	rep(i,n) {
		int a[3];
		rep(j,3) cin >> a[j];
		rep(j,3) {
			if(a[j] == 1) {
				arr[j].a++;
			} else if(a[j] == 2) {
				arr[j].b++;
			} else if(a[j] == 3) {
				arr[j].c++;
			} 
		}
	}
	sort(arr, arr+3);
	int ms = arr[2].a+arr[2].b*2+arr[2].c*3;
	if(!(arr[1] < arr[2]) && !(arr[1] < arr[2])) {
		cout << "0 " << ms;
	} else {
		cout << arr[2].i << ' ' << ms;
	}
}
