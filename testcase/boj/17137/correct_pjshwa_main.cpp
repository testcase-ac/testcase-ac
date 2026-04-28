#include <bits/stdc++.h>
using namespace std;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? "," : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200, MOD = 1e9 + 7;
int d[MAX + 1][MAX + 1];

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  sort(a.begin(), a.end());

  memset(d, 0, sizeof(d));
  for (int i = 0; i <= MAX; ++i) d[0][i] = 1;

  for (int i = 0; i < n; ++i) {
    d[i + 1][0] = 0;
    for (int j = 1; j <= MAX; ++j) {
      d[i + 1][j] = d[i + 1][j - 1];
      if (j <= a[i]) d[i + 1][j] = (d[i + 1][j] + d[i][j]) % MOD;
    }
  }

  cout << ((long long)n * d[n][MAX]) % MOD << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
