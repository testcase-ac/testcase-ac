#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(1, 2);
    for(int i = 0; i < T; i++) {
        string cand = "[a-b]";
        int c = rnd.next(0, 2);
        if(c == 1) {
            cand = "[a-e]";
        } else if(c == 2) {
            cand = "[a-z]";
        }
        int N = rnd.next(2, 6);
        println(N);
        int len_mn = rnd.next(1, 4);
        int len_mx = rnd.next(len_mn+1, 5);
        set<string> st;
        for(int j = 0; j < N; j++) {
            string s;
            do {
                int len = rnd.next(len_mn, len_mx);
                s = "";
                for(int k = 0; k < len; k++) {
                    s += rnd.next(cand);
                }
            } while(st.count(s));
            st.insert(s);
            println(s);
        }
    }
}
