/*
#include "main/compiler/lexer.h"

#include <stdbool.h>

//--- struct ---//
struct lexer {
  str_ascii source;
  uint32_t index;
};

//--- private ---//
char wschars[] = {' ',  '\t', '\n',
                  '\v', '\f', '\r'};
bool is_whitespace(char ch) {
  for (int i = 0; i < 6; i++) {
    if (wschars[i] == ch) {
      return true;
    }
  }
  return false;
}
void consume_whitepspace(lexer *lex) {

  while (is_whitespace(*lex->cur)) {
    lex->cur++;
  }
}

char cur_char(lexer *lex) {
  return is_whitespace(str_ascii_at(
      *lex->source, lex->index));
}

//--- lexer ---//
lexer lexer_make(str_ascii source) {
  lexer lex;
  lex.source = source;
  lex.cur = 0;
  return lex;
}
void lexer_destroy(lexer *lex) { return; }

lexer_token_type lexer_next(lexer *lex) {

  consume_whitepspace(lex);
  while (!is_whitespace(cur_char(lex))) {
    lex->cur++;
  }
  return lex_tok_eof;
}
lexer_token_type
lexer_peek_ahead(lexer *lex, uint32_t index);
*/
