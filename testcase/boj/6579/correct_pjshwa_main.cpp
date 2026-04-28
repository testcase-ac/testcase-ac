#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool isop(char c) {
  return c == '+' || c == '-' || c == '*';
}

int opid(char c) {
  if (c == '+') return -1;
  if (c == '-') return -2;
  if (c == '*') return -3;

  assert(false);
  return -4;
}

int evaluate(string S) {
  int N = S.size(), cur = 0; vector<int> st;

  // Handle '(' and ')'
  for (int i = 0; i < N; ++i) {
    if (S[i] == '(') {
      int r = i;
      stack<int> st_p;
      while (r < N) {
        if (S[r] == '(') st_p.push(1);
        else if (S[r] == ')') {
          st_p.pop();
          if (st_p.empty()) break;
        }
        ++r;
      }
      cur = evaluate(S.substr(i + 1, r - i - 1));
      st.push_back(cur);
      i = r;
    }
    else if (S[i] == '{') cur = 0;
    else if (S[i] == '}') st.push_back(cur);
    else if (isalpha(S[i])) cur |= 1 << (S[i] - 'A');
    else if (isop(S[i])) st.push_back(opid(S[i]));
    else assert(false);
  }

  // cout << "st = ";
  // for (int e : st) cout << e << ' ';
  // cout << '\n';

  // Handle '*'
  vector<int> st2;
  for (int e : st) {
    if (!st2.empty() && st2.back() == -3) {
      st2.pop_back();
      int f = st2.back(); st2.pop_back();
      st2.push_back(f & e);
    }
    else st2.push_back(e);
  }

  // cout << "st2 = ";
  // for (int e : st2) cout << e << ' ';
  // cout << '\n';

  // Handle '+', '-'
  int val = st2[0], Z = st2.size(); assert(Z & 1);
  for (int i = 1; i < Z; i += 2) {
    int op = st2[i], next = st2[i + 1];
    if (op == -1) val |= next;
    else if (op == -2) val -= (val & next);
    else assert(false);
  }

  return val;
}

string S;
void solve() {
  int val = evaluate(S);

  cout << "{";
  for (int i = 0; i < 26; ++i) {
    if (val & (1 << i)) cout << (char)('A' + i);
  }
  cout << "}\n";
}

int main() {
  fast_io();

  while (cin >> S) solve();
}
