#include "testlib.h"
#include <vector>
using namespace std;
int generate_int_biased(int min, int max, vector<int> thresholds) {
    int sz = thresholds.size();
    int c = rnd.next(1, sz+1);
    if(c == 1) {
        return rnd.next(min, thresholds[0]);
    } else if(c == sz+1) {
        return rnd.next(thresholds[sz-1]+1, max);
    } else {
        return rnd.next(thresholds[c-2]+1, thresholds[c-1]);
    }
}
vector<int> generate_vec(int len_min, int len_max, int elem_min, int elem_max) {
    int N = rnd.next(len_min, len_max);
    vector<int> v;
    for (int i = 0; i < N; i++) {
        v.push_back(rnd.next(elem_min, elem_max));
    }
    return v;
}
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 15);
    vector<int> cmds;
    bool has_zero = false;
    double th = rnd.next();
    for(int i = 0; i < N; i++) {
        if(rnd.next() < th) {
            has_zero = true;
            cmds.push_back(0);
        } else {
            cmds.push_back(rnd.next(1, 9));
        }
    }
    if(!has_zero) {
        int idx = rnd.next(0, N-1);
        cmds[idx] = 0;
    }
    println(N);
    for(int i = 0; i < N; i++) {
        println(cmds[i]);
    }
}
