#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static volatile signed long long int total = 0;
pthread_mutex_t mutex_total;

struct worker_context {
  int repeat;
};

void * Worker(void * ctxt) {
  struct worker_context * context;
  context = (struct worker_context *) ctxt;

  for (int i = 0; i < context->repeat; ++i) {
    for (int j = 1; j <= 1000000; ++j) {
      pthread_mutex_lock(&mutex_total);
      total += j;
      pthread_mutex_unlock(&mutex_total);
    }
  }

  pthread_exit(NULL);
}

int main(int argc, char * argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Error: Must be called with number of threads.\n");
    exit(EXIT_FAILURE);
  }

  int N = atoi(argv[1]);
  int repeat = 100;
  int repetitions_per_thread = repeat / N;
  int excess = repeat % N;

  pthread_t threads[N];
  struct worker_context thread_contexts[N];

  pthread_mutex_init(&mutex_total, NULL);

  for (int n = 0; n < N; ++n) {
    thread_contexts[n].repeat = repetitions_per_thread + (n < excess ? 1 : 0);
    int e = pthread_create(&threads[n], NULL, Worker, (void *) &thread_contexts[n]);

    if (e) {
      fprintf(stderr, "Error: Could not create threads.\n%i\n", e);
      exit(EXIT_FAILURE);
    }
  }

  void * status;

  for (int n = 0; n < N; ++n) {
    int e = pthread_join(threads[n], &status);

    if (e) {
      fprintf(stderr, "Error: Could not join threads.\n");
      exit(EXIT_FAILURE);
    }
  }

  pthread_mutex_destroy(&mutex_total);

  printf("%lli\n", total);
  return EXIT_SUCCESS;
}
