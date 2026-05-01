#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
  
    int N = rnd.next(10, 100);

    vector<int> T(N);
    for (int i = 0; i < N; i++) {
        T[i] = rnd.next(0, 2);
    }

    println(N);
    println(T);
    return 0;
}
