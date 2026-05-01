#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Solver for the bulb-switch problem
    auto solve = [&](const string& cur, const string& target) -> int {
        int n = (int)cur.size();
        const int INF = 1000000007;

        auto simulate = [&](bool pressFirst) -> int {
            string a = cur;
            int cnt = 0;

            auto toggle = [&](int idx) {
                a[idx] = (a[idx] == '0' ? '1' : '0');
            };
            auto press = [&](int i) {
                for (int d = -1; d <= 1; ++d) {
                    int j = i + d;
                    if (0 <= j && j < n) toggle(j);
                }
            };

            if (pressFirst) {
                press(0);
                cnt++;
            }

            for (int i = 1; i < n; ++i) {
                if (a[i - 1] != target[i - 1]) {
                    press(i);
                    cnt++;
                }
            }

            if (a[n - 1] != target[n - 1]) return INF;
            return cnt;
        };

        int res0 = simulate(false);
        int res1 = simulate(true);
        int best = min(res0, res1);
        if (best >= INF) return -1;
        return best;
    };

    // Random binary string generator
    auto randomString = [&](int n) -> string {
        string s(n, '0');
        for (int i = 0; i < n; ++i)
            s[i] = char('0' + rnd.next(0, 1));
        return s;
    };

    // Apply pressing a switch to a bulb state string
    auto pressSwitchStr = [&](string &s, int i) {
        int n = (int)s.size();
        for (int d = -1; d <= 1; ++d) {
            int j = i + d;
            if (0 <= j && j < n)
                s[j] = (s[j] == '0' ? '1' : '0');
        }
    };

    int scenario = rnd.next(0, 5); // 0..5: six different generation modes
    int N;

    if (scenario == 5) {
        // For impossible-case search, avoid the very smallest N to enrich patterns
        N = rnd.next(3, 25);
    } else {
        // Size distribution for other scenarios
        int sizeType = rnd.next(0, 9);
        if (sizeType <= 2)      N = rnd.next(2, 5);   // 30% very small
        else if (sizeType <= 6) N = rnd.next(6, 15);  // 50% medium
        else                    N = rnd.next(16, 25); // 20% larger (but still small)
    }

    string cur, target;

    switch (scenario) {
        case 0: {
            // Completely random current and target
            cur = randomString(N);
            target = randomString(N);
            break;
        }
        case 1: {
            // Guaranteed solvable: start from cur and apply random presses to get target
            cur = randomString(N);
            target = cur;
            for (int i = 0; i < N; ++i) {
                if (rnd.next(0, 1)) {
                    pressSwitchStr(target, i);
                }
            }
            break;
        }
        case 2: {
            // Current equals target (0 presses optimal)
            cur = randomString(N);
            target = cur;
            break;
        }
        case 3: {
            // Target is bitwise complement of current
            cur = randomString(N);
            target = cur;
            for (int i = 0; i < N; ++i)
                target[i] = (cur[i] == '0' ? '1' : '0');
            break;
        }
        case 4: {
            // Only boundaries or a tiny segment differ
            cur = randomString(N);
            target = cur;
            int pattern = rnd.next(0, 3);
            if (pattern == 0) {
                // Only first bulb differs
                target[0] = (target[0] == '0' ? '1' : '0');
            } else if (pattern == 1) {
                // Only last bulb differs
                target[N - 1] = (target[N - 1] == '0' ? '1' : '0');
            } else if (pattern == 2) {
                // Both first and last differ
                target[0] = (target[0] == '0' ? '1' : '0');
                target[N - 1] = (target[N - 1] == '0' ? '1' : '0');
            } else {
                // Small contiguous segment flipped (length 1..3)
                int l = rnd.next(0, N - 1);
                int r = min(N - 1, l + rnd.next(0, 2));
                for (int i = l; i <= r; ++i)
                    target[i] = (target[i] == '0' ? '1' : '0');
            }
            break;
        }
        case 5: {
            // Try to generate a configuration that is impossible (-1 answer)
            int attempts = 0;
            while (attempts < 5000) {
                cur = randomString(N);
                target = randomString(N);
                if (solve(cur, target) == -1) {
                    break;
                }
                ++attempts;
            }
            if (attempts == 5000) {
                // Fallback to random if we failed to find an impossible one
                cur = randomString(N);
                target = randomString(N);
            }
            break;
        }
    }

    println(N);
    println(cur);
    println(target);

    return 0;
}
