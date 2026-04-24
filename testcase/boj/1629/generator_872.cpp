#include "testlib.h"
using namespace std;

int sample() {
    double p = rnd.next();
    if(p < 0.5) {
        return rnd.next(1, 9);
    } else if(p < 0.8) {
        return rnd.next(1, 2147483647);
    } else {
        return 2147483647;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    println(sample(), sample(), sample());
}
