#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 10);
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        v[i] = i+1;
    }
    shuffle(v.begin(), v.end());
    println(N);
    println(v);
}
