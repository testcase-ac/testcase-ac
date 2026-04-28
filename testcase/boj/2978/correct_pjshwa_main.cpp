#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<string> split(const string &str, string delim) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(delim, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delim.size();
  }

  tokens.push_back(str.substr(start));
  return tokens;
}

const int MAXN = 1000, MAXV = 5000, INF = 0x3f3f3f3f;
int dp[MAXN + 1][MAXV + 1], Z[MAXN], N, S;
string A;

int rec(int i, int v) {
  if (i == N) return v == S ? 0 : INF;
  if (dp[i][v] != -1) return dp[i][v];

  int ret = INF, num = 0;
  for (int j = Z[i]; j < N; ++j) {
    num = num * 10 + (A[j] - '0');
    if (v + num > S) break;
    ret = min(ret, 1 + rec(j + 1, v + num));
  }
  return dp[i][v] = ret;
}

void trace(int i, int v) {
  if (i == N) {
    cout << "=" << S << '\n';
    return;
  }

  if (i > 0) cout << '+';

  int num = 0;
  for (int j = i; j < N; ++j) {
    cout << A[j];
    num = num * 10 + (A[j] - '0');

    if (rec(i, v) != 1 + rec(j + 1, v + num)) continue;
    return trace(j + 1, v + num);
  }
}

void solve() {
  string SS; cin >> SS;
  auto chunks = split(SS, "=");
  A = chunks[0]; S = stoi(chunks[1]);
  N = A.size();

  Z[N - 1] = N - 1;
  for (int i = N - 2; i >= 0; --i) Z[i] = (A[i] == '0') ? Z[i + 1] : i;

  memset(dp, -1, sizeof(dp));
  trace(0, 0);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
