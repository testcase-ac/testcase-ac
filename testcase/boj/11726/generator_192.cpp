#include "testlib.h"

int MIN = 1;
int MAX = 1000;
int THRESHOLDS[] = {25, 100};
const int sz = sizeof(THRESHOLDS) / sizeof(THRESHOLDS[0]);
int generate_with_threshold() {
    int c = rnd.next(1, sz+1);
    if(c == 1) {
        return rnd.next(MIN, THRESHOLDS[0]);
    } else if(c == sz+1) {
        return rnd.next(THRESHOLDS[sz-1]+1, MAX);
    } else {
        return rnd.next(THRESHOLDS[c-2]+1, THRESHOLDS[c-1]);
    }
}
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    println(generate_with_threshold());
}
