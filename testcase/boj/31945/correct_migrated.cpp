#include <iostream>
using namespace std;
int T, P[4];
int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    cin >> T;
    while (T--) {
        for (int i = 0; i < 4; i++) cin >> P[i];
        cout << (([&] {
            for (int i = 0; i < 3; i++) {
                int b = (P[0] >> i) & 1;
                for (int j = 1; j < 4; j++)
                    if (((P[j] >> i) & 1) != b) goto skip;
                return true;
                skip:;
            }
            return false;
        }()) ? "YES\n" : "NO\n");
    }
}
