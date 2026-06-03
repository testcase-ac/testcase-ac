#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        n = rnd.next(200, 239);
    } else if (mode == 1) {
        vector<int> anchors = {200, 209, 210, 219, 220, 229, 230, 239};
        n = rnd.any(anchors);
    } else if (mode == 2) {
        int center = rnd.any(vector<int>{206, 208, 216, 218, 226, 228});
        n = max(200, min(239, center + rnd.next(-1, 1)));
    } else {
        int lo = rnd.any(vector<int>{200, 210, 220, 230});
        n = rnd.next(lo, min(239, lo + 9));
    }

    println(n);
    return 0;
}
