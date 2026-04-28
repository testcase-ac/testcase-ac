#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000, MAXV = 120;
const int B[7] = {0, 2, 4, 5, 7, 9, 11};
const char C[7] = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};
int notes[MAXN], dp[MAXN][MAXV][MAXV], N;

int rec(int i, int l, int r) {
  if (i == N) return 0;
  if (dp[i][l][r] != -1) return dp[i][l][r];

  int c = notes[i], ret = 0x3f3f3f3f;
  ret = min(ret, rec(i + 1, c, r) + abs(l - c));
  ret = min(ret, rec(i + 1, l, c) + abs(r - c));
  return dp[i][l][r] = ret;
}

void trace(int i, int l, int r) {
  if (i == N) return;
  int c = notes[i], ret = rec(i, l, r);
  if (ret == rec(i + 1, c, r) + abs(l - c)) {
    cout << "1 ";
    trace(i + 1, c, r);
  } else {
    cout << "2 ";
    trace(i + 1, l, c);
  }
}

int parse_note(string note) {
  int L = note[1] - '0', Bi;
  for (Bi = 0; Bi < 8; ++Bi) {
    if (note[0] == C[Bi]) break;
  }
  int ret = L * 12 + B[Bi];
  if (note.back() == '#') ++ret;
  return ret;
}

void solve() {
  string Ls, Rs; cin >> Ls >> Rs >> N;
  int L = parse_note(Ls), R = parse_note(Rs);
  for (int i = 0; i < N; ++i) {
    string note; cin >> note;
    notes[i] = parse_note(note);
  }
  memset(dp, -1, sizeof(dp));
  cout << rec(0, L, R) << '\n';
  trace(0, L, R);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
