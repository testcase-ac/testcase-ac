#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  cin >> n;
  assert(1 <= n && n <= 100);

  set<string> stu_sub;
  map<string, vector<int>> plc_table;
  int max_sub = 0;
  for (int i = 0; i < n; i++) {
    string name, place;
    int st, et;
    cin >> name >> place >> st >> et;
    assert(1 <= name.size() && name.size() <= 10);
    assert(1 <= place.size() && place.size() <= 20);
    for (char c : name) assert('a' <= c && c <= 'z');
    for (char c : place) assert('a' <= c && c <= 'z');
    assert(1 <= st && st <= 50000);
    assert(st < et && et <= 50000);

    if (stu_sub.count(name)) continue;
    stu_sub.insert(name);

    if (!plc_table.count(place)) plc_table[place] = vector<int>(50001);
    for (int t = st; t < et; t++) max_sub = max(max_sub, ++plc_table[place][t]);
  }
  assert(1 <= plc_table.size() && plc_table.size() <= 10);

  for (auto [place, times] : plc_table) {
    for (int t1 = 0; t1 < 50001; t1++) if (times[t1] == max_sub) {
      int sw = -1;
      for (int t2 = 0; t2 < 50001; t2++) {
        if (sw == -1 && times[t2] == max_sub) sw = t2;
        if (sw != -1 && times[t2] != max_sub) {
          return cout << place << " " << sw << " " << t2 << endl, 0;
        }
      }
    }
  }
}
