#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: number of files N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Second line: sizes of the N files
    vector<long long> sizes = inf.readLongs(N, 0LL, 1000000000LL, "size_i");
    inf.readEoln();

    // Third line: cluster size
    long long C = inf.readLong(1LL, 1048576LL, "cluster_size");
    inf.readEoln();

    // No extra data
    inf.readEof();
    return 0;
}
