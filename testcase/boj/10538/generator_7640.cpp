#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Pattern size
    int hp = rnd.next(1, 10);
    int wp = rnd.next(1, 10);
    // Masterpiece size, at least as big as pattern, up to +10
    int hm = rnd.next(hp, hp + rnd.next(0, 10));
    int wm = rnd.next(wp, wp + rnd.next(0, 10));
    // Generate pattern with random density
    double pd = rnd.next(0.0, 1.0);
    vector<string> pat(hp, string(wp, 'x'));
    for (int i = 0; i < hp; i++)
        for (int j = 0; j < wp; j++)
            pat[i][j] = (rnd.next() < pd ? 'x' : 'o');
    // Generate masterpiece background with random density
    double bd = rnd.next(0.0, 1.0);
    vector<string> big(hm, string(wm, 'x'));
    for (int i = 0; i < hm; i++)
        for (int j = 0; j < wm; j++)
            big[i][j] = (rnd.next() < bd ? 'x' : 'o');
    // List all possible placement positions
    vector<pair<int,int>> poss;
    for (int i = 0; i + hp <= hm; i++)
        for (int j = 0; j + wp <= wm; j++)
            poss.emplace_back(i, j);
    shuffle(poss.begin(), poss.end());
    int maxpos = poss.size();
    // Choose bias parameter for number of embeddings
    vector<int> Ts = {-2, -1, 0, 1, 2};
    int t = rnd.any(Ts);
    // Number of times to embed the pattern (may overlap)
    int k = rnd.wnext(maxpos + 1, t);
    if (k > maxpos) k = maxpos;
    // Embed pattern at first k shuffled positions
    for (int idx = 0; idx < k; idx++) {
        int si = poss[idx].first;
        int sj = poss[idx].second;
        for (int di = 0; di < hp; di++)
            for (int dj = 0; dj < wp; dj++)
                big[si + di][sj + dj] = pat[di][dj];
    }
    // Output
    println(hp, wp, hm, wm);
    for (auto &row : pat) println(row);
    for (auto &row : big) println(row);
    return 0;
}
