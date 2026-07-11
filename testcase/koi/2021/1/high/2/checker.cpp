// https://github.com/MikeMirzayanov/testlib/blob/b4be380c7a96542ecf652bd7896a187de30fa267/testlib.h
#include "testlib.h"

#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;

struct bigint {
    std::vector<int> v;

    bigint(): v(1,1) { }

    void operator*= (long long x) {
        std::vector<int> w;
        while(x > 0) {
            w.push_back(x % 10);
            x /= 10;
        }

        std::vector<int> nxt(v.size() + w.size() + 10);
        for (int i = 0; i < v.size(); i++) {
            for (int j = 0; j < w.size(); j++) {
                nxt[i + j] += v[i] * w[j];
            }
        }
        for (int i = 0; i < nxt.size(); i++) {
            if (nxt[i] >= 10) {
                nxt[i+1] += nxt[i] / 10;
                nxt[i] %= 10;
            }
        }
        while (!nxt.empty() && nxt.back() == 0) {
            nxt.pop_back();
        }
        v = nxt;
    }

    bool operator< (const bigint &other) const {
        if (v.size() != other.v.size()) {
            return v.size() < other.v.size();
        }
        for (int i = v.size(); --i >= 0; ) {
            if (v[i] != other.v[i]) {
                return v[i] < other.v[i];
            }
        }
        return false;
    }

    bool operator== (const bigint &other) const {
        return v == other.v;
    }
};

int n, k;
int a[4];
multiset<pii> S;

bigint readAns(InStream& stream) {
	multiset<pii> T(S.begin(), S.end());

	long long b[4] = {};
	for (int i = 0; i < 4; i++)
		b[i] = a[i];

	for (int i = 0; i < k; i++) {
		char t1 = stream.readToken("[ABCD]{1}")[0];
		int t2 = stream.readInt();

		auto it = T.find(make_pair(t1 - 'A', t2));
		stream.quitif(it == T.end(), _wa, format("Card [%c,%d] not remains in set", t1, t2).c_str());
		T.erase(it);
		b[t1 - 'A'] += t2;
	}
	bigint mul;
	for (int i = 0; i < 4; i++) {
		mul *= b[i];
	}
	return mul;
}

int main(int argc, char* argv[]) {
	registerTestlibCmd(argc, argv);

	n = inf.readInt();
	k = inf.readInt();

	for (int i = 0; i < 4; i++)
		a[i] = inf.readInt();
	for (int i = 0; i < n; i++) {
		char t1 = inf.readToken()[0];
		int t2 = inf.readInt();
		S.emplace(t1 - 'A', t2);
	}

	bigint ans_jury = readAns(ans);
	bigint ans_part = readAns(ouf);

	if (ans_jury < ans_part)
		quitf(_fail, "Participant has better answer");
	else if (ans_part == ans_jury)
		quitf(_ok, "OK");
	else
		quitf(_wa, "Participant has Smaller Answer");

	return 0;
}
