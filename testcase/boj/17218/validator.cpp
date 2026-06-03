#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

static int lcsLength(const string& a, const string& b) {
    int n = (int)a.size();
    int m = (int)b.size();
    vector<vector<int>> len(n + 1, vector<int>(m + 1, 0));

    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            if (a[i] == b[j]) {
                len[i][j] = len[i + 1][j + 1] + 1;
            } else {
                len[i][j] = max(len[i + 1][j], len[i][j + 1]);
            }
        }
    }

    return len[0][0];
}

static long long countDistinctLcs(const string& a, const string& b) {
    int n = (int)a.size();
    int m = (int)b.size();
    vector<vector<int>> len(n + 1, vector<int>(m + 1, 0));
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            len[i][j] = a[i] == b[j] ? len[i + 1][j + 1] + 1
                                     : max(len[i + 1][j], len[i][j + 1]);
        }
    }

    vector<vector<long long>> memo(n + 1, vector<long long>(m + 1, -1));
    auto countFrom = [&](auto&& self, int i, int j) -> long long {
        long long& ret = memo[i][j];
        if (ret != -1) {
            return ret;
        }
        if (len[i][j] == 0) {
            return ret = 1;
        }
        long long ways = 0;
        for (char ch = 'A'; ch <= 'Z'; ++ch) {
            int ni = i;
            while (ni < n && a[ni] != ch) {
                ++ni;
            }
            int nj = j;
            while (nj < m && b[nj] != ch) {
                ++nj;
            }
            if (ni == n || nj == m || len[ni + 1][nj + 1] + 1 != len[i][j]) {
                continue;
            }
            ways += self(self, ni + 1, nj + 1);
            if (ways >= 2) {
                return ret = 2;
            }
        }
        return ret = ways;
    };

    return countFrom(countFrom, 0, 0);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string first = inf.readToken("[A-Z]{1,40}", "first");
    inf.readEoln();
    string second = inf.readToken("[A-Z]{1,40}", "second");
    inf.readEoln();
    inf.readEof();

    ensuref(lcsLength(first, second) > 0, "longest common subsequence must be nonempty");
    ensuref(countDistinctLcs(first, second) == 1, "longest common subsequence must be unique");
}
