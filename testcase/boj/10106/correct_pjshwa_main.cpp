#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
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

const int MAX = 1e5;
int A[MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];
  reverse(A, A + N);

  stack<int> s;
  int next = 1;
  for (int i = 0; i < N; i++) {
    while (!s.empty() && s.top() == next) {
      s.pop();
      next++;
    }

    if (A[i] == next) next++;
    else s.push(A[i]);
  }

  while (!s.empty() && s.top() == next) {
    s.pop();
    next++;
  }

  if (next == N + 1) cout << "Y\n";
  else cout << "N\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
