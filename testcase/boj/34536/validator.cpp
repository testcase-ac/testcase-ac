#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and K
    int N = inf.readInt(1, 200000, "N");
    inf.readSpace();
    // K can be up to 3*10^9, so use long long
    long long K = inf.readLong(1LL, 3000000000LL, "K");
    inf.readEoln();

    // 2. Read 영우's cards
    vector<int> youngwoo = inf.readInts(N, 1, 1000000000, "youngwoo_cards");
    inf.readEoln();

    // 3. Read 민우's cards
    vector<int> minwoo = inf.readInts(N, 1, 1000000000, "minwoo_cards");
    inf.readEoln();

    // 4. Read 우진's cards
    vector<int> woojin = inf.readInts(N, 1, 1000000000, "woojin_cards");
    inf.readEoln();

    // No further global constraints specified in the statement.
    // No requirement for all cards to be distinct, or for any other property.

    inf.readEof();
}
