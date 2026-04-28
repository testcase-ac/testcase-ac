#include <bits/stdc++.h>
using namespace std;
using ll = long long;

vector<int> ask(vector<int>& Q) {
  cout << "? " << Q.size();
  for (int& q : Q) cout << ' ' << q;
  cout << endl;

  int K; cin >> K; vector<int> A(K);
  for (int i = 0; i < K; ++i) cin >> A[i];
  return A;
}

int main() {
  int N; cin >> N;
  vector<int> P;
  for (int i = 1; i <= N; ++i) {
    P.push_back(i);
    P.push_back(i);
  }
  reverse(P.begin(), P.end());

  vector<int> L;
  while (!P.empty()) {
    vector<int> Q;
    while (!P.empty() && Q.size() < N) Q.push_back(P.back()), P.pop_back();
    auto A = ask(Q);
    for (int& a : A) L.push_back(a);
  }

  cout << "! "; int i = 0, j = 1;
  for (int t = 1; t <= N; ++t) {
    while (L[i] != L[j]) ++j;
    cout << j - i << ' ';
    for (int l = i; l < j; ++l) cout << L[l] << ' ';
    i = 2 * j - i; j = i + 1;
  }
  cout << endl;
}
