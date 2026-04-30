#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // 2. Read A_1 ... A_N
    vector<int> A = inf.readInts(N, 1, 10000, "A_i");
    inf.readEoln();

    // 3. Read M
    int M = inf.readInt(2, 200000, "M");
    inf.readEoln();

    int cnt_query2 = 0;
    for (int q = 1; q <= M; ++q) {
        int type = inf.readInt(1, 2, "query_type");
        inf.readSpace();

        if (type == 1) {
            // 1 i v: A_i를 v로 바꾼다. (1 ≤ i ≤ N, 1 ≤ v ≤ 10^4)
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            int v = inf.readInt(1, 10000, "v");
            inf.readEoln();
        } else if (type == 2) {
            // 2 i j k: A_i, ..., A_j, k보다 큰 원소의 개수
            int i = inf.readInt(1, N, "i");
            inf.readSpace();
            int j = inf.readInt(i, N, "j"); // 1 ≤ i ≤ j ≤ N
            inf.readSpace();
            int k = inf.readInt(1, 10000, "k");
            inf.readEoln();
            ++cnt_query2;
        } else {
            ensuref(false, "Unknown query type %d at line %d", type, q+3);
        }
    }

    // At least one query of type 2
    ensuref(cnt_query2 >= 1, "There must be at least one query of type 2, but found %d", cnt_query2);

    inf.readEof();
}
