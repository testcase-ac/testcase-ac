#include "testlib.h"
#include <vector>
#include <map>
using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input numbers
    vector<int> a(10);
    long long sum = 0;
    map<int,int> freq;
    for (int i = 0; i < 10; i++) {
        a[i] = inf.readInt(1, 1000, format("a[%d]", i+1).c_str());
        sum += a[i];
        freq[a[i]]++;
    }
    // Compute true average and max frequency
    int true_avg = sum / 10;
    int maxfreq = 0;
    for (auto &kv : freq)
        maxfreq = max(maxfreq, kv.second);
    // Read participant output
    int p_avg = ouf.readInt(1, 1000, "average");
    int p_mode = ouf.readInt(1, 1000, "mode");
    ouf.readEof();
    // Check average
    if (p_avg != true_avg) {
        quitf(_wa, "wrong average: expected %d, found %d", true_avg, p_avg);
    }
    // Check mode: must have highest frequency
    auto it = freq.find(p_mode);
    int p_freq = (it == freq.end() ? 0 : it->second);
    if (p_freq != maxfreq) {
        quitf(_wa, "wrong mode: %d appears %d time(s), but maximum frequency is %d",
              p_mode, p_freq, maxfreq);
    }
    // All good
    quitf(_ok, "average = %d, mode = %d", p_avg, p_mode);
}
