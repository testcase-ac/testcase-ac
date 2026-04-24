#include "testlib.h"

int MIN = 2;
int MAX = 1e6;
int THRESHOLDS[] = {50, 500, 5000};
const int sz = sizeof(THRESHOLDS) / sizeof(THRESHOLDS[0]);
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int c = rnd.next(1, sz+1);
    if(c == 1) {
        println(rnd.next(MIN, THRESHOLDS[0]));
    } else if(c == sz+1) {
        println(rnd.next(THRESHOLDS[sz-1]+1, MAX));
    } else {
        println(rnd.next(THRESHOLDS[c-2]+1, THRESHOLDS[c-1]));
    }

}
