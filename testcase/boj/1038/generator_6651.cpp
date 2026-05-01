#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Special values to catch edge cases
    vector<int> specials = {0, 1, 9, 10, 100, 1021, 1022, 1023, 1024, 1000000};
    int N;
    int mode = rnd.next(0, 4);
    if (mode == 0) {
        // pick a special value
        N = rnd.any(specials);
    } else if (mode == 1 || mode == 2) {
        // pick a valid small/medium N within range of existing decreasing numbers
        N = rnd.next(0, 1022);
    } else {
        // pick a too-large N to force -1
        N = rnd.next(1023, 1000000);
    }
    println(N);
    return 0;
}
