#include <iostream>
using namespace std;

int j(int N, int K) {
    int r = 0;
    for (int i = 2; i <= N; ++i) {
        r = (r + K) % i;
    }
    return r + 1;
}

int main() {
    int N, K;
    cin >> N >> K;
    cout << j(N, K) << endl;
    return 0;
}
