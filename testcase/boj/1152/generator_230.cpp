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
    int N = rnd.next(2, 15);
    bool last_space = false;
    bool all_space = true;
    string s;
    while(s.length() < N) {
        int c = rnd.next(1, 3);
        if(c == 1) {
            s += rnd.next("[a-z]{1}");
            last_space = false;
        } else if(c == 2) {
            s += rnd.next("[A-Z]{1}");
            last_space = false;
        } else if(c == 3) {
            if(!last_space) {
                s += " ";
                last_space = true;
            }
        }
    }
    if(last_space) {
      s += rnd.next("[a-z]{1}");
    }
    println(s);
}
