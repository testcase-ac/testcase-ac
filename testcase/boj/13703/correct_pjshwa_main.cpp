#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

long long nc[65][130];
long long rec(int time, int depth) {
  if (depth == 0) return 0;
  if (time == 0) return 1;

  if (nc[time][depth] == -1) nc[time][depth] = rec(time - 1, depth - 1) + rec(time - 1, depth + 1);
  return nc[time][depth];
}

int main() {
  fast_io();

  int k, n;
  cin >> k >> n;

  memset(nc, -1, sizeof(nc));
  cout << rec(n, k) << '\n';
}
