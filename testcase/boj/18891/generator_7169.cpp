#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of parties
    int P = rnd.next(6, 12);
    // Generate unique party names
    vector<string> names(P);
    for (int i = 0; i < P; i++) {
        names[i] = "party_";
        names[i] += char('a' + i);
    }
    // Choose special indices: vote-only and seat-only
    int vote_idx = rnd.next(0, P - 1);
    int seat_idx = rnd.next(0, P - 2);
    if (seat_idx >= vote_idx) seat_idx++;
    // Big party index (distinct)
    vector<int> avail;
    for (int i = 0; i < P; i++) if (i != vote_idx && i != seat_idx) avail.push_back(i);
    int big_idx = avail[rnd.next(0, (int)avail.size() - 1)];
    // Generate region (district) seats
    vector<int> r(P, 0);
    r[seat_idx] = rnd.next(5, 20);
    int rem_max = 253 - r[seat_idx];
    int rem_R = rnd.next(0, rem_max);
    // Random weights for distributing rem_R
    vector<double> w_r(P, 0.0);
    double sum_wr = 0;
    for (int i = 0; i < P; i++) {
        if (i == seat_idx) continue;
        w_r[i] = rnd.next();
        sum_wr += w_r[i];
    }
    for (int i = 0; i < P; i++) {
        if (i == seat_idx) continue;
        if (sum_wr > 0)
            r[i] = int(w_r[i] / sum_wr * rem_R);
        else
            r[i] = 0;
    }
    int used_R = r[seat_idx];
    for (int i = 0; i < P; i++) if (i != seat_idx) used_R += r[i];
    int left_R = r[seat_idx] + rem_R - used_R;
    // Actually left_R = rem_R - sum(r[i] for i!=seat)
    left_R = rem_R - accumulate(r.begin(), r.end(), 0) + r[seat_idx];
    while (left_R-- > 0) {
        int i;
        do { i = rnd.next(0, P - 1); } while (i == seat_idx);
        r[i]++;
    }
    // Total votes V
    long long V;
    if (rnd.next(0,1) == 0) V = rnd.next(1000, 50000);
    else V = rnd.next(50001, 1000000);
    // Threshold for 3%
    long long threshold = (3 * V + 99) / 100;
    // Assign votes
    vector<long long> c(P, 0);
    c[vote_idx] = threshold;
    c[seat_idx] = max(0LL, threshold - 1);
    // Big party votes
    long long big_lo = threshold * 2;
    long long big_hi = V / 2;
    if (big_lo > big_hi) big_lo = threshold;
    c[big_idx] = rnd.next(big_lo, big_hi);
    // Remaining votes
    long long sum_spec = c[vote_idx] + c[seat_idx] + c[big_idx];
    long long rem_votes = V - sum_spec;
    vector<int> rest;
    for (int i = 0; i < P; i++)
        if (i != vote_idx && i != seat_idx && i != big_idx)
            rest.push_back(i);
    if (rem_votes < 0) rem_votes = 0;
    // Distribute rem_votes among rest by weights
    vector<double> w_v(P, 0.0);
    double sum_wv = 0;
    for (int i : rest) {
        w_v[i] = rnd.next();
        sum_wv += w_v[i];
    }
    for (int i : rest) {
        if (sum_wv > 0)
            c[i] = int(w_v[i] / sum_wv * rem_votes);
        else
            c[i] = 0;
    }
    long long used_v = 0;
    for (int i : rest) used_v += c[i];
    long long left_v = rem_votes - used_v;
    while (left_v-- > 0 && !rest.empty()) {
        int idx = rest[rnd.next(0, (int)rest.size() - 1)];
        c[idx]++;
    }
    // Prepare and shuffle output lines
    struct Party { string name; int r; long long c; };
    vector<Party> parties;
    for (int i = 0; i < P; i++)
        parties.push_back({names[i], r[i], c[i]});
    shuffle(parties.begin(), parties.end());
    // Output
    println(P, V);
    for (auto &p : parties)
        println(p.name, p.r, p.c);
    return 0;
}
