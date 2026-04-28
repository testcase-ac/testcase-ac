#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 200;
bool adj[MAX][MAX];

int main() {
  fast_io();

  int n, m, ai, bi;
  cin >> n >> m;
  while (m--) {
    cin >> ai >> bi;
    ai--; bi--;
    adj[ai][bi] = adj[bi][ai] = true;
  }

  int cnt = 0;
  int stk[3], stk_pointer, stsz = 3;
  bool finished;

  // combinations
  stk_pointer = -1;
  stk[0] = 0;

  finished = false;
  while (!finished) {

    for (stk_pointer++; stk_pointer < stsz - 1; stk_pointer++) {
      stk[stk_pointer + 1] = stk[stk_pointer] + 1;
    }

    // stk[0]..stk[stsz - 1] contains the indexes
    // do work here
    if (!adj[stk[0]][stk[1]] && !adj[stk[1]][stk[2]] && !adj[stk[2]][stk[0]]) cnt++;

    do {
      if (stk_pointer == -1) {
        finished = true;
        break;
      }
      stk[stk_pointer--]++;
    } while (stk[stk_pointer + 1] + stsz == n + stk_pointer + 2);
  }

  cout << cnt;
}
