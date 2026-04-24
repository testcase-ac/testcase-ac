#include "testlib.h"

int MIN = 1;
int MAX = 29;
int THRESHOLDS[] = {6};
const int sz = sizeof(THRESHOLDS) / sizeof(THRESHOLDS[0]);
int gen_int() {
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
    int T = rnd.next(1, 3);
    println(T);
    for(int i = 0; i < T; i++) {
        int a = gen_int(), b = gen_int();
        if(a > b) std::swap(a, b);
        println(a, b);
    }
}
