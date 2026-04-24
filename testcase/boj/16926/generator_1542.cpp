#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int N, M;
    int t = rnd.next(0, 1);
    if (t == 0) {
        int s = rnd.next(1, 3) * 2; // 2, 4, 6
        N = s;
        M = rnd.next(N, min(N + 2, 300));
    } else {
        int s = rnd.next(1, 3) * 2; // 2, 4, 6
        M = s;
        N = rnd.next(M, min(M + 2, 300));
    }
    
    int R = rnd.next(1, 5);
    println(N, M, R);
    
    for (int i = 0; i < N; ++i) {
        vector<int> row;
        for (int j = 0; j < M; ++j) {
            row.push_back(rnd.next(1, 9));
        }
        for (int j = 0; j < M; ++j) {
            if (j > 0) {
                cout << ' ';
            }
            cout << row[j];
        }
        cout << endl;
    }
    
    return 0;
}
