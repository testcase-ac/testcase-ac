#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXV = 1e6;
int lp[MAXV + 1];
vector<int> pr;

void solve() {
  ll N; cin >> N;
  vector<int> fs;
  for (int p : pr) {
    if (N % p) continue;
    int cnt = 0;
    while (N % p == 0) {
      N /= p;
      ++cnt;
    }
    fs.push_back(cnt);
  }
  if (N > 1) fs.push_back(1);

  int sumv = accumulate(fs.begin(), fs.end(), 0);
  int maxv = *max_element(fs.begin(), fs.end());
  if (2 * maxv > sumv || sumv % 2 == 1) cout << "yyyy7089\n";
  else cout << "toycartoon\n";
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAXV; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXV; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
