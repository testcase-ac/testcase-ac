#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

using ll = long long;

ll randomSmall() {
    return rnd.next(-5, 5);
}

ll randomValue() {
    int mode = rnd.next(4);
    if (mode == 0) return 0;
    if (mode == 1) return rnd.next(-3, 3);
    if (mode == 2) return rnd.next(-10, 10);
    return rnd.next(-20, 20);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int q = rnd.next(1, 18);
    int typeOneCount = rnd.next(0, min(3, q - 1));
    vector<int> types(q, 2);
    for (int i = 0; i < typeOneCount; ++i) types[i] = 1;
    shuffle(types.begin(), types.end());

    vector<ll> roots;
    println(q);
    for (int i = 0; i < q; ++i) {
        if (types[i] == 2) {
            int mode = rnd.next(5);
            ll c;
            if (!roots.empty() && mode <= 2) {
                ll r = rnd.any(roots);
                if (mode == 0) c = r;
                else if (mode == 1) c = r - 1;
                else c = r + 1;
            } else {
                c = randomValue();
            }
            println(2, c);
            continue;
        }

        int mode = rnd.next(6);
        ll a;
        ll b;
        if (mode == 0) {
            a = 0;
            b = randomValue();
        } else if (mode <= 3) {
            ll root = randomSmall();
            a = rnd.next(-5, 5);
            if (a == 0) a = 1;
            b = -a * root;
            roots.push_back(root);
        } else {
            a = randomValue();
            b = randomValue();
        }
        println(1, a, b);
    }

    return 0;
}
