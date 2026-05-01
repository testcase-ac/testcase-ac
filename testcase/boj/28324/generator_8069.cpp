#include "testlib.h"
#include <vector>
#include <string>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 12);
    vector<long long> V(N);
    vector<string> types = {"random", "inc", "dec", "peak", "valley", "uniform", "one_big", "layered"};
    string type = rnd.any(types);
    if (type == "random") {
        for (int i = 0; i < N; i++) V[i] = rnd.next(1, 10);
    } else if (type == "inc") {
        V[0] = rnd.next(1, 5);
        for (int i = 1; i < N; i++) V[i] = V[i-1] + rnd.next(0, 3);
    } else if (type == "dec") {
        V[0] = rnd.next(5, 10);
        for (int i = 1; i < N; i++) V[i] = max(1LL, V[i-1] - rnd.next(0, 3));
    } else if (type == "peak") {
        int p = rnd.next(0, N-1);
        for (int i = 0; i < N; i++) V[i] = rnd.next(1, 5);
        V[p] = rnd.next(8, 15);
    } else if (type == "valley") {
        int p = rnd.next(0, N-1);
        for (int i = 0; i < N; i++) V[i] = rnd.next(5, 10);
        V[p] = 1;
    } else if (type == "uniform") {
        long long v = rnd.next(1, 10);
        for (int i = 0; i < N; i++) V[i] = v;
    } else if (type == "one_big") {
        int p = rnd.next(0, N-1);
        for (int i = 0; i < N; i++) V[i] = rnd.next(1, 5);
        V[p] = rnd.next(20, 50);
    } else if (type == "layered") {
        int mid = N / 2;
        for (int i = 0; i < N; i++) {
            if (i <= mid) V[i] = rnd.next(1, (i+1)*2);
            else V[i] = rnd.next(1, (N-i)*2 + 1);
        }
    }
    println(N);
    println(V);
    return 0;
}
