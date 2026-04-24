#include <bits/stdc++.h>
using namespace std;

int a[100000];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	int sum = accumulate(a, a+k, 0), msum = sum;
	for(int i=k; i<n; i++) {
		sum += a[i];
		sum -= a[i-k];
		msum = max(msum, sum);
	}
	cout << msum;
}
