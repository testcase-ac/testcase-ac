// Copyright 2020 <jehan.yoon>
#include <cstdio>

inline void ioInit(void) {
#ifdef JH_DEBUG
  freopen("9466_input.txt", "rt", stdin);
#endif
}

#include <algorithm>
namespace fio {
  constexpr size_t BUF_SIZ = 0x8'0000, SPARE = 20;
  char buf_i[BUF_SIZ], *p_in = buf_i, *p_max = p_in;

  inline char getCh(void) {
    if (p_in == p_max) {
      p_max = buf_i + fread(buf_i, 1, BUF_SIZ, stdin);
      p_in = buf_i;
    }
    return *(p_in++);
  }

  template<typename T>
  inline int get(void) {
    int t, sign = 1;
    T r = 0;
    do {
      t = getCh();
    } while (t != '-' && (t < '0' || t > '9'));
    if (t == '-')  sign = -1, t = getCh();
    while (true) {
      r = r * 10 + t - '0'; t = getCh();
      if (t < '0' || t > '9')    break;
    }
    return r * sign;
  }

  char buf_o[BUF_SIZ + SPARE], *p_out = buf_o;

  template<typename T>
  void prt(T n, char delim = ' ') {
    if (n < 0) n = -n, *p_out++ = '-';
    char *ptr = p_out;
    do { *ptr++ = n % 10 + '0';  n /= 10; } while (n);
    std::reverse(p_out, ptr);
    *ptr++ = delim;
    if (ptr < buf_o + BUF_SIZ) {
      p_out = ptr;
    } else {
      fwrite(buf_o, ptr - buf_o, 1, stdout); p_out = buf_o;
    }
  }

  inline void prtn(void) {
    *p_out++ = '\n';
    if (p_out >= buf_o + BUF_SIZ)
    { fwrite(buf_o, p_out - buf_o, 1, stdout); p_out = buf_o; }
  }

  void flush(void) {
    fwrite(buf_o, p_out - buf_o, 1, stdout);
    p_out = buf_o;
  }
};  // namespace fio
///////////////////////////

///////////////////////////
// #include <vector>
// using std::vector;
constexpr int MAXN = 100'001;
int N, pair[MAXN];
int visited[MAXN];

void readData(void) {
  N = fio::get<int>();
  for (int n = 1; n <= N; n++) {
    pair[n] = fio::get<int>();
    visited[n] = 0;
  }
}

int countUnpaired(void) {
  int cnt = 0, turn = 0;
  for (int n = 1; n <= N; n++) {
    if (visited[n] != 0)  continue;
    turn++;

    int buddy = n;
    while (visited[buddy] == 0) {
      visited[buddy] = turn;
      cnt++;
      buddy = pair[buddy];
    }
    if (visited[buddy] == turn) {
      cnt--;
      for (int member = pair[buddy]; member != buddy; member = pair[member]) {
        cnt--;
      }
    }
  }

  return cnt;
}

int main(void) {
  ioInit();

  int T;
  scanf("%d", &T);
  while (T--) {
    readData();
    fio::prt(countUnpaired(), '\n');
  }
  fio::flush();

  return 0;
}
