#include "testlib.h"

#include <vector>

using namespace std;

vector<int> makeValues(int count, int mode) {
    vector<int> values(count);
    for (int i = 0; i < count; ++i) {
        if (mode == 0) {
            values[i] = rnd.next(0, 9);
        } else if (mode == 1) {
            values[i] = rnd.next(0, 1) ? rnd.next(0, 3) : rnd.next(997, 1000);
        } else if (mode == 2) {
            values[i] = rnd.next(0, 4) == 0 ? 0 : rnd.next(1, 30);
        } else if (mode == 3) {
            values[i] = rnd.next(0, 4) == 0 ? 1000 : rnd.next(0, 1000);
        } else {
            int base = rnd.next(0, 40);
            values[i] = min(1000, base + rnd.next(0, 15));
        }
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(1, 6);
    println(cases);

    for (int tc = 0; tc < cases; ++tc) {
        int mode = rnd.next(0, 4);
        int n;
        if (mode == 0) {
            n = 2;
        } else if (mode == 1) {
            n = rnd.next(3, 5);
        } else if (mode == 2) {
            n = rnd.next(6, 12);
        } else {
            n = rnd.next(13, 30);
        }

        int scalarMode = rnd.next(0, 4);
        vector<int> scalars = makeValues(4, scalarMode);
        println(n, scalars[0], scalars[1], scalars[2], scalars[3]);

        int arrayMode = rnd.next(0, 4);
        vector<int> pass1 = makeValues(n - 1, arrayMode);
        vector<int> dribble1 = makeValues(n - 1, (arrayMode + rnd.next(0, 2)) % 5);
        vector<int> pass2 = makeValues(n - 1, (arrayMode + rnd.next(1, 3)) % 5);
        vector<int> dribble2 = makeValues(n - 1, (arrayMode + rnd.next(2, 4)) % 5);

        if (mode == 1) {
            for (int i = 0; i < n - 1; ++i) {
                pass1[i] = rnd.next(0, 1) ? 0 : 1000;
                dribble2[i] = pass1[i];
            }
        }
        if (mode == 2) {
            int pivot = rnd.next(0, n - 2);
            pass1[pivot] = 0;
            pass2[pivot] = 0;
            dribble1[pivot] = rnd.next(900, 1000);
            dribble2[pivot] = rnd.next(900, 1000);
        }

        println(pass1);
        println(dribble1);
        println(pass2);
        println(dribble2);
    }

    return 0;
}
