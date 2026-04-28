#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<string> split(const string &str, string delim) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(delim, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delim.size();
  }

  tokens.push_back(str.substr(start));
  return tokens;
}

int ts2ep(string s) {
  auto su = split(s, ":");
  return stoi(su[0]) * 60 + stoi(su[1]);
}

string ep2ts(int ep) {
  int h = (ep / 60) % 24, m = ep % 60;
  stringstream ss;
  ss << setfill('0') << setw(2) << h << ':' << setw(2) << m;
  return ss.str();
}

// All states
// 0: Down train, before start
// 1: Down train, waiting for route 1
// 2: Down train, on route 1
// 3: Down train, waiting for route 2
// 4: Down train, on route 2
// 5: Down train, waiting for route 3
// 6: Down train, on route 3
// 7: Down train, waiting for route 4
// 8: Down train, on route 4
// 9: Down train, arrived

// 10: Up train, before start
// 11: Up train, waiting for route 4
// 12: Up train, on route 4
// 13: Up train, waiting for route 3
// 14: Up train, on route 3
// 15: Up train, waiting for route 2
// 16: Up train, on route 2
// 17: Up train, waiting for route 1
// 18: Up train, on route 1
// 19: Up train, arrived

const int MAX = 40;
const int dwait[5] = {0, 7, 7, 8, 10};
int state[MAX], wait[MAX], tserial[MAX];
int st[MAX], et[MAX];

void solve() {
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++) {
    int tnum; string st_str;
    cin >> tnum >> st_str;

    st[i] = ts2ep(st_str);
    state[i] = 0;
    tserial[i] = tnum;
  }
  for (int i = n; i < n + m; i++) {
    int tnum; string st_str;
    cin >> tnum >> st_str;

    st[i] = ts2ep(st_str);
    state[i] = 10;
    tserial[i] = tnum;
  }
  n += m;

  queue<int> waitd[5], waitu[5];
  for (int t = 0; t < 2880; t++) {
    for (int i = 0; i < n; i++) {
      // cout << "t = " << ep2ts(t) << " i = " << i << " state = " << state[i] << " wait = " << wait[i] << endl;
      if (state[i] == 0 && st[i] == t) state[i] = 1, waitd[1].push(i);
      if (state[i] == 10 && st[i] == t) state[i] = 11, waitu[4].push(i);

      if (state[i] == 3) if (!--wait[i]) waitd[2].push(i);
      if (state[i] == 13) if (!--wait[i]) waitu[3].push(i);

      if (state[i] == 5) if (!--wait[i]) waitd[3].push(i);
      if (state[i] == 15) if (!--wait[i]) waitu[2].push(i);

      if (state[i] == 7) if (!--wait[i]) waitd[4].push(i);
      if (state[i] == 17) if (!--wait[i]) waitu[1].push(i);

      if (state[i] == 2) {
        if (!--wait[i]) state[i] = 3, wait[i] = 1;
      }
      if (state[i] == 12) {
        if (!--wait[i]) state[i] = 13, wait[i] = 1;
      }

      if (state[i] == 4) {
        if (!--wait[i]) state[i] = 5, wait[i] = 1;
      }
      if (state[i] == 14) {
        if (!--wait[i]) state[i] = 15, wait[i] = 1;
      }

      if (state[i] == 6) {
        if (!--wait[i]) state[i] = 7, wait[i] = 1;
      }
      if (state[i] == 16) {
        if (!--wait[i]) state[i] = 17, wait[i] = 1;
      }

      if (state[i] == 8) {
        if (!--wait[i]) state[i] = 9, et[i] = t;
      }
      if (state[i] == 18) {
        if (!--wait[i]) state[i] = 19, et[i] = t;
      }
    }

    for (int c = 1; c <= 4; c++) {
      bool able = true;
      for (int i = 0; i < n; i++) able &= state[i] != 2 * c;
      for (int i = 0; i < n; i++) able &= state[i] != 20 - 2 * c;
      if (!able) continue;

      if (waitd[c].size() && waitu[c].empty()) {
        int i = waitd[c].front();
        waitd[c].pop();
        state[i] = 2 * c, wait[i] = dwait[c];
      }
      else if (waitd[c].empty() && waitu[c].size()) {
        int i = waitu[c].front();
        waitu[c].pop();
        state[i] = 20 - 2 * c, wait[i] = dwait[c];
      }
      else if (waitd[c].size() && waitu[c].size()) {
        int i = waitd[c].front(), j = waitu[c].front();
        if (st[i] < st[j]) {
          waitd[c].pop();
          state[i] = 2 * c, wait[i] = dwait[c];
        }
        else if (st[i] > st[j]) {
          waitu[c].pop();
          state[j] = 20 - 2 * c, wait[j] = dwait[c];
        }
        else {
          if (tserial[i] < tserial[j]) {
            waitd[c].pop();
            state[i] = 2 * c, wait[i] = dwait[c];
          }
          else {
            waitu[c].pop();
            state[j] = 20 - 2 * c, wait[j] = dwait[c];
          }
        }
      }

    }


  }

  vector<pii> o;
  for (int i = 0; i < n; i++) o.push_back({tserial[i], i});
  sort(o.begin(), o.end());

  for (int i = 0; i < n; i++) cout << ep2ts(et[o[i].second]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
