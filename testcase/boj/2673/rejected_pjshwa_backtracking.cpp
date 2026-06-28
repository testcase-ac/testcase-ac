#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool is_between(pii a, int p) {
  return a.first <= p && p <= a.second;
}

bool intersect(pii a, pii b) {
  return is_between(a, b.first) ^ is_between(a, b.second);
}

pii chords[50];
bool vis[50];
int n, maxs;

void dfs(int i, int s) {
  maxs = max(maxs, s);
  if (i == n) return;

  pii chord = chords[i];
  bool able = true;
  for (int j = 0; j < i; j++) {
    if (vis[j] && intersect(chord, chords[j])) able = false;
  }
  if (able) {
    vis[i] = 1;
    dfs(i + 1, s + 1);
    vis[i] = 0;
  }
  dfs(i + 1, s);
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    if (a > b) swap(a, b);
    chords[i] = make_pair(a, b);
  }

  dfs(0, 0);
  cout << maxs;
}
