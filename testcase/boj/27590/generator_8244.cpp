#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int ds, ys, dm, ym, n;
    // Retry until we find a valid configuration with next eclipse within 5000 years
    do {
        // Hyper-parameters to bias period selection toward small or large values
        int ts = rnd.next(-2, 2);
        int tm = rnd.next(-2, 2);
        // ys, ym in [1,50], biased by wnext
        ys = rnd.wnext(50, ts) + 1;
        ym = rnd.wnext(50, tm) + 1;
        // ds in [0, ys-1], dm in [0, ym-1]
        ds = rnd.next(0, ys - 1);
        dm = rnd.next(0, ym - 1);
        // avoid eclipse happening right now
        if (ds == 0 && dm == 0) continue;
        // check next eclipse within 5000 years
        n = -1;
        for (int i = 1; i <= 5000; i++) {
            if ((ds + i) % ys == 0 && (dm + i) % ym == 0) {
                n = i;
                break;
            }
        }
    } while (n < 0);

    // Output
    println(ds, ys);
    println(dm, ym);
    return 0;
}
