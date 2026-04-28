#include <cstdio>
#include <algorithm>
#include <unistd.h>
#include <sys/syscall.h>

namespace FIO {
	const size_t BUFFER_SIZE = 1 << 18;
	char buffer[BUFFER_SIZE];
	char* ptr = buffer + BUFFER_SIZE;

	inline char readByte() {
		if (ptr == buffer + BUFFER_SIZE) {
			syscall(0x00, 0, buffer, BUFFER_SIZE);
			ptr = buffer;
		}
		return *ptr++;
	}

	int readInt() {
		int ret = 0;
		unsigned char c = readByte();
		while (c < '-') c = readByte();

		bool neg = false;
		if (c == '-') {
			neg = true;
			c = readByte();
		}
		while (c >= '0') {
			ret = ret * 10 + (c - '0');
			c = readByte();
		}
		return neg ? -ret : ret;
	}

	char outbuf[BUFFER_SIZE + 20];
	char* outp = outbuf;

	void printInt(int n) {
		if (n < 0) n = -n, *outp++ = '-';
		char *end = outp;
		do {
			*end++ = n % 10 + '0';
			n /= 10;
		} while (n);
		std::reverse(outp, end);
		*end++ = ' ';
		if (end < outbuf + BUFFER_SIZE) outp = end;
		else {
			syscall(0x01, 1, outbuf, end - outbuf);
			outp = outbuf;
		}
	}

	void flush() {
		syscall(0x01, 1, outbuf, outp - outbuf);
	}
};


const int MAXN = 1000000;

int arr[MAXN];
int ans[MAXN];

inline int readint() { return FIO::readInt(); }
inline void writeint(int n) { FIO::printInt(n); }
inline void flush() { FIO::flush(); }

int main() {
    int n = readint();

    for (int i = 0; i < n; ++i) {
        arr[i] = readint();
    }

    int e = n;
    for (int i = n; i-- > 0; ) {
        while (e < n && arr[e] <= arr[i]) ++e;
        ans[i] = e < n ? arr[e] : -1;
        arr[--e] = arr[i];
    }

    for (int i = 0; i < n; ++i) {
        writeint(ans[i]);
    }

    flush();
    return 0;
}
