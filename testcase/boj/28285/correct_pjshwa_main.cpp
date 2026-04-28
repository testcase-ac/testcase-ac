#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000;
string T;
int cx, cy, x, y, N, it;

bool move_Q() {
  if (cx <= N) {
    if (cx == 1 || cy == 1) return false;
    cx--; cy--;
  }
  else {
    if (cx == 1) return false;
    cx--;
  }
  T.push_back('Q');
  if (cx == x && cy == y) it = T.size();
  return true;
}

bool move_E() {
  if (cx <= N) {
    if (cx == 1 || cy == N + cx - 1) return false;
    cx--;
  }
  else {
    if (cx == 1) return false;
    cx--; cy++;
  }
  T.push_back('E');
  if (cx == x && cy == y) it = T.size();
  return true;
}

bool move_A() {
  if (cy == 1) return false;
  cy--;
  T.push_back('A');
  if (cx == x && cy == y) it = T.size();
  return true;
}

bool move_D() {
  if (cy == 2 * N - 1 - abs(cx - N)) return false;
  cy++;
  T.push_back('D');
  if (cx == x && cy == y) it = T.size();
  return true;
}

bool move_Z() {
  if (cx < N) {
    cx++;
  }
  else {
    if (cx == 2 * N - 1 || cy == 1) return false;
    cx++; cy--;
  }
  T.push_back('Z');
  if (cx == x && cy == y) it = T.size();
  return true;
}

bool move_C() {
  if (cx < N) {
    cx++; cy++;
  }
  else {
    if (cx == 2 * N - 1 || cy == 2 * N - 1 - abs(cx - N)) return false;
    cx++;
  }
  T.push_back('C');
  if (cx == x && cy == y) it = T.size();
  return true;
}

void solve() {
  cin >> N >> x >> y;

  cx = N, cy = 1;
  while (move_E()) {}
  while (move_D()) {}

  int dir = 1;
  while (cx < 2 * N - 2) {
    if (cy == 2 && dir == 0) {
      if (cx < N) move_Z();
      else move_C();
      dir = 1;
    }
    else if (cy == 2 * N - 1 - abs(cx - N) && dir == 1) {
      if (cx < N) move_C();
      else move_Z();
      dir = 0;
    }
    else {
      if (dir) move_D();
      else move_A();
    }
  }
  assert(cy == 2 * N - 1 - abs(cx - N));
  for (int i = 0; i < N; i++) {
    move_Z();
    move_Q();
  }
  for (int i = 0; i < N - 2; i++) move_Q();

  cout << T.substr(it) + T.substr(0, it) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
