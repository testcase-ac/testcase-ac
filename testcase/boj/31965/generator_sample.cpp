#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12);
    int q = rnd.next(5, 12);
    int mode = rnd.next(0, 2);
    int maxGap = mode == 0 ? 3 : mode == 1 ? 1000000 : 20;

    vector<int> gaps(n - 1);
    long long totalGap = 0;
    for (int& gap : gaps) {
        gap = rnd.next(1, maxGap);
        totalGap += gap;
    }

    int start;
    if (mode == 2)
        start = 1000000000 - totalGap - rnd.next(0, 20);
    else
        start = rnd.next(1, mode == 0 ? 20 : 100);

    vector<int> x(n, start);
    for (int i = 1; i < n; ++i)
        x[i] = x[i - 1] + gaps[i - 1];

    println(n, q);
    println(x);

    int offset = rnd.next(0, 4);
    for (int query = 0; query < q; ++query) {
        int l, r;
        switch ((query + offset) % 5) {
        case 0:
            l = x.front();
            r = x.back();
            break;
        case 1:
            l = r = rnd.any(x);
            break;
        case 2:
            l = rnd.next(1, 1000000000);
            r = rnd.next(1, 1000000000);
            if (l > r) swap(l, r);
            break;
        case 3:
            l = rnd.any(x);
            r = rnd.any(x);
            if (l > r) swap(l, r);
            break;
        default:
            if (x.front() > 1) {
                l = 1;
                r = x.front() - 1;
            } else {
                l = x.back() + 1;
                r = 1000000000;
            }
        }
        println(l, r);
    }
}
