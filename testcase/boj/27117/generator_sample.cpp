#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 7) {
        n = rnd.next(50, 200);
    } else {
        n = rnd.next(2, 20);
    }

    vector<int> ticket(n);
    for (int i = 0; i < n; ++i) ticket[i] = i + 1;

    if (mode == 1) {
        reverse(ticket.begin(), ticket.end());
    } else if (mode == 2) {
        rotate(ticket.begin(), ticket.begin() + rnd.next(1, n - 1), ticket.end());
    } else if (mode == 3) {
        shuffle(ticket.begin(), ticket.end());
    } else if (mode == 4) {
        int swaps = rnd.next(1, max(1, n / 2));
        for (int i = 0; i < swaps; ++i) {
            int a = rnd.next(0, n - 1);
            int b = rnd.next(0, n - 1);
            while (b == a) b = rnd.next(0, n - 1);
            swap(ticket[a], ticket[b]);
        }
    } else if (mode == 5) {
        int block = rnd.next(2, n);
        shuffle(ticket.begin(), ticket.begin() + block);
    } else if (mode == 6) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i;
        shuffle(order.begin(), order.end());
        int last = ticket[order.back()];
        for (int i = n - 1; i > 0; --i) {
            ticket[order[i]] = ticket[order[i - 1]];
        }
        ticket[order[0]] = last;
    } else if (mode == 7) {
        shuffle(ticket.begin(), ticket.end());
        int sortedPrefix = rnd.next(0, n / 2);
        for (int i = 0; i < sortedPrefix; ++i) {
            auto it = find(ticket.begin(), ticket.end(), i + 1);
            swap(ticket[i], *it);
        }
    }

    println(n);
    println(ticket);
    return 0;
}
