#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

char merge(char a, char b) {
  if (a == 'A') {
    if (b == 'A') return 'A';
    if (b == 'G') return 'C';
    if (b == 'C') return 'A';
    if (b == 'T') return 'G';
  }
  if (a == 'G') {
    if (b == 'A') return 'C';
    if (b == 'G') return 'G';
    if (b == 'C') return 'T';
    if (b == 'T') return 'A';
  }
  if (a == 'C') {
    if (b == 'A') return 'A';
    if (b == 'G') return 'T';
    if (b == 'C') return 'C';
    if (b == 'T') return 'G';
  }
  if (a == 'T') {
    if (b == 'A') return 'G';
    if (b == 'G') return 'A';
    if (b == 'C') return 'G';
    if (b == 'T') return 'T';
  }
}

int main() {
  fast_io();

  int n;
  cin >> n;
  cin.ignore();

  char c;
  cin >> c;
  char qa = merge(c, 'A');
  char qg = merge(c, 'G');
  char qc = merge(c, 'C');
  char qt = merge(c, 'T');
  char pa, pg, pc, pt;

  for (int i = 1; i < n; i++) {
    cin >> c;
    pa = qa, pg = qg, pc = qc, pt = qt;
    qa = merge(c, 'A');
    qg = merge(c, 'G');
    qc = merge(c, 'C');
    qt = merge(c, 'T');

    if (qa == 'A') qa = pa;
    else if (qa == 'G') qa = pg;
    else if (qa == 'C') qa = pc;
    else if (qa == 'T') qa = pt;

    if (qg == 'A') qg = pa;
    else if (qg == 'G') qg = pg;
    else if (qg == 'C') qg = pc;
    else if (qg == 'T') qg = pt;

    if (qc == 'A') qc = pa;
    else if (qc == 'G') qc = pg;
    else if (qc == 'C') qc = pc;
    else if (qc == 'T') qc = pt;

    if (qt == 'A') qt = pa;
    else if (qt == 'G') qt = pg;
    else if (qt == 'C') qt = pc;
    else if (qt == 'T') qt = pt;
  }

  if (c == 'A') cout << qa;
  if (c == 'G') cout << qg;
  if (c == 'C') cout << qc;
  if (c == 'T') cout << qt;
}
