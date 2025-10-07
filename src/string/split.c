#include "extr_string.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#ifndef HAVE_STRNDUP
static char* co_strndup(const char* s, size_t n) {
  char* r = (char*) malloc(n + 1);
  if (!r) return NULL;
  memcpy(r, s, n);
  r[n] = '\0';
  return r;
}
#define strndup co_strndup
#endif

char** split_tokens(const char* str, const char* delims, size_t* count) {
  if (!str) return NULL;

  size_t cap = 16;
  size_t _count = 0;
  char** tokens = (char**) malloc(cap* sizeof(char*));
  if (!tokens) return NULL;

  const char* p = str;
  const char* token_start = NULL;
  _Bool inq = 0;

  #define PUSH_TOKEN(tok) do { \
    if (_count + 2 > cap) { \
      cap *= 2; \
      char** tmp = realloc(tokens, cap * sizeof(char*));  \
      if (!tmp) goto oom; \
      tokens = tmp; \
    } \
    tokens[_count++] = (tok); \
    } while (0)

  while (*p) {
    unsigned char c = (unsigned char)*p;

    if (inq) {
      if (c == '"') {
        char* tok = strndup(token_start, p - token_start);
        if (!tok) goto oom;
        PUSH_TOKEN(tok);
        token_start = NULL;
        inq = 0;
        p++;
      } else {
        p++;
      }
      continue;
    }

    if (c == '"') {
      if (token_start) {
        char* tok = strndup(token_start, p - token_start);
        if (!tok) goto oom;
        PUSH_TOKEN(tok);
        token_start = NULL;
      }
      inq = 1;
      token_start = ++p;
      continue;
    }

    if (isspace(c)) {
      if (token_start) {
        char* tok = strndup(token_start, p - token_start);
        if (!tok) goto oom;
        PUSH_TOKEN(tok);
        token_start = NULL;
      }
      p++;
      continue;
    }

    if (strchr(delims, c)) {
      if (token_start) {
        char* tok = strndup(token_start, p - token_start);
        if (!tok) goto oom;
        PUSH_TOKEN(tok);
        token_start = NULL;
      }

      char dstr[2] = { *p, '\0' };
      char* delcopy = strdup(dstr);
      if (!delcopy) goto oom;
      PUSH_TOKEN(delcopy);
      p++;
      continue;
    }

    if (!token_start)
      token_start = p;
    p++;
  }

  if (token_start) {
    char* tok = strndup(token_start, p - token_start);
    if (!tok) goto oom;
    PUSH_TOKEN(tok);
  }

  tokens[_count] = NULL;
  if (count) *count = _count;
  return tokens;

oom:
  for (size_t i = 0; i < _count; ++i)
    free(tokens[i]);
  free(tokens);
  if (count) *count = 0;
  return NULL;
}

void _core_free_split_arr(char **toks, size_t count) {
  if (!toks) return;
  for (size_t i = 0; i < count; i++)
    free(toks[i]);
  free(toks);
}
