#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    string charList = "[a-zA-Z0-9]";
    if(rnd.next() < 0.75) {
        charList = "[a-e]";
    }
    int mn = rnd.next(1, 5);
    int mx = rnd.next(mn, 6);
    for(int i=0; i<5; i++) {
        int col = rnd.next(mn, mx);
        string s = "";
        for(int j=0; j<col; j++) {
            s += rnd.next(charList);
        }
        println(s);
    }
}
