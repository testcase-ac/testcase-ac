#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<int> v(30);
    for (int i = 0; i < 30; i++) {
        v[i] = i+1;
    }
    if(rnd.next(0, 1)) {
        reverse(v.begin(), v.end());
    }
    int swap_count = rnd.next(0, 4);
    if(rnd.next(0, 1)) {
        swap_count = rnd.next(5, 100);
    }
    for (int i = 0; i < swap_count; i++) {
        int a = rnd.next(0, 29);
        int b = rnd.next(0, 29);
        swap(v[a], v[b]);
    }
    for(int i = 0; i < 28; i++) {
        println(v[i]);
    }
}
