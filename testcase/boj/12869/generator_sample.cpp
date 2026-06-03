#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 3);
    int mode = rnd.next(0, 4);
    vector<int> hp(n);

    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            hp[i] = rnd.next(1, 10);
        } else if (mode == 1) {
            hp[i] = rnd.next(50, 60);
        } else if (mode == 2) {
            hp[i] = rnd.next(1, 60);
        } else {
            vector<int> anchors = {1, 2, 3, 4, 8, 9, 10, 18, 27, 36, 45, 54, 60};
            hp[i] = rnd.any(anchors);
        }
    }

    shuffle(hp.begin(), hp.end());

    println(n);
    println(hp);

    return 0;
}
