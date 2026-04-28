#include <bits/stdc++.h>
using namespace std;
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100, INF = 0x3f3f3f3f;
int acost[MAX][MAX], bcost[MAX][MAX];
map<string, int> fi;
int fcount;

int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    return fcount++;
  }
  else return found->second;
}

void solve() {
  int N, R;
  cin >> N >> R;
  for (int i = 0; i < N; i++) {
    string S;
    cin >> S;
    fidx(S);
  }

  int M;
  cin >> M;
  vector<int> plans;
  for (int i = 0; i < M; i++) {
    string S;
    cin >> S;
    plans.push_back(fidx(S));
  }

  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    if (i != j) acost[i][j] = bcost[i][j] = INF;
  }

  int K;
  cin >> K;
  while (K--) {
    string W, Si, Ei;
    int price;
    cin >> W >> Si >> Ei >> price;
    int s = fidx(Si), e = fidx(Ei);

    acost[s][e] = min(acost[s][e], 2 * price);
    acost[e][s] = min(acost[e][s], 2 * price);
    if (W == "Mugunghwa" || W == "ITX-Saemaeul" || W == "ITX-Cheongchun") {
      bcost[s][e] = min(bcost[s][e], 0);
      bcost[e][s] = min(bcost[e][s], 0);
    }
    else if (W == "S-Train" || W == "V-Train") {
      bcost[s][e] = min(bcost[s][e], price);
      bcost[e][s] = min(bcost[e][s], price);
    }
    else {
      bcost[s][e] = min(bcost[s][e], 2 * price);
      bcost[e][s] = min(bcost[e][s], 2 * price);
    }
  }

  // Floyd-Warshall
  for (int k = 0; k < N; k++) for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    acost[i][j] = min(acost[i][j], acost[i][k] + acost[k][j]);
    bcost[i][j] = min(bcost[i][j], bcost[i][k] + bcost[k][j]);
  }

  int atotal = 0, btotal = 2 * R;
  for (int i = 0; i < M - 1; i++) {
    int s = plans[i], e = plans[i + 1];
    atotal += acost[s][e];
    btotal += bcost[s][e];
  }

  if (atotal > btotal) cout << "Yes\n";
  else cout << "No\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
