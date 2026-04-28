#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n;
char a[6][7];
char o[6][7] = {
  "abcdef",
  "ghijkl",
  "mnopqr",
  "stuvwx",
  "yz0123",
  "456789"
};
vector<tuple<int, char, int>> ops;

void rotate_right(int i, int c) {
  char b[n];
  for (int k = 0; k < n; k++) b[(k + c) % n] = a[i][k];
  for (int k = 0; k < n; k++) a[i][k] = b[k];
  ops.push_back(make_tuple(i + 1, 'R', c));
}

void rotate_left(int i, int c) {
  rotate_right(i, n - c);
}

void rotate_down(int j, int c) {
  char b[n];
  for (int k = 0; k < n; k++) b[(k + c) % n] = a[k][j];
  for (int k = 0; k < n; k++) a[k][j] = b[k];
  ops.push_back(make_tuple(j + 1, 'D', c));
}

void rotate_up(int j, int c) {
  rotate_down(j, n - c);
}

void swap_right(int i, int j) {
  rotate_up(j, 1);
  for (int k = 0; k < 3; k++) {
    rotate_left(i, 1);
    rotate_up(j, 1);
    rotate_right(i, 1);
    rotate_up(j, 1);
  }
}

void print_board() {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) cout << a[i][j];
    cout << endl;
  }
}

int main() {
  fast_io();

  n = 6;
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int i = 0; i < n - 1; i++) for (int j = 0; j < n; j++) {
    if (a[i][j] == o[i][j]) continue;

    bool set = false;
    for (int k = j + 1; k < n; k++) {
      if (a[i][k] == o[i][j]) {
        rotate_down(j, 1);
        rotate_down(k, 1);
        rotate_left(i + 1, k - j);
        rotate_up(j, 1);
        rotate_up(k, 1);
        set = true;
        break;
      }
    }
    if (set) continue;

    for (int ri = i + 1; ri < n; ri++) {
      for (int ci = 0; ci < n; ci++) {
        if (a[ri][ci] == o[i][j]) {
          if (ci == j) {
            rotate_right(ri, 1);
            rotate_down(j, ri - i);
            rotate_left(ri, 1);
            rotate_up(j, ri - i);
          }
          else {
            rotate_down(j, ri - i);
            if (ci < j) rotate_right(ri, j - ci);
            else rotate_left(ri, ci - j);
            rotate_up(j, ri - i);
          }
          set = true;
          break;
        }
      }
      if (set) break;
    }
  }

  for (int k = 0; k < n; k++) {
    for (int l = 0; l < n - k - 1; l++) {
      if (a[n - 1][l] > a[n - 1][l + 1]) swap_right(n - 1, l);
    }
  }

  // print_board();

  for (auto t : ops) cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n';
}
