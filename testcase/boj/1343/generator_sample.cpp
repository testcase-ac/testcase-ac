#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    string board;

    if (mode == 0) {
        int n = rnd.next(1, 50);
        board.assign(n, '.');
    } else if (mode == 1) {
        int n = rnd.next(1, 50);
        board.assign(n, 'X');
    } else if (mode == 2) {
        int n = rnd.next(1, 50);
        double xProb = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            board += rnd.next() < xProb ? 'X' : '.';
        }
    } else {
        vector<int> evenRuns = {2, 4, 6, 8, 10, 12};
        vector<int> oddRuns = {1, 3, 5, 7};
        int target = rnd.next(1, 50);

        while ((int)board.size() < target) {
            if (!board.empty() && board.back() != '.' && rnd.next(3) == 0) {
                int dots = min(rnd.next(1, 4), target - (int)board.size());
                board.append(dots, '.');
                continue;
            }

            bool useOdd = mode == 4 && rnd.next(3) == 0;
            const vector<int>& choices = useOdd ? oddRuns : evenRuns;
            int run = rnd.any(choices);
            run = min(run, target - (int)board.size());
            board.append(run, 'X');

            if ((int)board.size() < target) {
                int dots = min(rnd.next(1, 3), target - (int)board.size());
                board.append(dots, '.');
            }
        }
    }

    println(board);
    return 0;
}
