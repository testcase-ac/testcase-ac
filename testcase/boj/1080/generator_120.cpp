#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 6);
    int M = rnd.next(1, 6);
    println(N, M);
    double lo = rnd.next(), hi = rnd.next(lo, 1.0);
    for(int i = 0; i < N; i++) {
        double prob = rnd.next(lo, hi);
        string s;
        for(int j = 0; j < M; j++) {
            if(rnd.next() < prob) {
                s += "1";
            } else {
                s += "0";
            }
        }
        println(s);
    }

    lo = rnd.next(), hi = rnd.next(lo, 1.0);
    for(int i = 0; i < N; i++) {
        double prob = rnd.next(lo, hi);
        string s;
        for(int j = 0; j < M; j++) {
            if(rnd.next() < prob) {
                s += "1";
            } else {
                s += "0";
            }
        }
        println(s);
    }
}
