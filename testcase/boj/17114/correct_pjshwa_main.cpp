# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")

#include <vector>
#include <tuple>
#include <queue>
#define t11 tuple<int, int, int, int, int, int, int, int, int, int, int>
#include <stdio.h>
#include <string.h>
#define __BUFSIZE 2097152
#define __BLANK(c) (c == ' ' \
					|| c == '\n' \
					|| c == '\t' \
					|| c == '\v' \
					|| c == '\f' \
					|| c == '\r')
#define __ENDL(c) (c == '\n')
#define __END(c) (c == '\0')

char __RBUF[__BUFSIZE], __WBUF[__BUFSIZE];
int __RIDX, __NIDX, __WIDX, __END_FLAG;

inline char readChar(){
	if (__RIDX == __NIDX){
		__NIDX = fread(__RBUF, sizeof(char), __BUFSIZE, stdin);
		if (__NIDX == 0){
			__END_FLAG = 1;
			return 0;
		}
		__RIDX = 0;
	}
	return __RBUF[__RIDX ++];
}

inline int readInt(){
	int res = 0;
	char cur = readChar();
	int flag = 0;

	while (__BLANK(cur))
		cur = readChar();

	if (cur == '-'){
		flag = 1;
		cur = readChar();
	}

	while (!__BLANK(cur) && !__END(cur)){
		res = 10 * res + cur - '0';
		cur = readChar();
	}

	return flag ? -res : res;
}

static inline int uintSize(int n){
	int isz = 1;
	if (n < 0) n = -n;

	while (n >= 10){
		isz ++;
		n /= 10;
	}

	return isz;
}

inline void bflush(){
	fwrite(__WBUF, sizeof(char), __WIDX, stdout);
	__WIDX = 0;
}

inline void writeInt(int n){
	int isz = uintSize(n);
	if (__WIDX + isz >= __BUFSIZE){
		bflush();
	}
	if (n < 0){
		n = -n;
		__WBUF[__WIDX ++] = '-';
	}
	int next = __WIDX + isz;

	while (isz --){
		__WBUF[__WIDX + isz] = n % 10 + '0';
		n /= 10;
	}
	__WIDX = next;
}

using namespace std;

int main() {
  int m, n, o, p, q, r, s, t, u, v, w;
  int mv = 0, utomato = 0;

  m = readInt();
  n = readInt();
  o = readInt();
  p = readInt();
  q = readInt();
  r = readInt();
  s = readInt();
  t = readInt();
  u = readInt();
  v = readInt();
  w = readInt();

  int farm[w][v][u][t][s][r][q][p][o][n][m];

  for (int wi = 0; wi < w; wi++) for (int vi = 0; vi < v; vi++) for (int ui = 0; ui < u; ui++) 
  for (int ti = 0; ti < t; ti++) for (int si = 0; si < s; si++) for (int ri = 0; ri < r; ri++) 
  for (int qi = 0; qi < q; qi++) for (int pi = 0; pi < p; pi++) for (int oi = 0; oi < o; oi++) 
  for (int ni = 0; ni < n; ni++) for (int mi = 0; mi < m; mi++) {
    farm[wi][vi][ui][ti][si][ri][qi][pi][oi][ni][mi] = readInt();
    if (!farm[wi][vi][ui][ti][si][ri][qi][pi][oi][ni][mi]) utomato++;
  }

  queue<pair<t11, int>> qt;
  for (int mi = 0; mi < m; mi++) for (int ni = 0; ni < n; ni++) for (int oi = 0; oi < o; oi++) 
  for (int pi = 0; pi < p; pi++) for (int qi = 0; qi < q; qi++) for (int ri = 0; ri < r; ri++) 
  for (int si = 0; si < s; si++) for (int ti = 0; ti < t; ti++) for (int ui = 0; ui < u; ui++) 
  for (int vi = 0; vi < v; vi++) for (int wi = 0; wi < w; wi++) {
    if (farm[wi][vi][ui][ti][si][ri][qi][pi][oi][ni][mi] == 1)
      qt.push({{wi, vi, ui, ti, si, ri, qi, pi, oi, ni, mi}, 0});
  }

  while (!qt.empty()) {
    auto[pt, it] = qt.front();
    auto[wi, vi, ui, ti, si, ri, qi, pi, oi, ni, mi] = pt;
    mv = max(mv, it);
    qt.pop();

    if (mi > 0 && farm[wi][vi][ui][ti][si][ri][qi][pi][oi][ni][mi - 1] == 0) {
      utomato--;
      farm[wi][vi][ui][ti][si][ri][qi][pi][oi][ni][mi - 1] = 1;
      qt.push({{wi, vi, ui, ti, si, ri, qi, pi, oi, ni, mi - 1}, it + 1});
    }
    if (ni > 0 && farm[wi][vi][ui][ti][si][ri][qi][pi][oi][ni - 1][mi] == 0) {
      utomato--;
      farm[wi][vi][ui][ti][si][ri][qi][pi][oi][ni - 1][mi] = 1;
      qt.push({{wi, vi, ui, ti, si, ri, qi, pi, oi, ni - 1, mi}, it + 1});
    }
    if (oi > 0 && farm[wi][vi][ui][ti][si][ri][qi][pi][oi - 1][ni][mi] == 0) {
      utomato--;
      farm[wi][vi][ui][ti][si][ri][qi][pi][oi - 1][ni][mi] = 1;
      qt.push({{wi, vi, ui, ti, si, ri, qi, pi, oi - 1, ni, mi}, it + 1});
    }
    if (pi > 0 && farm[wi][vi][ui][ti][si][ri][qi][pi - 1][oi][ni][mi] == 0) {
      utomato--;
      farm[wi][vi][ui][ti][si][ri][qi][pi - 1][oi][ni][mi] = 1;
      qt.push({{wi, vi, ui, ti, si, ri, qi, pi - 1, oi, ni, mi}, it + 1});
    }
    if (qi > 0 && farm[wi][vi][ui][ti][si][ri][qi - 1][pi][oi][ni][mi] == 0) {
      utomato--;
      farm[wi][vi][ui][ti][si][ri][qi - 1][pi][oi][ni][mi] = 1;
      qt.push({{wi, vi, ui, ti, si, ri, qi - 1, pi, oi, ni, mi}, it + 1});
    }
    if (ri > 0 && farm[wi][vi][ui][ti][si][ri - 1][qi][pi][oi][ni][mi] == 0) {
      utomato--;
      farm[wi][vi][ui][ti][si][ri - 1][qi][pi][oi][ni][mi] = 1;
      qt.push({{wi, vi, ui, ti, si, ri - 1, qi, pi, oi, ni, mi}, it + 1});
    }
    if (si > 0 && farm[wi][vi][ui][ti][si - 1][ri][qi][pi][oi][ni][mi] == 0) {
      utomato--;
      farm[wi][vi][ui][ti][si - 1][ri][qi][pi][oi][ni][mi] = 1;
      qt.push({{wi, vi, ui, ti, si - 1, ri, qi, pi, oi, ni, mi}, it + 1});
    }
    if (ti > 0 && farm[wi][vi][ui][ti - 1][si][ri][qi][pi][oi][ni][mi] == 0) {
      utomato--;
      farm[wi][vi][ui][ti - 1][si][ri][qi][pi][oi][ni][mi] = 1;
      qt.push({{wi, vi, ui, ti - 1, si, ri, qi, pi, oi, ni, mi}, it + 1});
    }
    if (ui > 0 && farm[wi][vi][ui - 1][ti][si][ri][qi][pi][oi][ni][mi] == 0) {
      utomato--;
      farm[wi][vi][ui - 1][ti][si][ri][qi][pi][oi][ni][mi] = 1;
      qt.push({{wi, vi, ui - 1, ti, si, ri, qi, pi, oi, ni, mi}, it + 1});
    }
    if (vi > 0 && farm[wi][vi - 1][ui][ti][si][ri][qi][pi][oi][ni][mi] == 0) {
      utomato--;
      farm[wi][vi - 1][ui][ti][si][ri][qi][pi][oi][ni][mi] = 1;
      qt.push({{wi, vi - 1, ui, ti, si, ri, qi, pi, oi, ni, mi}, it + 1});
    }
    if (wi > 0 && farm[wi - 1][vi][ui][ti][si][ri][qi][pi][oi][ni][mi] == 0) {
      utomato--;
      farm[wi - 1][vi][ui][ti][si][ri][qi][pi][oi][ni][mi] = 1;
      qt.push({{wi - 1, vi, ui, ti, si, ri, qi, pi, oi, ni, mi}, it + 1});
    }

    if (mi < m - 1 && farm[wi][vi][ui][ti][si][ri][qi][pi][oi][ni][mi + 1] == 0) {
      utomato--;
      farm[wi][vi][ui][ti][si][ri][qi][pi][oi][ni][mi + 1] = 1;
      qt.push({{wi, vi, ui, ti, si, ri, qi, pi, oi, ni, mi + 1}, it + 1});
    }
    if (ni < n - 1 && farm[wi][vi][ui][ti][si][ri][qi][pi][oi][ni + 1][mi] == 0) {
      utomato--;
      farm[wi][vi][ui][ti][si][ri][qi][pi][oi][ni + 1][mi] = 1;
      qt.push({{wi, vi, ui, ti, si, ri, qi, pi, oi, ni + 1, mi}, it + 1});
    }
    if (oi < o - 1 && farm[wi][vi][ui][ti][si][ri][qi][pi][oi + 1][ni][mi] == 0) {
      utomato--;
      farm[wi][vi][ui][ti][si][ri][qi][pi][oi + 1][ni][mi] = 1;
      qt.push({{wi, vi, ui, ti, si, ri, qi, pi, oi + 1, ni, mi}, it + 1});
    }
    if (pi < p - 1 && farm[wi][vi][ui][ti][si][ri][qi][pi + 1][oi][ni][mi] == 0) {
      utomato--;
      farm[wi][vi][ui][ti][si][ri][qi][pi + 1][oi][ni][mi] = 1;
      qt.push({{wi, vi, ui, ti, si, ri, qi, pi + 1, oi, ni, mi}, it + 1});
    }
    if (qi < q - 1 && farm[wi][vi][ui][ti][si][ri][qi + 1][pi][oi][ni][mi] == 0) {
      utomato--;
      farm[wi][vi][ui][ti][si][ri][qi + 1][pi][oi][ni][mi] = 1;
      qt.push({{wi, vi, ui, ti, si, ri, qi + 1, pi, oi, ni, mi}, it + 1});
    }
    if (ri < r - 1 && farm[wi][vi][ui][ti][si][ri + 1][qi][pi][oi][ni][mi] == 0) {
      utomato--;
      farm[wi][vi][ui][ti][si][ri + 1][qi][pi][oi][ni][mi] = 1;
      qt.push({{wi, vi, ui, ti, si, ri + 1, qi, pi, oi, ni, mi}, it + 1});
    }
    if (si < s - 1 && farm[wi][vi][ui][ti][si + 1][ri][qi][pi][oi][ni][mi] == 0) {
      utomato--;
      farm[wi][vi][ui][ti][si + 1][ri][qi][pi][oi][ni][mi] = 1;
      qt.push({{wi, vi, ui, ti, si + 1, ri, qi, pi, oi, ni, mi}, it + 1});
    }
    if (ti < t - 1 && farm[wi][vi][ui][ti + 1][si][ri][qi][pi][oi][ni][mi] == 0) {
      utomato--;
      farm[wi][vi][ui][ti + 1][si][ri][qi][pi][oi][ni][mi] = 1;
      qt.push({{wi, vi, ui, ti + 1, si, ri, qi, pi, oi, ni, mi}, it + 1});
    }
    if (ui < u - 1 && farm[wi][vi][ui + 1][ti][si][ri][qi][pi][oi][ni][mi] == 0) {
      utomato--;
      farm[wi][vi][ui + 1][ti][si][ri][qi][pi][oi][ni][mi] = 1;
      qt.push({{wi, vi, ui + 1, ti, si, ri, qi, pi, oi, ni, mi}, it + 1});
    }
    if (vi < v - 1 && farm[wi][vi + 1][ui][ti][si][ri][qi][pi][oi][ni][mi] == 0) {
      utomato--;
      farm[wi][vi + 1][ui][ti][si][ri][qi][pi][oi][ni][mi] = 1;
      qt.push({{wi, vi + 1, ui, ti, si, ri, qi, pi, oi, ni, mi}, it + 1});
    }
    if (wi < w - 1 && farm[wi + 1][vi][ui][ti][si][ri][qi][pi][oi][ni][mi] == 0) {
      utomato--;
      farm[wi + 1][vi][ui][ti][si][ri][qi][pi][oi][ni][mi] = 1;
      qt.push({{wi + 1, vi, ui, ti, si, ri, qi, pi, oi, ni, mi}, it + 1});
    }

  }

  writeInt(utomato ? -1 : mv);
  bflush();
}
