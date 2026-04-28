#include <bits/stdc++.h>
#include <unistd.h>
#include <sys/syscall.h>
using namespace std;

namespace fio {
	const int BSIZE = 2097152;
	char buffer[BSIZE];
	auto p = buffer + BSIZE;
	inline char readChar() {
		if (p == buffer + BSIZE) {
			syscall(0x00, 0, buffer, BSIZE);
			p = buffer;
		}
		return *p++;
	}
	int readInt() {
		char c = readChar();
		while (c < '-') {
			c = readChar();
		}
		int ret = 0;
		while (c >= '-') {
			ret = ret * 10 + c - '0';
			c = readChar();
		}
		return ret;
	}

	unsigned char outbuf[BSIZE];
	unsigned char *outp = outbuf;

	inline void printans(bool ans)
	{
		*outp++ = ans + '0';
		*outp++ = '\n';
	}

	void flush()
	{
		syscall(0x01, 1, outbuf, outp - outbuf);
	}
}

int str[2000005];
int plen[2000005];
int n;

// find longest palindromic span for each element in str
// O(|str|)
void manacher() {
	int r = -1, p = -1;
	for (int i = 0; i < n; ++i) {
		if (i <= r)
			plen[i] = min((2 * p - i >= 0) ? plen[2 * p - i] : 0, r - i);
		else
			plen[i] = 0;
		while (i - plen[i] - 1 >= 0 && i + plen[i] + 1 < n
			&& str[i - plen[i] - 1] == str[i + plen[i] + 1]) {
			plen[i] += 1;
		}
		if (i + plen[i] > r) {
			r = i + plen[i];
			p = i;
		}
	}
}

int main()
{
	n = fio::readInt() * 2 - 1;

	for (int i = 0; i < n; i++)
	{
		if (i % 2) str[i] = -1;
		else str[i] = fio::readInt();
	}

	manacher();

	int m = fio::readInt();
	while (m--)
	{
		int a, b;
		a = (fio::readInt() - 1) * 2;
		b = (fio::readInt() - 1) * 2;
		int mid = (a + b) / 2;
		fio::printans(b - mid <= plen[mid]);
	}
	fio::flush();
	_Exit(0);
}
