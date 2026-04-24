#include <bits/stdc++.h>
using namespace std;
#define int long long
double solve() {
	int n;
	cin >> n;
	vector<double> arr;
	for(int i=0; i<n; i++) {
		double t;
		cin >> t;
		if(t == 0)
			continue;
		arr.push_back(t);
	}
	n = arr.size();
	if(arr.empty())
		return 0;
	sort(arr.begin(), arr.end());
	if(arr.back() == 1)
		return 1;

	double product = 1, sum = 0;
	auto f = [&](double add = -1){
		if(add == -1) {
			return product*sum;
		} else {
			return product*(1-add)*(sum+add/(1-add));
		}
	};
	double ans = 0;
	for(int i=0, j=0; i<n; product /= (1-arr[i]), sum -= (arr[i]/(1-arr[i])), i++) {
		// if(i % 100 == 0) {
		// 	product = 1;
		// 	sum = 0;
		// 	for(int k=i; k<j; k++) {
		// 		product *= (1-arr[k]);
		// 		sum += arr[k]/(1-arr[k]);
		// 	}
		// }
		while(j < n && f() < f(arr[j])) {
			product *= (1-arr[j]);
			sum += (arr[j])/ (1-arr[j]);
			j++;
		}
		ans = max(ans, f());
	}
	return ans;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int t;
	cin >> t;
	while(t--) {
		cout << fixed << setprecision(10) << solve() << '\n';
	}
}
