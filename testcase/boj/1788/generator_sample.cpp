#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(-20, 20);
    } else if (mode == 1) {
        n = rnd.any(vector<int>{-1, 0, 1, -2, 2, -7, 7, -10, 10});
    } else if (mode == 2) {
        n = rnd.next(-2000, -21);
    } else if (mode == 3) {
        n = rnd.next(21, 2000);
    } else if (mode == 4) {
        int magnitude = rnd.next(1, 1000000);
        if (rnd.next(0, 1) == 0) {
            magnitude += magnitude % 2;
        } else {
            magnitude += 1 - magnitude % 2;
        }
        if (magnitude > 1000000) {
            magnitude -= 2;
        }
        n = -magnitude;
    } else {
        n = rnd.any(vector<int>{-1000000, -999999, -999998, 999998, 999999, 1000000});
    }

    println(n);
    return 0;
}
