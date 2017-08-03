#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdatomic.h>

static volatile atomic_llong total;

struct worker_context {
  int repeat;
};

void * Worker(void * ctxt) {
  struct worker_context * context;
  context = (struct worker_context *) ctxt;

  for (int i = 0; i < context->repeat; ++i) {
    for (int j = 1; j <= 1000000; ++j) {
      atomic_fetch_add(&total, j);
    }
  }

  pthread_exit(NULL);
}

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Error: Must be called with number of threads.\n");
    exit(-1);
  }

  int N = atoi(argv[1]);
  int repeat = 10000;
  int repetitions_per_thread = repeat / N;
  int excess = repeat % N;

  pthread_t threads[N];
  struct worker_context thread_contexts[N];

  for (int n = 0; n < N; ++n) {
    thread_contexts[n].repeat = repetitions_per_thread + (n < excess ? 1 : 0);
    int e = pthread_create(&threads[n], NULL, Worker, (void *) &thread_contexts[n]);

    if (e) {
      fprintf(stderr, "Error: Could not create threads.\n%i\n", e);
      exit(-1);
    }
  }

  void * status;

  for (int n = 0; n < N; ++n) {
    int e = pthread_join(threads[n], &status);

    if (e) {
      fprintf(stderr, "Error: Could not join threads.\n");
      exit(-1);
    }
  }

  printf("%lli\n", total);

  return 0;
}
