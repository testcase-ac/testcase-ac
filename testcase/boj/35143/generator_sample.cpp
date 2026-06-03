#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> small = {1, 3, 5, 7};
    vector<int> boundary = {1, 119, 121};

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.any(small);
    } else if (mode == 1) {
        n = rnd.any(boundary);
    } else if (mode == 2) {
        n = 2 * rnd.next(0, 60) + 1;
    } else {
        n = 2 * rnd.wnext(61, 3) + 1;
    }

    println(n);
    return 0;
}
