#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX], B[MAX], C[MAX];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 0; i < N; i++) cin >> A[i] >> B[i] >> C[i];

  ll ans = 0;
  {
    vector<int> V;
    for (int i = 0; i < N; i++) V.push_back(A[i] + B[i]);
    sort(V.begin(), V.end(), greater<int>());

    ll cur = 0;
    for (int i = 0; i < K; i++) cur += V[i];
    ans = max(ans, cur);
  }
  {
    vector<int> V;
    for (int i = 0; i < N; i++) V.push_back(A[i] + C[i]);
    sort(V.begin(), V.end(), greater<int>());

    ll cur = 0;
    for (int i = 0; i < K; i++) cur += V[i];
    ans = max(ans, cur);
  }
  {
    vector<int> V;
    for (int i = 0; i < N; i++) V.push_back(B[i] + C[i]);
    sort(V.begin(), V.end(), greater<int>());

    ll cur = 0;
    for (int i = 0; i < K; i++) cur += V[i];
    ans = max(ans, cur);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
