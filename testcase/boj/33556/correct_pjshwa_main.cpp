#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string equals(string& A, string& B) {
  if (A == "null") return "NullPointerException";
  if (B == "null") return "false";
  if (A.size() != B.size()) return "false";
  for (int i = 0; i < (int)A.size(); i++) {
    if (A[i] != B[i]) return "false";
  }
  return "true";
}

string equalsIgnoreCase(string& A, string& B) {
  if (A == "null") return "NullPointerException";
  if (B == "null") return "false";
  if (A.size() != B.size()) return "false";
  for (int i = 0; i < (int)A.size(); i++) {
    if (tolower(A[i]) != tolower(B[i])) return "false";
  }
  return "true";
}

void solve() {
  string A, B; cin >> A >> B;
  cout << equals(A, B) << '\n';
  cout << equalsIgnoreCase(A, B) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
