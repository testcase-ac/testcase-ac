#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define X first
#define Y second
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using T = pair<int, pii>;

struct subset {
    int parent;
    int rank;
};

struct subset *subsets;

char buf[1 << 17];

inline char read() {
	static int idx = 1 << 17;
	if (idx == 1 << 17) {
		fread(buf, 1, 1 << 17, stdin);
		idx = 0;
	}
	return buf[idx++];
}
inline int readInt() {
	int sum = 0;
	bool flg = 1;
	char now = read();

	while (now == 10 || now == 32) now = read();
	if (now == '-') flg = 0, now = read();
	while (now >= 48 && now <= 57) {
		sum = sum * 10 + now - 48;
		now = read();
	}

	return flg ? sum : -sum;
}

int find(int i){
    if(subsets[i].parent != i)subsets[i].parent = find(subsets[i].parent);
    return subsets[i].parent;
}

void Union(int x, int y){
    int xroot = find(x);
    int yroot = find(y);
    if(subsets[xroot].rank < subsets[yroot].rank) subsets[xroot].parent = yroot;
    else if(subsets[xroot].rank > subsets[yroot].rank) subsets[yroot].parent = xroot;
    else{
        subsets[yroot].parent = xroot;
        subsets[xroot].rank ++;
    }
}

int main() {
	int v = readInt(), e = readInt();

	int a, b, c;
	vector<T> edge;
	for (int i = 0; i < e; ++i) {
        a = readInt();
        b = readInt();
        c = readInt();
		edge.push_back({ c, { a, b } });
	}

    subsets = (struct subset*) malloc( (v + 1) * sizeof(struct subset) );
    for (int i = 1; i < v + 1; ++i) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

	sort(edge.begin(), edge.end());

	int ans = 0;
	for (T &it : edge) {
		if (find(it.Y.X) == find(it.Y.Y)) continue;
		ans += it.X;
		Union(it.Y.X, it.Y.Y);
	}

	printf("%d", ans);

	return 0;
}
