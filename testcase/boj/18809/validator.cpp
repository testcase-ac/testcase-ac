#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 50, "N");
    inf.readSpace();
    int M = inf.readInt(2, 50, "M");
    inf.readSpace();
    int G = inf.readInt(1, 5, "G");
    inf.readSpace();
    int R = inf.readInt(1, 5, "R");
    inf.readEoln();

    vector<vector<int>> a(N, vector<int>(M));
    int cnt2 = 0;

    for (int i = 0; i < N; ++i) {
        // read exactly M integers on this line
        for (int j = 0; j < M; ++j) {
            a[i][j] = inf.readInt(0, 2, "cell");
            if (j + 1 < M)
                inf.readSpace();
            if (a[i][j] == 2) cnt2++;
        }
        inf.readEoln();
    }

    // Problem guarantees:
    // "배양액을 뿌릴 수 있는 땅의 수는 R+G개 이상이고 10개 이하이다."
    ensuref(cnt2 >= R + G,
            "Number of cells with value 2 (%d) is less than R+G (%d)",
            cnt2, R + G);
    ensuref(cnt2 <= 10,
            "Number of cells with value 2 (%d) is greater than 10",
            cnt2);

    inf.readEof();
}
