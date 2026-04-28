#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int main() {
  int m_sq_sum[50001];
  memset(m_sq_sum, 4, sizeof(m_sq_sum));

  m_sq_sum[0] = 0;
  for (int i = 1; i * i <= 50000; i++) {
    m_sq_sum[i * i] = 1;
  }

  for (int i = 2; i <= 50000; i++) {
    for (int j = 1; j * j <= i; j++) {
      m_sq_sum[i] = min(m_sq_sum[i], m_sq_sum[j * j] + m_sq_sum[i - j * j]);
    }
  }

  int n;
  cin >> n;
  cout << m_sq_sum[n] << '\n';
}
