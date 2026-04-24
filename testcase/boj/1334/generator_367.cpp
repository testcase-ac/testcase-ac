#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    if(rnd.next(0, 1)) {
        println(rnd.next("[1-9][0-9]{1,49}"));
    } else {
        string s = rnd.next("[1-9][0-9]{1,24}");
        string rev = s;
        reverse(rev.begin(), rev.end());
        string res = s + rev;
        println(res);
    }
}
