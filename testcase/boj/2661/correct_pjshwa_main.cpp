#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<int> current;
int n;

bool overlaps() {
  for (int d = 1; d <= current.size() / 2; d++) {
    int s2 = current.size() - d, s1 = s2 - d;
    bool cover = true;
    for (int i = 0; i < d; i++) {
      if (current[s1 + i] != current[s2 + i]) {
        cover = false;
        break;
      }
    }
    if (cover) return true;
  }
  return false;
}

void dfs(int i) {
  if (current.size() == n) {
    for (int c : current) cout << c;
    exit(0);
  }

  for (int i = 1; i <= 3; i++) {
    current.push_back(i);
    if (!overlaps()) dfs(i);
    current.pop_back();
  }
}

int main() {
  fast_io();

  cin >> n;
  dfs(0);
}
