#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 10);
    println(N);
    int c = rnd.next(1, 3);
    for (int i = 0; i < N; i++) {
        if(c == 1) {
            println(rnd.next("[a-z]{1,5}"));
        } else if(c == 2) {
            println(rnd.next("[a-b]{1,5}"));
        } else if(c == 3) {
            println(rnd.next("[a-c]{1,5}"));
        }
    }
}
