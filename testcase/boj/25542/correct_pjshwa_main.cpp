#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string A[20];
bool d[20];
int N, L;
string cur = "";

void dfs(int i) {
  if (i == L) {
    cout << cur << '\n';
    exit(0);
  }

  for (char c = 'A'; c <= 'Z'; c++) {
    bool able = true;
    for (int j = 0; j < N; j++) {
      if (d[j] && A[j][i] != c) {
        able = false;
        break;
      }
    }
    if (!able) continue;

    for (int j = 0; j < N; j++) {
      if (A[j][i] != c) d[j] = true;
    }
    cur += c;
    dfs(i + 1);
    cur.pop_back();
    for (int j = 0; j < N; j++) {
      if (A[j][i] != c) d[j] = false;
    }
  }
}

void solve() {
  cin >> N >> L;
  for (int i = 0; i < N; i++) cin >> A[i];
  
  dfs(0);
  cout << "CALL FRIEND\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
