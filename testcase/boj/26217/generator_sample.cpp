#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> candidates;
    int mode = rnd.next(0, 6);
    if (mode == 0) {
        candidates = {1, 2, 3};
    } else if (mode == 1) {
        candidates = {4, 5, 10, 20};
    } else if (mode == 2) {
        candidates = {30, 50, 96, 100};
    } else if (mode == 3) {
        candidates = {250, 500, 750};
    } else if (mode == 4) {
        candidates = {900, 950, 999, 1000};
    } else {
        println(rnd.next(1, 1000));
        return 0;
    }

    println(rnd.any(candidates));
    return 0;
}
