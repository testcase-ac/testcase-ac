#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

using ll = long long;

const ll MAX_K = 1000000000000000LL;

ll boundedMul(ll a, ll b) {
    if (a > MAX_K / b) return MAX_K + 1;
    return a * b;
}

ll powerWithin(ll base, int exp) {
    ll value = 1;
    for (int i = 0; i < exp; ++i) {
        value = boundedMul(value, base);
        if (value > MAX_K) break;
    }
    return value;
}

void addDivisorCandidate(vector<ll>& divisors, ll k, ll d) {
    if (d <= 0 || k % d != 0) return;
    divisors.push_back(d);
    divisors.push_back(k / d);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<ll> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
    int mode = rnd.next(0, 5);
    ll k = 2;
    vector<ll> divisorCandidates;

    if (mode == 0) {
        ll p = rnd.any(smallPrimes);
        int maxExp = 1;
        while (powerWithin(p, maxExp + 1) <= MAX_K) ++maxExp;
        k = powerWithin(p, rnd.next(1, min(maxExp, 18)));
        addDivisorCandidate(divisorCandidates, k, p);
    } else if (mode == 1) {
        k = 1;
        shuffle(smallPrimes.begin(), smallPrimes.end());
        int count = rnd.next(2, 5);
        for (int i = 0; i < count; ++i) {
            int exp = rnd.next(1, 4);
            ll factor = powerWithin(smallPrimes[i], exp);
            if (boundedMul(k, factor) <= MAX_K) k *= factor;
        }
        if (k < 2) k = 2;
        for (ll p : smallPrimes) addDivisorCandidate(divisorCandidates, k, p);
    } else if (mode == 2) {
        ll a = rnd.next(2LL, 1000000LL);
        ll b = rnd.next(2LL, 1000000LL);
        k = a * b;
        addDivisorCandidate(divisorCandidates, k, a);
        addDivisorCandidate(divisorCandidates, k, b);
    } else if (mode == 3) {
        ll base = rnd.next(900000000000000LL, MAX_K);
        k = base - rnd.next(0LL, 1000LL);
        if (k < 2) k = 2;
        for (ll p : smallPrimes) addDivisorCandidate(divisorCandidates, k, p);
    } else if (mode == 4) {
        ll p = rnd.any(smallPrimes);
        int exp = rnd.next(8, 24);
        k = powerWithin(p, exp);
        if (k > MAX_K) k = powerWithin(p, 10);
        ll tail = rnd.next(2LL, 997LL);
        if (boundedMul(k, tail) <= MAX_K) k *= tail;
        addDivisorCandidate(divisorCandidates, k, p);
        addDivisorCandidate(divisorCandidates, k, tail);
    } else {
        k = rnd.next(2LL, 100000LL);
        for (ll p : smallPrimes) addDivisorCandidate(divisorCandidates, k, p);
    }

    int q = rnd.next(1, 30);
    vector<ll> answers;
    answers.reserve(q);

    vector<ll> anchors = {1, k - 1};
    divisorCandidates.push_back(1);
    divisorCandidates.push_back(k);
    sort(divisorCandidates.begin(), divisorCandidates.end());
    divisorCandidates.erase(unique(divisorCandidates.begin(), divisorCandidates.end()), divisorCandidates.end());
    for (ll d : divisorCandidates) {
        if (1 <= d && d < k) anchors.push_back(d);
    }

    for (int i = 0; i < q; ++i) {
        ll value;
        int kind = rnd.next(0, 5);
        if (kind == 0) {
            value = rnd.any(anchors);
        } else if (kind == 1) {
            ll d = rnd.any(divisorCandidates);
            value = max(1LL, min(k - 1, d));
        } else if (kind == 2) {
            ll d = rnd.any(divisorCandidates);
            ll multiplier = rnd.next(1LL, max(1LL, min(1000LL, (k - 1) / d)));
            value = d * multiplier;
        } else if (kind == 3) {
            value = rnd.next(1LL, min(k - 1, 1000000LL));
        } else if (kind == 4) {
            ll delta = rnd.next(1LL, min(k - 1, 1000000LL));
            value = k - delta;
        } else {
            value = rnd.next(1LL, k - 1);
        }
        answers.push_back(max(1LL, min(k - 1, value)));
    }

    println(k, q);
    println(answers);
    return 0;
}
