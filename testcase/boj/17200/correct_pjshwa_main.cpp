#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

map<string, int> fi;
int fcount;
int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    return fcount++;
  }
  else return found->second;
}

void solve() {
  int N;
  cin >> N;

  vector<set<int>> skills(N);
  for (int i = 0; i < N; i++) {
    int K;
    cin >> K;

    for (int j = 0; j < K; j++) {
      string s; cin >> s;
      skills[i].insert(fidx(s));
    }
  }

  set<int> pre[fcount];
  for (int i = 0; i < N; i++) for (int j = i + 1; j < N; j++) {
    set<int> common;
    for (int s1 : skills[i]) for (int s2 : skills[j]) {
      if (s1 == s2) common.insert(s1);
    }

    for (int s1 : skills[i]) {
      if (common.count(s1)) continue;
      for (int c : common) pre[s1].insert(c);
    }
    for (int s2 : skills[j]) {
      if (common.count(s2)) continue;
      for (int c : common) pre[s2].insert(c);
    }
  }

  for (int i = 0; i < N; i++) {
    for (int s : skills[i]) {
      for (int p : pre[s]) {
        if (skills[i].count(p)) continue;
        return cout << "no\n", void();
      }
    }
  }
  cout << "yes\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
