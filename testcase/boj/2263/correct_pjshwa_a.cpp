#include <vector>
#include <cassert>
#include <algorithm>
#define SZ(v) ((int) v.size())
#include <stdio.h>
#include <string.h>
#define __BUFSIZE 2097152
#define __BLANK(c) (c == ' ' \
					|| c == '\n' \
					|| c == '\t' \
					|| c == '\v' \
					|| c == '\f' \
					|| c == '\r')
#define __ENDL(c) (c == '\n')
#define __END(c) (c == '\0')

char __RBUF[__BUFSIZE], __WBUF[__BUFSIZE];
int __RIDX, __NIDX, __WIDX, __END_FLAG;

inline int isEnd(){
	return __END_FLAG;
}

inline char readChar(){
	if (__RIDX == __NIDX){
		__NIDX = fread(__RBUF, sizeof(char), __BUFSIZE, stdin);
		if (__NIDX == 0){
			__END_FLAG = 1;
			return 0;
		}
		__RIDX = 0;
	}
	return __RBUF[__RIDX ++];
}

inline size_t readString(char* dest, int maxl){
	size_t idx = 0;
	char cur;

	if (maxl == 0){
		*dest = 0;
		return 0;
	}

	cur = readChar();

	while (__BLANK(cur))
		cur = readChar();

	while (!__BLANK(cur) && !__END(cur) && idx < (unsigned) maxl){
		*(dest + idx ++) = cur;
		cur = readChar();
	}

	*(dest + idx) = 0;

	return idx;
}

inline size_t readLine(char *dest, int maxl){
	size_t idx = 0;
	char cur;

	if (maxl == 0){
		*dest = 0;
		return 0;
	}

	cur = readChar();

	while (!__ENDL(cur) && !__END(cur) && idx < (unsigned) maxl){
		*(dest + idx ++) = cur;
		cur = readChar();
	}

	*(dest + idx) = 0;

	return idx;
}

inline int readInt(){
	int res = 0;
	char cur = readChar();
	int flag = 0;

	while (__BLANK(cur))
		cur = readChar();

	if (cur == '-'){
		flag = 1;
		cur = readChar();
	}

	while (!__BLANK(cur) && !__END(cur)){
		res = 10 * res + cur - '0';
		cur = readChar();
	}

	return flag ? -res : res;
}

inline double readDouble(){
	/* Not yet implemented */
	return 0;
}

inline long long readLL(){
	long long res = 0;
	char cur = readChar();
	int flag = 0;

	while (__BLANK(cur))
		cur = readChar();

	if (cur == '-'){
		flag = 1;
		cur = readChar();
	}

	while (!__BLANK(cur) && !__END(cur)){
		res = 10 * res + cur - '0';
		cur = readChar();
	}

	return flag ? -res : res;
}

static inline int uintSize(int n){
	int isz = 1;
	if (n < 0) n = -n;

	while (n >= 10){
		isz ++;
		n /= 10;
	}

	return isz;
}

inline int ullintSize(long long n){
	int isz = 1;
	if (n < 0) n = -n;

	while (n >= 10){
		isz ++;
		n /= 10;
	}

	return isz;
}

inline void bflush(){
	fwrite(__WBUF, sizeof(char), __WIDX, stdout);
	__WIDX = 0;
}

inline void writeChar(char c){
	if (__WIDX == __BUFSIZE){
		bflush();
	}
	__WBUF[__WIDX ++] = c;
}

inline void newLine(){
	writeChar('\n');
}

inline void writeString(const char* s){
	int len = strlen(s);
	if (__WIDX + len >= __BUFSIZE){
		bflush();
	}
	int next = __WIDX + len;

	while (len --){
		__WBUF[__WIDX + len] = *(s + len);
	}
	__WIDX = next;
}

inline void writeInt(int n){
	int isz = uintSize(n);
	if (__WIDX + isz >= __BUFSIZE){
		bflush();
	}
	if (n < 0){
		n = -n;
		__WBUF[__WIDX ++] = '-';
	}
	int next = __WIDX + isz;

	while (isz --){
		__WBUF[__WIDX + isz] = n % 10 + '0';
		n /= 10;
	}
	__WIDX = next;
}

inline void writeDouble(double d){
	/* Not yet implemented */
	return;
}

inline void writeLL(long long n){
	int isz = ullintSize(n);
	if (__WIDX + isz >= __BUFSIZE){
		bflush();
	}
	if (n < 0){
		n = -n;
		__WBUF[__WIDX ++] = '-';
	}
	int next = __WIDX + isz;

	while (isz --){
		__WBUF[__WIDX + isz] = n % 10 + '0';
		n /= 10;
	}
	__WIDX = next;
}

inline void writeCharLn(char c){
	writeChar(c);
	newLine();
}

inline void writeStringLn(const char* s){
	writeString(s);
	newLine();
}

inline void writeIntLn(int n){
	writeInt(n);
	newLine();
}

inline void writeDoubleLn(double d){
	/* Not yet implemented */
	newLine();
}

inline void writeLLLn(long long n){
	writeLL(n);
	newLine();
}

using namespace std;

int n, a[100003], b[100003], idx[100003];

void solve(int as, int ae, int bs, int be){
	assert(ae-as == be-bs);
	if (as > ae || bs > be) return;
	writeInt(b[be]);
    writeChar(' ');
	if (bs == be) return;
    int am = idx[b[be]]-1, bm = am - as + bs;
	solve(as, am, bs, bm);
	solve(am+2, ae, bm+1, be-1);
}

int main(){
	n = readInt();
	for (int i=0; i<n; i++){
		a[i] = readInt();
        idx[a[i]] = i;
	}
	for (int i=0; i<n; i++){
		b[i] = readInt();
	}
	solve(0, n-1, 0, n-1);
	newLine();
    bflush();
	return 0;
}
