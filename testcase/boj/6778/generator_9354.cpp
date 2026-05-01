#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    auto isTroy = [](int a, int e) {
        return (a >= 3 && e <= 4);
    };
    auto isVlad = [](int a, int e) {
        return (a <= 6 && e >= 2);
    };
    auto isGraeme = [](int a, int e) {
        return (a <= 2 && e <= 3);
    };

    // Scenario types:
    // 0: none
    // 1: only TroyMartian
    // 2: only VladSaturnian
    // 3: only GraemeMercurian
    // 4: TroyMartian + VladSaturnian
    // 5: VladSaturnian + GraemeMercurian
    int scenario = rnd.next(0, 5);

    int a, e;
    while (true) {
        // Small, hand-checkable range
        a = rnd.next(0, 8);
        e = rnd.next(0, 8);

        bool T = isTroy(a, e);
        bool V = isVlad(a, e);
        bool G = isGraeme(a, e);

        bool ok = false;
        switch (scenario) {
            case 0: ok = (!T && !V && !G); break;
            case 1: ok = ( T && !V && !G); break;
            case 2: ok = (!T &&  V && !G); break;
            case 3: ok = (!T && !V &&  G); break;
            case 4: ok = ( T &&  V && !G); break;
            case 5: ok = (!T &&  V &&  G); break;
        }

        if (ok) break;
    }

    println(a);
    println(e);

    return 0;
}
