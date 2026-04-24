#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for train capacity bias: small or large
    int tCap = rnd.next(-1, 1);
    int cap = rnd.wnext(100, tCap) + 1;  // capacity between 1 and 100

    vector<pair<int,int>> a;
    a.reserve(10);

    int curr = 0;
    // Station 1: no one leaves
    {
        int off = 0;
        int t1 = rnd.next(-1, 1);
        int board = rnd.wnext(cap + 1, t1);  // 0..cap
        a.emplace_back(off, board);
        curr = board;
    }

    // Stations 2 to 9
    for (int i = 2; i <= 9; ++i) {
        // number of people leaving: 0..curr
        int tOff = rnd.next(-1, 1);
        int offi = rnd.wnext(curr + 1, tOff);
        int afterOff = curr - offi;

        // number of people boarding: 0..(cap - afterOff)
        int maxAdd = cap - afterOff;
        int tBoard = rnd.next(-1, 1);
        int boardi = rnd.wnext(maxAdd + 1, tBoard);

        a.emplace_back(offi, boardi);
        curr = afterOff + boardi;
    }

    // Station 10: final stop, no one boards
    {
        int tOff = rnd.next(-1, 1);
        int offi = rnd.wnext(curr + 1, tOff);
        a.emplace_back(offi, 0);
    }

    // Output 10 lines
    for (auto &p : a) {
        println(p.first, p.second);
    }

    return 0;
}
