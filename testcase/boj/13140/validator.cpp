#include "testlib.h"
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    // "첫 번째 줄에 양의 정수 N이 주어진다. N은 32비트 정수 범위로 표현할 수 있는 수만 들어온다."
    // So: 1 <= N <= 2147483647
    // Also, must not have leading zeros.

    string N_str = inf.readToken("[0-9]+", "N");
    inf.readEoln();

    // Check no leading zeros unless N == "0"
    ensuref(N_str.size() == 1 || N_str[0] != '0', "N has unnecessary leading zeros");

    // Check N in [1, 2147483647]
    ensuref(N_str.size() <= 10, "N is too large (more than 10 digits)");
    long long N = 0;
    for (char c : N_str) {
        N = N * 10 + (c - '0');
    }
    ensuref(1LL <= N && N <= 2147483647LL, "N is out of range: %lld", N);

    inf.readEof();
}
