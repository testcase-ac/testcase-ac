#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static int compareDecimal(const string& a, const string& b) {
    if (a.size() != b.size()) {
        return a.size() < b.size() ? -1 : 1;
    }
    if (a == b) {
        return 0;
    }
    return a < b ? -1 : 1;
}

static string addDecimal(const string& a, const string& b) {
    string result;
    int carry = 0;
    int i = (int)a.size() - 1;
    int j = (int)b.size() - 1;
    while (i >= 0 || j >= 0 || carry > 0) {
        int sum = carry;
        if (i >= 0) {
            sum += a[i--] - '0';
        }
        if (j >= 0) {
            sum += b[j--] - '0';
        }
        result.push_back(char('0' + (sum % 10)));
        carry = sum / 10;
    }
    reverse(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    vector<string> values;
    values.reserve(T);
    for (int tc = 0; tc < T; ++tc) {
        string s = inf.readToken("[0-9]+", "F_n");
        inf.readEoln();

        ensuref(s[0] != '0', "leading zero in F_n at testcase %d: %s",
                tc + 1, s.c_str());
        ensuref((int)s.size() <= 21001,
                "F_n at testcase %d has too many digits: %d", tc + 1,
                (int)s.size());
        values.push_back(s);
    }

    inf.readEof();

    vector<int> order(T);
    for (int i = 0; i < T; ++i) {
        order[i] = i;
    }
    sort(order.begin(), order.end(), [&](int a, int b) {
        if (values[a].size() != values[b].size()) {
            return values[a].size() < values[b].size();
        }
        return values[a] < values[b];
    });

    string prev = "0";
    string cur = "1";
    int next = 0;
    for (int n = 1; n <= 100000 && next < T; ++n) {
        while (next < T && values[order[next]] == cur) {
            ++next;
        }
        while (next < T && compareDecimal(values[order[next]], cur) < 0) {
            int tc = order[next] + 1;
            ensuref(false,
                    "F_n at testcase %d is not a Fibonacci number with "
                    "1 <= n <= 100000: %s",
                    tc, values[order[next]].c_str());
        }
        string nxt = addDecimal(prev, cur);
        prev = cur;
        cur = nxt;
    }

    for (; next < T; ++next) {
        int tc = order[next] + 1;
        ensuref(false,
                "F_n at testcase %d is not a Fibonacci number with "
                "1 <= n <= 100000: %s",
                tc, values[order[next]].c_str());
    }

    for (int tc = 0; tc < T; ++tc) {
        if ((int)values[tc].size() == 21001) {
            ensuref(values[tc] == "1" + string(21000, '0'),
                    "F_n at testcase %d exceeds 10^21000: %s", tc + 1,
                    values[tc].c_str());
        }
    }

    return 0;
}
