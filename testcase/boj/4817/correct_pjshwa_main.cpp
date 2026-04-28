#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_alpha(char c) {
  return 'a' <= c && c <= 'z';
}

string S;
void solve() {
  int N = S.size();
  string ans = S;

  stack<pair<int, bool>> O;
  for (int i = 0; i < N; ++i) {
    char c = S[i];
    if (c == '(') O.push({i, false});
    else if (c == ')') {
      auto [li, has_plus] = O.top(); O.pop();
      bool dup_brac = i < N - 1 && S[i + 1] == ')';
      dup_brac &= li > 0 && S[li - 1] == '(';
      if (dup_brac) {
        ans[li] = ans[i] = ' ';
        if (!O.empty()) O.top().second = has_plus;
        continue;
      }

      bool adj_mul = li > 0 && (is_alpha(S[li - 1]) || S[li - 1] == ')');
      adj_mul |= i < N - 1 && (is_alpha(S[i + 1]) || S[i + 1] == '(');
      if (!has_plus || !adj_mul) ans[li] = ans[i] = ' ';
    }
    else if (!O.empty()) {
      if (c == '+') O.top().second = true;
    }
  }

  for (char& c : ans) {
    if (c == ' ') continue;
    cout << c;
  }
  cout << '\n';
}

int main() {
  fast_io();

  while (cin >> S) solve();
}
