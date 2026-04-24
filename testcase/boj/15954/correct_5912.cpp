#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int arr[500], n, k;
inline double sq(double i){return i*i;}
double stdev(int l, int r) { // [l,r)
	double mean = 0, devi = 0;
	for(int i=l; i<r; i++) mean += arr[i];
	mean /= (r-l);
	for(int i=l; i<r; i++) {
		devi += sq(arr[i] - mean);
	}
	double ret = sqrt(devi/(r-l));
	return ret;
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cout.setf(ios::fixed);
	cout.precision(15);
	cin >> n >> k;
	rep(i,n) cin >> arr[i];
	//sort(arr, arr+n);
	double ans = DBL_MAX;
	for(int i=0; i<n; i++) {
		for(int j=i+k; j<=n; j++) {
			ans = min(ans, stdev(i, j));
		}
	}
	cout << ans;
}
