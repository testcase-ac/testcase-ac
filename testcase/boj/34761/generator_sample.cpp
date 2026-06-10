#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = (mode == 0 ? 1 : rnd.next(2, 14));
    if (rnd.next(5) == 0) n = rnd.next(15, 40);

    int alphabet = rnd.next(1, n);
    if (mode == 4) alphabet = 1;
    if (mode == 5) alphabet = n;

    vector<int> values(n);
    for (int i = 0; i < n; ++i) values[i] = i + 1;
    shuffle(values.begin(), values.end());
    values.resize(alphabet);

    vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = values[rnd.next(alphabet)];

    if (mode == 2 && n > 1) {
        a[0] = 1;
        bool hasTwo = false;
        for (int x : a) hasTwo = hasTwo || x == 2;
        if (hasTwo) {
            for (int& x : a) {
                if (x == 2) x = 1;
            }
        }
    }

    vector<int> b(2 * n);
    for (int i = 0; i < n; ++i) b[i] = a[i];

    vector<int> present(n + 1, 0);
    vector<int> seen;
    for (int x : a) {
        if (!present[x]) {
            present[x] = 1;
            seen.push_back(x);
        }
    }

    for (int i = n; i < 2 * n; ++i) b[i] = seen[rnd.next((int)seen.size())];

    if (mode == 1 && n > 1) {
        int pos = rnd.next(n);
        int replacement = rnd.next(1, n);
        while (replacement == b[pos] && n > 1) replacement = rnd.next(1, n);
        b[pos] = replacement;
    } else if (mode == 2 && n > 1) {
        int missing = 0;
        for (int x = 1; x <= n; ++x) {
            if (!present[x]) {
                missing = x;
                break;
            }
        }
        if (missing != 0) b[rnd.next(n, 2 * n - 1)] = missing;
    } else if (mode == 3) {
        reverse(b.begin() + n, b.end());
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
