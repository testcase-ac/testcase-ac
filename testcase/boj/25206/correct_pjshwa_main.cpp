#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

double grad2score(string grad) {
  if (grad == "A+") return 4.5;
  if (grad == "A0") return 4.0;
  if (grad == "B+") return 3.5;
  if (grad == "B0") return 3.0;
  if (grad == "C+") return 2.5;
  if (grad == "C0") return 2.0;
  if (grad == "D+") return 1.5;
  if (grad == "D0") return 1.0;
  if (grad == "F") return 0.0;
}

void solve() {
  double tcred = 0, tscore = 0;
  for (int i = 1; i <= 20; i++) {
    string subj, grad;
    double cred;
    cin >> subj >> cred >> grad;
    if (grad == "P") continue;

    tcred += cred;
    tscore += cred * grad2score(grad);
  }

  cout << fixed << setprecision(10) << tscore / tcred << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
