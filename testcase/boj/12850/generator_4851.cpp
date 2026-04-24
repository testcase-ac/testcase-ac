#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We want a small, hand-checkable D (1 ≤ D ≤ 20), 
    // but bias toward both small and large ends within this range.
    vector<int> t_choices = {-2, -1, 1, 2};
    int t = rnd.any(t_choices);
    // rnd.wnext(20, t) produces a value in [0,19] biased by t; +1 gives [1,20]
    int D = rnd.wnext(20, t) + 1;

    // Output D
    println(D);

    return 0;
}
