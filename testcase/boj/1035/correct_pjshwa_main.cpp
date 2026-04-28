#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5;
char ob[MAX + 1][MAX + 1];
bool b[MAX][MAX];
bool svis[1 << 25], bvis[MAX * MAX];
int n = 5;

int board_to_mask() {
  int mask = 0;
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) {
    if (b[i][j]) mask |= (1 << (i * n + j));
  }
  return mask;
}

void dfs(int i, int mask) {
  bvis[i] = true;

  if (i % n != 0 && !bvis[i - 1] && (mask & (1 << (i - 1)))) dfs(i - 1, mask);
  if (i % n != n - 1 && !bvis[i + 1] && (mask & (1 << (i + 1)))) dfs(i + 1, mask);
  if (i - n >= 0 && !bvis[i - n] && (mask & (1 << (i - n)))) dfs(i - n, mask);
  if (i + n < n * n && !bvis[i + n] && (mask & (1 << (i + n)))) dfs(i + n, mask);
}

bool connected(int mask) {
  memset(bvis, 0, sizeof(bvis));
  int cc = 0;
  for (int i = 0; i < n * n; i++) if (!bvis[i] && (mask & (1 << i))) {
    dfs(i, mask);
    cc++;
  }
  return cc == 1;
}

int main() {
  fast_io();

  for (int i = 0; i < n; i++) cin >> ob[i];
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) b[i][j] = ob[i][j] == '*';

  queue<pii> q;
  q.push({board_to_mask(), 0});

  while (!q.empty()) {
    auto [mask, ccnt] = q.front();
    q.pop();

    if (connected(mask)) return cout << ccnt << '\n', 0;
    svis[mask] = true;

    int nmask;
    for (int i = 0; i < n * n; i++) {
      if (!(mask & (1 << i))) continue;
      if (i - n >= 0 && !(mask & (1 << (i - n)))) {
        nmask = mask | (1 << (i - n));
        nmask = nmask & ~(1 << i);
        if (!svis[nmask]) svis[nmask] = true, q.push({nmask, ccnt + 1});
      }
      if (i + n < n * n && !(mask & (1 << (i + n)))) {
        nmask = mask | (1 << (i + n));
        nmask = nmask & ~(1 << i);
        if (!svis[nmask]) svis[nmask] = true, q.push({nmask, ccnt + 1});
      }
      if (i % n != 0 && !(mask & (1 << (i - 1)))) {
        nmask = mask | (1 << (i - 1));
        nmask = nmask & ~(1 << i);
        if (!svis[nmask]) svis[nmask] = true, q.push({nmask, ccnt + 1});
      }
      if (i % n != n - 1 && !(mask & (1 << (i + 1)))) {
        nmask = mask | (1 << (i + 1));
        nmask = nmask & ~(1 << i);
        if (!svis[nmask]) svis[nmask] = true, q.push({nmask, ccnt + 1});
      }
    }
  }
}
