#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int op2int(char op) {
  if (op == '+') return 0;
  if (op == '-') return 1;
  if (op == '*') return 2;
  if (op == '/') return 3;
  return -1;
}

ll calc(ll a, ll b, int op) {
  if (op == 0) return a + b;
  if (op == 1) return a - b;
  if (op == 2) return a * b;
  if (op == 3) return a / b;
  return -1;
}

void solve() {
  string S; cin >> S;
  deque<ll> dq; int N = S.size(), i = 0;
  if (S[0] == '-') {
    ll num = 0; ++i;
    while (i < N && isdigit(S[i])) {
      num = num * 10 + S[i] - '0';
      ++i;
    }
    dq.push_back(-num);
    if (i < N) dq.push_back(op2int(S[i++]));
  }

  while (i < N) {
    ll num = 0;
    while (i < N && isdigit(S[i])) {
      num = num * 10 + S[i] - '0';
      ++i;
    }
    dq.push_back(num);
    if (i < N) dq.push_back(op2int(S[i++]));
    else break;
  }
  assert(dq.size() % 2 == 1);

  auto calc_front = [&](int dry) {
    ll a = dq[0], op = dq[1], b = dq[2];
    ll ret = calc(a, b, op);
    if (!dry) {
      dq.pop_front(); dq.pop_front(); dq.pop_front();
      dq.push_front(ret);
    }
    return ret;
  };
  auto calc_back = [&](int dry) {
    ll a = dq[dq.size() - 3], op = dq[dq.size() - 2], b = dq[dq.size() - 1];
    ll ret = calc(a, b, op);
    if (!dry) {
      dq.pop_back(); dq.pop_back(); dq.pop_back();
      dq.push_back(ret);
    }
    return ret;
  };

  while (dq.size() > 3) {
    int op_f = dq[1], op_b = dq[dq.size() - 2];
    if ((op_f ^ op_b) & 2) {
      if (op_f & 2) calc_front(0);
      else if (op_b & 2) calc_back(0);
      else assert(false);
    } else {
      ll val_f = calc_front(1), val_b = calc_back(1);
      if (val_b > val_f) calc_back(0);
      else calc_front(0);
    }
  }
  if (dq.size() == 3) calc_front(0);

  cout << dq.front() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
