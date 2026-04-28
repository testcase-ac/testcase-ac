#include <cstdio>
#include <vector>

using namespace std;

vector<int> list;
char		buf[0x40000];
int			number[500000],
			idx, bytes;
long long	checked[1562500];

inline static int read() {
	if (!(idx ^ bytes)) {
		buf[bytes = fread(buf, sizeof(char), sizeof buf - 1, stdin)] = 0x0A;
		idx = 0;
	}
	return buf[idx++];
}
inline static int parse() {
	int ret = 0,
		num = read();

	while (0x30 <= num && num <= 0x39) {
		ret = ret*10 + (num & 0x0F);
		num = read();
	}
	return ret;
}

int main() {
	int n = parse(),
		m = parse();

	for (int i = 0; i < m; i++)
		number[i] = parse();
	while (m--) {
		int index = number[m] >> 6,
			hash  = number[m] & 63;

		if (!(checked[index] & (1LL << hash))) {
			checked[index] |= 1LL << hash;
			list.push_back(number[m]);
		}
 	}
	m = list.size();

	while (n-- && m--)
		printf("%08d\n", list[m]);
}

// https://www.acmicpc.net/source/8831532
