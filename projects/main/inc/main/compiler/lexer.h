#ifndef LEXER_H
#define LEXER_H

#include "main/collections/str_ascii.h"

#include <stdint.h>

typedef struct lexer lexer;

typedef enum {
  lex_tok_eof,
  lex_tok_ident_type,
  lex_tok_ident_func,
  lex_tok_ident_var,
  lex_tok_if,
  lex_tok_while,
} lexer_token_type;

lexer lexer_make(str_ascii source);
void lexer_destroy(lexer *lex);

lexer_token_type lexer_next(lexer *lex);
lexer_token_type
lexer_peek_ahead(lexer *lex, uint32_t index);

#endif

// let a = 10;
// let a: mut = 10;
// let a: mut int = 10;
// let a: ref mut int = 10; //ref to mut int
// let a: mut ref mut int = 10; // mut ref to
// mut int
