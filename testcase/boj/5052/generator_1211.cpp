#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 2);
    println(T);
    string nums = "[0-9]";
    if(rnd.next(0, 1)) {
        nums = "[0-2]";
    }
    set<string> seen;
    for(int i=0; i<T; i++) {
        int N = rnd.next(1, 6);
        println(N);
        for(int j=0; j<N; j++) {
            string s;
            do {
              s.clear();
              int len = rnd.next(1, 5);
              for(int k=0; k<len; k++) {
                  s += rnd.next(nums);
              }
            } while(seen.count(s));
            seen.insert(s);
            println(s);
        }
    }
}
