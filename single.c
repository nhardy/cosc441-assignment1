#include <stdio.h>
#include <stdlib.h>

static signed long long int total = 0;

int main() {
  for (int i = 0; i < 10000; ++i) {
    for (int j = 1; j <= 1000000; ++j) {
      total += j;
    }
  }

  printf("%lld\n", total);
  return EXIT_SUCCESS;
}
