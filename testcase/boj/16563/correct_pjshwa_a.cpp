#include <cstdio>
#include <iostream>
using namespace std;

int sieve[5000001]{ 1, 1 };
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
int main() {
    ios::sync_with_stdio(false);
	int t = readInt();

	for (int i = 2; i * i <= 5000000; ++i) if (!sieve[i])
		for (int j = i * i; j <= 5000000; j += i) if (!sieve[j]) sieve[j] = i;

	int n;
	while (t--) {
		n = readInt();

		while (sieve[n]) {
            cout << sieve[n] << ' ';
			n /= sieve[n];
		}
        cout << n << '\n';
	}

	return 0;
}
