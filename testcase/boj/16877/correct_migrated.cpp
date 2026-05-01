#include <iostream>
#include <array>

using namespace std;
using u32 = unsigned int;

constexpr int MAX_N = 100'000;
constexpr int MAX_V = 3'000'000;

array<int, 32> fib;
array<int, MAX_V+1> grundy;
u32 vis;
void fill_grundy() {
    fib[0] = 1;
    fib[1] = 2;
    for (int i = 2; i <= 31; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    
    grundy[0] = 0;
    grundy[1] = 1;
    for (int i = 2; i <= MAX_V; i++) {
        vis = 0;
        for (int f : fib) {
            if (f > i) { break; }
            vis |= 1 << grundy[i - f];
        }
        grundy[i] = __builtin_ctz(~vis);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    fill_grundy();
    
    int n;
    cin >> n;

    int res = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        res ^= grundy[x];
    }

    cout << (res != 0 ? "koosaga" : "cubelover") << "\n";

    return 0;
}
