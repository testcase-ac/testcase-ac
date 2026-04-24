#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 20);
    println(N);
    for (int i = 0; i < N; i++) {
        int t = rnd.next(-10, 10);
        printf("%d", t);
        if(i == N-1) {
            printf("\n");
        } else {
            printf(" ");
        }
    }
}
