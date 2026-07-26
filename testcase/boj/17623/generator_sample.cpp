#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(0, 9) == 0 ? 100 : rnd.next(1, 12);
    println(t);

    const vector<int> boundaries = {5, 6, 9, 10, 11, 998, 999, 1000};
    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 3);
        if (mode == 0)
            println(rnd.any(boundaries));
        else if (mode == 1)
            println(rnd.next(5, 30));
        else if (mode == 2)
            println(rnd.next(950, 1000));
        else
            println(rnd.next(5, 1000));
    }
}
