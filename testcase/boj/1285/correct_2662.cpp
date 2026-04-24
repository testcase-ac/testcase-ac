#include <bits/stdc++.h>
using namespace std;
#define int long long
int n;
char arr[32][33], tmp[32][33];
int eval(vector<int>& state) {
	memcpy(tmp, arr, sizeof(arr));
	for(int i=0; i<n; i++) {
		if(state[i]) {
			for(int j=0; j<n; j++)
				tmp[i][j] = !tmp[i][j];
		}
	}
	int sum = 0;
	for(int j=0; j<n; j++) {
		int cnt = 0;
		for(int i=0; i<n; i++) {
			cnt += tmp[i][j];
		}
		sum += min({cnt, n-cnt});
	}
	return sum;
}
mt19937 _rng(chrono::high_resolution_clock::now().time_since_epoch().count());
uniform_int_distribution<int> dis(0,INT_MAX);
uniform_real_distribution<double> disdb(0, 1);
int rng(int ub){return dis(_rng)%ub;}
double rngdb(){return disdb(_rng);}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n;
	int tcnt = 0;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
		for(int j=0; j<n; j++) {
			arr[i][j] = (arr[i][j] == 'T');
			if(arr[i][j])
				tcnt++;
		}
	}
	vector<int> state(n), tmpst(n);
	int cur = eval(state), ans = cur;
	double k = 1;
	for(int t=0; t<1000000; t++) {
		tmpst = state;
		int i = rng(n);
		tmpst[i] = !tmpst[i];
		int nxt = eval(tmpst);
		double p = exp((cur-nxt)/k);
		if(p > rngdb()) {
			state = tmpst;
			cur = nxt;
			ans = min(ans, cur);
		}
		k *= 0.99999;
	}
	cout << ans;
}
