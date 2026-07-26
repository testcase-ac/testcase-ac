#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 20);
    int mode = rnd.next(0, 4);
    vector<int> a(n);

    if (mode == 0) {
        fill(a.begin(), a.end(), rnd.next(1, 1000000));
    } else if (mode == 1 || mode == 2) {
        for (int& value : a) value = rnd.next(1, 1000000);
        sort(a.begin(), a.end());
        if (mode == 2) reverse(a.begin(), a.end());
    } else {
        int limit = mode == 3 ? rnd.next(1, 5) : 1000000;
        for (int& value : a) value = rnd.next(1, limit);
    }

    println(n);
    println(a);
}
