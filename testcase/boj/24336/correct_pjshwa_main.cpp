#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

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
  if (s == "-:-") return -1;

  auto su = split(s, ":");
  return stoi(su[0]) * 60 + stoi(su[1]);
}

double dist[43] = {0.0, 9.1, 23.9, 41.5, 56.5, 66.5, 75.0, 84.4, 96.6, 107.4, 114.9, 129.3, 139.8, 151.9, 166.3, 182.5, 190.8, 196.4, 200.8, 204.6, 211.6, 226.2, 234.7, 253.8, 276.7, 281.3, 289.5, 296.0, 305.9, 323.1, 326.3, 338.6, 353.1, 361.8, 372.2, 381.6, 394.1, 403.2, 412.4, 421.8, 425.2, 430.3, 441.7};
string stations[43] = {"Seoul", "Yeongdeungpo", "Anyang", "Suwon", "Osan", "Seojeongri", "Pyeongtaek", "Seonghwan", "Cheonan", "Sojeongni", "Jeonui", "Jochiwon", "Bugang", "Sintanjin", "Daejeon", "Okcheon", "Iwon", "Jitan", "Simcheon", "Gakgye", "Yeongdong", "Hwanggan", "Chupungnyeong", "Gimcheon", "Gumi", "Sagok", "Yangmok", "Waegwan", "Sindong", "Daegu", "Dongdaegu", "Gyeongsan", "Namseonghyeon", "Cheongdo", "Sangdong", "Miryang", "Samnangjin", "Wondong", "Mulgeum", "Hwamyeong", "Gupo", "Sasang", "Busan"};
vector<tuple<string, int, int>> info;
map<string, double> dist_map;

void solve() {
  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) {
    string ss, sts, ets;
    cin >> ss >> sts >> ets;

    int st = ts2ep(sts), et = ts2ep(ets);
    info.push_back(make_tuple(ss, st, et));
  }

  for (int j = 0; j < 43; j++) dist_map[stations[j]] = dist[j];

  while (q--) {
    string s, e;
    cin >> s >> e;

    double sdist = dist_map[s], edist = dist_map[e];
    double adist = abs(sdist - edist);
    int js, je;
    for (auto& [station, st, et] : info) {
      if (station == s) js = et;
      if (station == e) je = st;
    }
    int elapsed = je - js;
    if (elapsed < 0) elapsed += 1440;

    adist *= 60;
    cout << fixed << setprecision(10) << adist / elapsed << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
