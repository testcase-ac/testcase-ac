#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <set>
#include <vector>
#include <queue>
#include <utility>
#include <list>
#include <map>
#include <stack>
#include <cmath>
#include <functional>
#include <string.h>


static const int INF = 0x1f1f1f1f;

struct CompactForm {
    int len;
    uint64_t b[2];
    static const CompactForm INF;

    CompactForm() {
        len = 0;
        b[0] = b[1] = 0;
    }
    CompactForm(const std::string& s) : CompactForm() {
        len = (int)s.length();
        for (int i = 0; i < len; i++) {
            setbit(i, s[i] == ')');
        }
    }
    CompactForm(const char* s) : CompactForm(std::string(s)) {}
    void setbit(int i, bool set) {
        if (set) b[i >> 6] |= 1ull << (63 - (i & 63));
        else b[i >> 6] &= ~(1ull << (63 - (i & 63)));
    }
    bool getbit(int i) const {
        return !!(b[i >> 6] & (1ull << (63 - (i & 63))));
    }
    CompactForm concat(const CompactForm& b) const {
        const CompactForm& a = *this;
        CompactForm c;
        c.len = std::min(128, a.len + b.len);
        if (a.len < 64) {
            c.b[0] = a.b[0] | (b.b[0] >> a.len);
            c.b[1] = (b.b[0] << (64 - a.len)) | (b.b[1] >> a.len);
        }
        else {
            c.b[0] = a.b[0];
            c.b[1] = a.b[1] | (b.b[0] >> (a.len - 64));
        }
        return c;
    }
    CompactForm wrap() const {
        CompactForm c;
        c.len = std::min(128, len + 2);
        c.b[0] = (0ull << 63) | (b[0] >> 1);
        c.b[1] = (b[0] << 63) | (b[1] >> 1);
        if (c.len < 64) c.b[0] |= (1ull << (64 - c.len));
        else if (len + 2 < 128) c.b[1] |= (1ull << (128 - c.len));
        return c;
    }
    CompactForm wrap(int times) const {
        if (times == 0) return *this;
        if (times >= 64) return CompactForm::INF;

        CompactForm c;
        c.len = std::min(128, len + 2 * times);
        c.b[0] = (0ull << (64 - times)) | (b[0] >> times);
        c.b[1] = (b[0] << (64 - times)) | (b[1] >> times);

        uint64_t closing = ((1ull << times) - 1) << (64 - times);
        if (len + times < 64) {
            c.b[0] |= closing >> (len + times);
            if (c.len >= 64) {
                c.b[1] |= closing << (64 - (len + times));
            }
        }
        else {
            c.b[1] |= closing >> (len + times - 64);
        }
        return c;
    }
    bool operator<(const CompactForm& rhs) const {
        if (len != rhs.len) return len < rhs.len;
        return (b[0] < rhs.b[0]) || (b[0] == rhs.b[0] && b[1] < rhs.b[1]);
    }
    std::string to_string() const {
        std::string s;
        s.resize(len);
        for (int i = 0; i < len; i++) s[i] = getbit(i) ? ')' : '(';
        return s;
    }
};
const CompactForm CompactForm::INF = "()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()()";

int Factor[1000001];
CompactForm DP[1000001];

int Tmp[10000000];
int* TmpNext = Tmp;

int main() {
    /* part 1: Eratosthenes's sieve */
    Factor[1] = 1;
    Factor[2] = 2;

    std::vector<int> primes;
    primes.push_back(2);
    for (int p = 3; p <= 1000000; p++) {
        Factor[p] = p;
        for (auto n : primes) {
            if (p % n == 0) {
                Factor[p] = n;
                break;
            }
            if (n * n > p) break;
        }
        if (Factor[p] == p) primes.push_back(p);
    }

    /* part 2: DP up to 1,000,000 */
    DP[1] = "";
    DP[2] = "()";

    for (int i = 3; i <= 1000000; i++) {
        DP[i] = DP[i - 1].wrap();
        if (Factor[i] < i) {
            std::map<int, int> m;
            for (int x = i; x > 1; x /= Factor[x]) {
                auto it = m.find(Factor[x]);
                if (it == m.end()) m[Factor[x]] = 1;
                else it->second++;
            }

            int PL = 0, QL = 0;
            int* TmpNextOrig = TmpNext;
            int* P = TmpNext;
            for (auto [p, q] : m) *TmpNext++ = p, PL++;
            int* Q = TmpNext;
            for (auto [p, q] : m) *TmpNext++ = q, QL++;

            std::function<void(int, int)> recurse = [&](int k, int val) {
                if (k == (int)PL) {
                    if (val != 1 && val != i) {
                        DP[i] = std::min(DP[i], DP[val].concat(DP[i / val]));
                        DP[i] = std::min(DP[i], DP[i / val].concat(DP[val]));
                    }
                }
                else {
                    for (int c = 0, power = val; c <= Q[k]; c++, power *= P[k]) recurse(k + 1, power);
                }
            };
            recurse(0, 1);
            TmpNext = TmpNextOrig;
        }
    }

    /* part 3: apply branch-and-bound */
    std::map<int, CompactForm> mTrue, mFalse;
    std::function<CompactForm(int, bool)> solve = [&](int n, bool allow_wrap) -> CompactForm { /* n <= 10^9 is assumed */
        if (n <= 1000000)
            return DP[n].to_string();
        
        auto& memoizer = allow_wrap ? mTrue : mFalse;
        if (memoizer.count(n))
            return memoizer[n];

        int x = n;
        std::map<int, int> m;
        for (auto p : primes) {
            if (x % p == 0) {
                int cnt = 0;
                while (x % p == 0) cnt++, x /= p;
                m[p] = cnt;
            }
            if (p * p > x) break;
        }
        if (x > 1) m[x] = 1;

        int PL = 0, QL = 0;
        int* TmpNextOrig = TmpNext;
        int* P = TmpNext;
        for (auto [p, q] : m) *TmpNext++ = p, PL++;
        int* Q = TmpNext;
        for (auto [p, q] : m) *TmpNext++ = q, QL++;

        CompactForm ans = CompactForm::INF;
        std::function<void(int, int)> recurse = [&](int k, int val) {
            if (k == (int)PL) {
                if (val != 1 && val != n) {
                    CompactForm v1 = solve(val, true);
                    CompactForm v2 = solve(n / val, true);
                    ans = std::min(ans, v1.concat(v2));
                    ans = std::min(ans, v2.concat(v1));
                }
            }
            else {
                for (int c = 0, power = val; c <= Q[k]; c++, power *= P[k]) recurse(k + 1, power);
            }
        };
        recurse(0, 1);
        TmpNext = TmpNextOrig;

        if (allow_wrap) {
            for (int d = 1; d <= 10; d++) {
                CompactForm v = solve(n - d, false);
                ans = std::min(ans, v.wrap(d));
            }
        }

        memoizer[n] = ans;
        if (allow_wrap) mFalse[n] = ans;
        return ans;
    };

    /* print */
    int T;
    scanf("%d", &T);
    for (int t = 1; t <= T; t++) {
        int n;
        scanf("%d", &n);
        printf("%s\n", solve(n, true).to_string().c_str());
    }

    return 0;
}
