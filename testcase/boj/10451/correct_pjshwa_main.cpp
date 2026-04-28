#include <iostream>
#include <cstring>
using namespace std;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  FastIO();
  int t; cin >> t;
  int n, cnt, j, start; int a[1000]; bool visited[1000];

  while (t--) {
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i];
    memset(visited, false, sizeof(bool) * n);

    cnt = 0;
    for(int i = 0; i < n; i++) {
      j = i;
      if (!visited[j]) {
        cnt++;
        start = j;
        visited[j] = true;
        j = a[j] - 1;
        while (j != start) {
          visited[j] = true;
          j = a[j] - 1;
        }
      }
    }

    cout << cnt << '\n';
  }
}
