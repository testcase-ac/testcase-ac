#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tests = rnd.next(1, 4);
    println(tests);
    for (int t = 0; t < tests; ++t) {
        int n = rnd.next(1, 12);
        int mode = rnd.next(0, 3);
        int x = rnd.next(1, 20);
        int baseHeight = rnd.next(1, 30);

        println(n);
        for (int i = 0; i < n; ++i) {
            int height;
            if (mode == 0)
                height = baseHeight;
            else if (mode == 1)
                height = baseHeight + i;
            else if (mode == 2)
                height = baseHeight + n - i;
            else
                height = rnd.next(1, 50);

            println(x, height);
            x += rnd.next(1, 20);
        }
    }
}
