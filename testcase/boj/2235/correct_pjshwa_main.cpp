#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string S, ans, cur;
int N;

bool sless(string a, string b) {
  if (a.size() != b.size()) return a.size() < b.size();

  for (int i = 0; i < a.size(); i++) {
    if (a[i] != b[i]) return a[i] < b[i];
  }
  return false;
}

void dfs(int i) {
  if (i == N) {
    if (sless(cur, ans)) ans = cur;
    return;
  }

  if (i < N - 1 && stoi(S.substr(i, 2)) <= 25) {
    int x = stoi(S.substr(i, 2));
    cur.push_back(S[]
  }

}

int tc;
void solve() {
  cout << "Problem " << ++tc << "\n";

  N = S.size();
  cur = ans = "";
  for (int i = 0; i < N; i++) ans.push_back('Z');
}

int main() {
  fast_io();

  while (cin >> S) {
    if (S == "#") break;
    solve();
  }
}
