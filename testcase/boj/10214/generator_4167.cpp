#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        // Hyper-parameter: maximum possible runs in an inning
        int maxScore = rnd.next(0, 9);

        // Desired outcome type: 0 = Draw, 1 = Yonsei wins, 2 = Korea wins
        int desiredType = (maxScore == 0 ? 0 : rnd.next(0, 2));

        vector<pair<int,int>> innings;
        int sumY, sumK;
        // Generate until we match the desired outcome
        do {
            innings.clear();
            sumY = sumK = 0;
            for (int i = 0; i < 9; ++i) {
                int Y = rnd.next(0, maxScore);
                int K = rnd.next(0, maxScore);
                innings.emplace_back(Y, K);
                sumY += Y;
                sumK += K;
            }
            int resultType = (sumY > sumK ? 1 : (sumY < sumK ? 2 : 0));
            if (resultType == desiredType) break;
        } while (true);

        // Output the 9 innings
        for (auto &p : innings) {
            println(p.first, p.second);
        }
    }

    return 0;
}
