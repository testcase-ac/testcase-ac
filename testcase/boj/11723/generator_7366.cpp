#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose number of operations: small or medium
    int M;
    if (rnd.next(2) == 0) M = rnd.next(6, 10);
    else M = rnd.next(15, 30);
    // Operation types: 0=add,1=remove,2=check,3=toggle,4=all,5=empty
    vector<int> weights = {2, 2, 3, 2, 1, 1};
    vector<int> typePool;
    for (int t = 0; t < 6; ++t)
        for (int k = 0; k < weights[t]; ++k)
            typePool.push_back(t);
    vector<int> types(M);
    for (int i = 0; i < M; ++i)
        types[i] = rnd.any(typePool);
    // Ensure each operation type appears at least once
    vector<bool> have(6, false);
    for (int t : types) have[t] = true;
    for (int t = 0; t < 6; ++t) {
        if (!have[t]) {
            int idx = rnd.next(0, M - 1);
            types[idx] = t;
        }
    }
    // Output
    println(M);
    for (int i = 0; i < M; ++i) {
        int t = types[i];
        if (t == 4) {
            println("all");
        } else if (t == 5) {
            println("empty");
        } else {
            string op;
            if (t == 0) op = "add";
            else if (t == 1) op = "remove";
            else if (t == 2) op = "check";
            else op = "toggle";
            int x;
            // 10% chance to pick boundary 1 or 20, else uniform
            if (rnd.next(9) == 0) x = rnd.any(vector<int>{1, 20});
            else x = rnd.next(1, 20);
            println(op, x);
        }
    }
    return 0;
}
