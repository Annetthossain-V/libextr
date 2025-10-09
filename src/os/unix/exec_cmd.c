#include "exec_cmd.h"
#include "../../string/extr_string.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdlib.h>

bool exec_cmd(const char *cmd, const bool wait, int *code) {
  size_t split_len = 0;
  char** split = split_tokens(cmd, " ", &split_len);

  pid_t child = fork();
  if (child < 0)
    return false;

  if (child == 0) {
    execvp(split[0], split);
    perror("execvp");
    exit(EXIT_FAILURE);
  } else {
    if (wait)
      waitpid(child, code, 0);
  }

  _core_free_split_arr(split, split_len);
  return true;
}
