#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> edgeValues = {1, 2, 3, 99, 100};
    int mode = rnd.next(0, 3);
    int n;

    if (mode == 0) {
        n = rnd.any(edgeValues);
    } else if (mode == 1) {
        n = rnd.next(4, 12);
    } else if (mode == 2) {
        n = rnd.next(13, 40);
    } else {
        n = rnd.next(41, 100);
    }

    println(n);
    return 0;
}
