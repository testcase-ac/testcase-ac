#include <cstdio>
#include <algorithm>
using namespace std;

void proc() {
    pair<int, int> p[3];
    for (int i = 0; i < 3; ++i) {
        scanf("%d %d", &p[i].first, &p[i].second);
    }
    sort(p, p + 3);
    do {
        for (int i = 0; i < 2; ++i) {
            for (int j = 0; j < 2; ++j) {
                for (int k = 0; k < 2; ++k) {
                    if (p[0].first == p[1].first && p[0].first == p[2].first) {
                        if (p[0].first == p[0].second + p[1].second + p[2].second) {
                            putchar('1');
                            return;
                        }
                    }
                    if (p[0].first == p[1].first + p[2].first && p[1].second == p[2].second) {
                        if (p[0].first == p[0].second + p[1].second) {
                            putchar('1');
                            return;
                        }
                    }

                    swap(p[2].first, p[2].second);    
                }
                swap(p[1].first, p[1].second);
            }
            swap(p[0].first, p[0].second);
        }
    } while (next_permutation(p, p + 3));
    putchar('0');
}

int main() {
    //freopen("input.txt", "r", stdin);
    proc();
    return 0;
}
