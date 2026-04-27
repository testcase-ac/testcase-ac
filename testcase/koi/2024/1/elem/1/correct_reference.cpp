#include <iostream>

using namespace std;

using ll = long long;

int N, X;

int main() {
    cin >> N >> X;

    int ans = -1;
    for(int i=1;i<=N;i++) {
        int S, T; cin >> S >> T;
        if(S+T <= X) ans = max(ans, S);
    }
    cout << ans << "\n";
}
