#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

vector<string> B;
set<char> S[26], U;
vector<char> V[26];
int N;
string cur = "";

void dfs(int i) {
  if (i == N) {
    B.push_back(cur);
    return;
  }

  for (char c : S[i]) {
    cur.push_back(c);
    dfs(i + 1);
    cur.pop_back();
  }
}

void solve() {
  int M;
  cin >> N >> M;

  vector<string> A(M);
  for (int i = 0; i < M; i++) {
    cin >> A[i];
    for (int j = 0; j < A[i].size(); j++) V[j].push_back(A[i][j]);
  }

  for (int i = 0; i < N; i++) {
    for (char c : V[i]) S[i].insert(c);
    for (char c : S[i]) {
      if (U.count(c)) return cout << "NO\n", void();
      U.insert(c);
    }
  }

  dfs(0);
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  if (A == B) {
    cout << "YES\n";
    for (int i = 0; i < N; i++) {
      for (char c : S[i]) cout << c;
      cout << '\n';
    }
  }
  else cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
