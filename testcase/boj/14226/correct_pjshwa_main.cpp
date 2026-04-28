#include <bits/stdc++.h>
#define tii tuple<int, int, int> // num, clip, order
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool visited[2001][2001];
int main() {
  fast_io();

  int s;
  cin >> s;
  queue<tii> q;
  q.push({1, 0, 0});

  int num, clip, order;
  while (!q.empty()) {
    tie(num, clip, order) = q.front();
    q.pop();
    visited[num][clip] = true;

    if (num == s) {
      cout << order << '\n';
      break;
    }

    if (num < s && !visited[num + clip][clip]) q.push({num + clip, clip, order + 1});
    if (clip != num && !visited[num][num]) q.push({num, num, order + 1});
    if (num && !visited[num - 1][clip]) q.push({num - 1, clip, order + 1});
  }
}
