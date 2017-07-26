#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static volatile signed long long int total = 0;

void worker(void * ctxt) {
  // code
  pthread_exit(&myresult);
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Error: Must be called with number of threads.\n");
    return 1;
  }

  int N = atoi(argv[1]);

  pthread_t threads[N];
  pthread_attr_t thread_attrs[N];

  for (int n = 0; n < N; ++n) {
    pthread_create(&threads[n], &thread_attrs[n], worker, &mydata);
  }

  for (int n = 0; n < N; ++n) {
    int e = pthread_join(threads[n], &myresult);
  }

  // for (int i = 0; i < 10000; ++i) {
  //   for (int j = 1; j <= 1000000; ++j) {
  //     total += j;
  //   }
  // }

  printf("%lli\n", total);

  return 0;
}
