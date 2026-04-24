#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int mn = 0, mx = 41;
    mn = rnd.next(0, 41);
    mx = rnd.next(mn, 41);
    vector<int> v;
    for(int i=0; i<10; i++) {
        v.push_back(rnd.next(mn, mx));
    }
    int c = rnd.next(0, 2);
    if(c == 0) {
        sort(v.begin(), v.end());
    } else if(c == 1) {
        sort(v.begin(), v.end(), greater<int>());
    }
    for(int t: v) {
        println(t);
    }
}
