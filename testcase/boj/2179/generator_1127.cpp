#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    string pattern;
    switch(rnd.next(1, 3)) {
        case 1:
            pattern = "[a-b]{1, 5}";
            break;
        case 2:
            pattern = "[a-c]{1, 5}";
            break;
        case 3:
            pattern = "[a-d]{1, 5}";
            break;
    }

    int N = rnd.next(2, 8);
    println(N);
    set<string> st;
    for(int i = 0; i < N; i++) {
        string s = rnd.next(pattern);
        while(st.count(s)) {
          s = rnd.next(pattern);
        }
        st.insert(s);
        println(s);
    }
}
