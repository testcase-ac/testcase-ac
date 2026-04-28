// https://ryute.tistory.com/36?category=735347

#include <bits/stdc++.h>
#include <random>
 
using namespace std;
int n;
int grid[40][40];
 
void turn(int x, int y) { 
  if (y == 0) {
    for (int i = 0; i < n; i++)
      grid[x][i] = 1 - grid[x][i];
  }
  else {
    for (int i = 0; i < n; i++)
      grid[i][x] = 1 - grid[i][x];
  }
}
 
void func() {
  for (int i = 0; i < n; i++) {
    int s = 0;
    for (int j = 0; j < n; j++)
      s += grid[j][i];
    if (s > (n / 2)) turn(i, 1);
  }
}
 
int scoring() {
  int s = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      s += grid[i][j];
  return s;
}
 
double t=1, d=0.9999, k=10, lim=0.0005;
std::mt19937_64 seed(1919);
std::uniform_real_distribution<double> rng(0, 1);
 
int ret = 999;
 
void simulated_annealing() {
  double e1, e2;
  int ori[40][40];
  while (t > lim) {
    e1 = scoring();
    for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) ori[i][j] = grid[i][j];
    int pos = rand() % n;
    turn(pos, 0);
    func();
    e2 = scoring();
 
    double p = exp((e1 - e2) / (k*t));
    if (p < rng(seed)) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) grid[i][j] = ori[i][j];
    t *= d;
 
    ret = min(ret, scoring());
  }
}

int main() {
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      char ch;
      scanf(" %c", &ch);
      grid[i][j] = (ch == 'H' ? 0 : 1);
    }
  }
  simulated_annealing();
  printf("%d", ret);
  return 0;
}
