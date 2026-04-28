#include <cstdio>
#include <cstring>

char a[10004];
char b[10004];

int main(void){
	scanf("%s %s", a, b);

  int curry = 0;
  int c_i, j;
  int a_size = strlen(a);
  int b_size = strlen(b);

  if (a_size < b_size) {
    for (int i = a_size - 1; i >= 0; i--) {
      j = i + (b_size - a_size);
      c_i = a[i] + b[j] - 96;

      if (curry) c_i++;
      curry = c_i / 10;
      b[j] = (c_i % 10) + 48;
    }

    while (curry && j >= 0) {
      j--;
      c_i = b[j] - 48 + 1;
      curry = c_i / 10;
      b[j] = (c_i % 10) + 48;
    }

    if (curry) printf("1%s\n", b);
    else printf("%s\n", b);
  }
  else {
    for (int i = b_size - 1; i >= 0; i--) {
      j = i + (a_size - b_size);
      c_i = a[j] + b[i] - 96;

      if (curry) c_i++;
      curry = c_i / 10;
      a[j] = (c_i % 10) + 48;
    }

    while (curry && j >= 0) {
      j--;
      c_i = a[j] - 48 + 1;
      curry = c_i / 10;
      a[j] = (c_i % 10) + 48;
    }

    if (curry) printf("1%s\n", a);
    else printf("%s\n", a);
  }

}
