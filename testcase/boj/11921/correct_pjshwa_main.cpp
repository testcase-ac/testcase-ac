# pragma GCC optimize ("O3")
# pragma GCC optimize ("Ofast")
# pragma GCC optimize ("unroll-loops")

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

static inline int uintSize(int n){
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

int main() {
  int n = readInt();
  long long s = 0;
  for (int i = 0; i < n; i++) s += readInt();
  printf("%d\n%lld\n", n, s);
}
