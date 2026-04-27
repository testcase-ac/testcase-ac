#include <iostream>
#include <vector>
 
using namespace std;
 
int main() {
	int n;
	cin >> n;
 
	vector<int> A(n + 1), B(n + 1);
	for (int i = 1; i <= n; i++) cin >> A[i] >> B[i];
 
	constexpr int mod = 1e9 + 7;
	vector<long long> ans(n + 1), cnt(n + 1), prefix(n + 1), suffix(n + 1);
	ans[0] = 1, cnt[0] = 1, prefix[0] = 1, suffix[0] = 1;
 
	for (int i = 1; i <= n; i++) {
		cnt[i] = cnt[A[i]] + cnt[B[i]];
		cnt[i] %= mod;
 
		prefix[i] = prefix[A[i]] + prefix[B[i]] + cnt[B[i]] - 1 + mod;
		prefix[i] %= mod;
 
		suffix[i] = suffix[A[i]] + suffix[B[i]] + cnt[A[i]] - 1 + mod;
		suffix[i] %= mod;
 
		ans[i] = ans[A[i]] + ans[B[i]] + suffix[A[i]] * cnt[B[i]] + prefix[B[i]] * cnt[A[i]] - 1 + mod;
		ans[i] %= mod;
	}
 
	for (int i = 1; i <= n; i++) cout << ans[i] << "\n";
}
