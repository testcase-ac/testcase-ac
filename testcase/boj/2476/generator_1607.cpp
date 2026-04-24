#include "testlib.h"
using namespace std;

vector<int> gen(int type) {
    if(type == 1) {
        int n = rnd.next(1, 6);
        return {n, n, n};
    } else if(type == 2) {
        int a = rnd.next(1, 6), b = rnd.next(1, 6);
        while(a == b) {
            b = rnd.next(1, 6);
        }
        vector<int> ret = {a, a, b};
        shuffle(ret.begin(), ret.end());
        return ret;
    } else {
        int a = rnd.next(1, 6), b = rnd.next(1, 6), c = rnd.next(1, 6);
        while(a == b || b == c || a == c) {
            a = rnd.next(1, 6);
            b = rnd.next(1, 6);
            c = rnd.next(1, 6);
        }
        return {a, b, c};
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 4);
    println(N);
    vector<int> types = {1, 2, 3};
    if(rnd.next() < 0.5) {
        int remove = rnd.next(0, 2);
        types.erase(types.begin() + remove);
    }
    for(int i = 0; i < N; i++) {
        vector<int> v = gen(types[rnd.next(0, (int)types.size() - 1)]);
        println(v);
    }
}
