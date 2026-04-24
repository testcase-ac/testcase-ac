#include "testlib.h"
#include <vector>
using namespace std;
int LEN_MIN = 1;
int LEN_MAX = 7;
int ELEM_MIN = -10;
int ELEM_MAX = 10;
vector<int> generate_vec(vector<int> cand) {
    int N = rnd.next(LEN_MIN, LEN_MAX);
    vector<int> v;
    for (int i = 0; i < N; i++) {
        v.push_back(rnd.any(cand));
    }
    return v;
}
vector<int> generate_cand() {
    vector<int> cand;
    double p = rnd.next();
    if(p < 0.075) {
        cand = {INT_MIN};
    } else if(p < 0.15) {
        cand = {INT_MAX};
    } else if(p < 0.35) {
        cand = {INT_MIN, INT_MAX};
    } else {
        int mn = rnd.next(ELEM_MIN, 0), mx = rnd.next(0, ELEM_MAX);
        for(int i=mn; i<=mx; i++) {
            cand.push_back(i);
        }
    }
    return cand;
}
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<int> cand1 = generate_cand(), cand2 = generate_cand();
    vector<int> a = generate_vec(cand1), b = generate_vec(cand2);
    println(a.size());
    for (int i = 0; i < a.size(); i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", a[i]);
        if(i == a.size()-1) {
            printf("\n");
        }
    }
    println(b.size());
    for (int i = 0; i < b.size(); i++) {
        if (i > 0) {
            printf(" ");
        }
        printf("%d", b[i]);
        if(i == b.size()-1) {
            printf("\n");
        }
    }
}
