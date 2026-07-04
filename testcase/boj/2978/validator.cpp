#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

static bool isCanonicalPositiveInteger(const string& value) {
    return !value.empty() && value[0] != '0';
}

static int parseSmallPositiveInteger(const string& value) {
    int result = 0;
    for (char digit : value) {
        result = result * 10 + (digit - '0');
    }
    return result;
}

static bool hasValidPlusInsertion(const string& a, int target) {
    vector<vector<unsigned char>> reachable(a.size() + 1,
                                            vector<unsigned char>(target + 1, 0));
    reachable[0][0] = 1;

    for (int start = 0; start < (int)a.size(); ++start) {
        bool hasReachablePrefix = false;
        for (int sum = 0; sum <= target; ++sum) {
            if (reachable[start][sum]) {
                hasReachablePrefix = true;
                break;
            }
        }
        if (!hasReachablePrefix) {
            continue;
        }

        int value = 0;
        for (int end = start; end < (int)a.size(); ++end) {
            value = value * 10 + (a[end] - '0');
            if (value > target) {
                break;
            }
            for (int sum = 0; sum + value <= target; ++sum) {
                if (reachable[start][sum]) {
                    reachable[end + 1][sum + value] = 1;
                }
            }
        }
    }

    return reachable[a.size()][target];
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string equation = inf.readLine("[0-9]{1,1000}=[0-9]{1,4}", "equation");
    inf.readEof();

    size_t equalPos = equation.find('=');
    ensuref(equalPos != string::npos, "equation must contain '='");

    string a = equation.substr(0, equalPos);
    string sText = equation.substr(equalPos + 1);

    ensuref(isCanonicalPositiveInteger(a), "A must be a positive integer without leading zeroes");
    ensuref(isCanonicalPositiveInteger(sText), "S must be a positive integer without leading zeroes");
    ensuref(a != sText, "A and S must be different");

    int s = parseSmallPositiveInteger(sText);
    ensuref(s <= 5000, "S must be at most 5000, found %d", s);
    ensuref(hasValidPlusInsertion(a, s),
            "no insertion of plus signs makes A sum to S");

    return 0;
}
