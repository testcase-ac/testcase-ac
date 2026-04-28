#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

queue<int> mpf[1001];
int wpf[1001][1001], wmatch[1001];
bool wfree[1001];
int n;

unordered_map<string, int> fmi, fwi;
int fm_count, fw_count;

int fm_index(string f) {
  auto found = fmi.find(f);
  if (fmi.end() == found) {
    fmi.insert({f, ++fm_count});
    return fm_count;
  }
  else return found->second;
}

int fw_index(string f) {
  auto found = fwi.find(f);
  if (fwi.end() == found) {
    fwi.insert({f, ++fw_count});
    return fw_count;
  }
  else return found->second;
}

bool wPrefersm1Tom2(int w, int m1, int m2) {
  int m1i = -1, m2i = -1;
  for (int i = 1; i <= n; i++) {
    if (wpf[w][i] == m1) m1i = i;
    if (wpf[w][i] == m2) m2i = i;
  }
  return m1i < m2i;
}

int main() {
  fast_io();

  cin >> n;
  string fm, fw;
  for (int i = 1; i <= n; i++) {
    cin >> fm;
    fm_index(fm);
  }
  for (int i = 1; i <= n; i++) {
    cin >> fw;
    fw_index(fw);
  }

  for (int i = 1; i <= n; i++) {
    cin >> fm;
    int fmi = fm_index(fm);
    for (int j = 1; j <= n; j++) {
      cin >> fw;
      int fwi = fw_index(fw);
      mpf[fmi].push(fwi);
    }
  }

  for (int i = 1; i <= n; i++) {
    cin >> fw;
    int fwi = fw_index(fw);
    for (int j = 1; j <= n; j++) {
      cin >> fm;
      int fmi = fm_index(fm);
      wpf[fwi][j] = fmi;
    }
  }
  for (int i = 1; i <= n; i++) wfree[i] = true;

  queue<int> mq;
  for (int i = 1; i <= n; i++) mq.push(i);

  while (!mq.empty()) {
    int cm = mq.front();
    mq.pop();

    int cw = mpf[cm].front();
    mpf[cm].pop();

    if (wfree[cw]) {
      wmatch[cw] = cm;
      wfree[cw] = false;
    }
    else {
      if (wPrefersm1Tom2(cw, cm, wmatch[cw])) {
        mq.push(wmatch[cw]);
        wmatch[cw] = cm;
      }
      else mq.push(cm);
    }
  }

  for (auto [fwn, fwii] : fwi) {
    for (auto [fmn, fmii] : fmi) {
      if (wmatch[fwii] == fmii) cout << fmn << ' ' << fwn << '\n';
    }
  }
}
