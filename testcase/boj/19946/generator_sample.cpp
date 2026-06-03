#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string toDecimal(unsigned __int128 value) {
    string result;
    do {
        result.push_back(char('0' + value % 10));
        value /= 10;
    } while (value > 0);
    reverse(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> edgeK = {1, 2, 3, 62, 63, 64};
    int mode = rnd.next(0, 4);
    int k;
    if (mode == 0) {
        k = rnd.any(edgeK);
    } else if (mode == 1) {
        k = rnd.next(1, 8);
    } else if (mode == 2) {
        k = rnd.next(57, 64);
    } else if (mode == 3) {
        k = rnd.next(24, 42);
    } else {
        k = rnd.next(1, 64);
    }

    unsigned __int128 n = (((unsigned __int128)1) << 64) -
                          (((unsigned __int128)1) << (64 - k));
    println(toDecimal(n));

    return 0;
}
