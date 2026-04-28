#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const string U[7] = {
  ".--", "-.", "---", "..", "--..", "--.-", ".-."
};

string S;
void solve() {
  vector<char> ans;

  int i = 0, N = S.size();
  while (i < N) {
    int ok = 0;
    for (int j = 0; j < 7; ++j) {
      if (S.substr(i, U[j].size()) == U[j]) {
        ans.push_back('A' + j);
        i += U[j].size();
        ok = 1;
        break;
      }
    }
    if (!ok) {
      cout << "could not be translated\n";
      return;
    }
  }

  cout << string(ans.begin(), ans.end()) << '\n';
}

int main() {
  fast_io();

  while (cin >> S) solve();
}
