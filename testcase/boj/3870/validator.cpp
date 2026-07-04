#include "testlib.h"

#include <map>
#include <vector>
using namespace std;

bool isPrime(int x) {
    if (x < 2) return false;
    if (x % 2 == 0) return x == 2;
    for (long long d = 3; d * d <= x; d += 2) {
        if (x % d == 0) return false;
    }
    return true;
}

long long countMultiples(int n, int s, int w, int q) {
    vector<int> a(n);
    int g = s;
    for (int i = 0; i < n; ++i) {
        a[i] = (g / 7) % 10;
        if (g % 2 == 0) {
            g /= 2;
        } else {
            g = (g / 2) ^ w;
        }
    }

    if (q == 2 || q == 5) {
        long long endings = 0;
        long long answer = 0;
        for (int i = n - 1; i >= 0; --i) {
            if (a[i] % q == 0) ++endings;
            if (a[i] != 0) answer += endings;
        }
        return answer;
    }

    map<int, int> suffixCount;
    suffixCount[0] = 1;
    long long answer = 0;
    long long place = 1;
    int suffix = 0;
    for (int i = n - 1; i >= 0; --i) {
        suffix = (suffix + a[i] * place) % q;
        place = (place * 10) % q;
        if (a[i] != 0) answer += suffixCount[suffix];
        ++suffixCount[suffix];
    }
    return answer;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasets = 0;
    while (true) {
        int n = inf.readInt(0, 100000, "N");
        inf.readSpace();
        int s = inf.readInt(0, 1000000000, "S");
        inf.readSpace();
        int w = inf.readInt(0, 1000000000, "W");
        inf.readSpace();
        int q = inf.readInt(0, 99999999, "Q");
        inf.readEoln();

        if (n == 0 && s == 0 && w == 0 && q == 0) {
            break;
        }

        ++datasets;
        setTestCase(datasets);
        ensuref(datasets <= 50, "too many datasets: %d", datasets);
        ensuref(n >= 1, "N must be positive before the terminator, got %d", n);
        ensuref(s >= 1, "S must be positive before the terminator, got %d", s);
        ensuref(w >= 1, "W must be positive before the terminator, got %d", w);
        ensuref(q >= 2, "Q must be a prime number before the terminator, got %d", q);
        ensuref(isPrime(q), "Q must be prime, got %d", q);

        long long answer = countMultiples(n, s, w, q);
        ensuref(answer < (1LL << 30), "answer must be less than 2^30, got %lld", answer);
    }

    inf.readEof();
}
