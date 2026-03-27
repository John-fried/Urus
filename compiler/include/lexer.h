/*
 * Copyright 2026 Urus Foundation (https://github.com/Urus-Foundation)
 *
 * This file is part of the Urus Programming Language.
 * For more about this language check at
 *
 *    https://github.com/Urus-Foundatation/Urus
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef URUS_LEXER_H
#define URUS_LEXER_H

#include "token.h"

typedef struct {
    const char *source;
    size_t length;
    size_t pos;
    int line;
    int line_start;
} Lexer;

void lexer_init(Lexer *l, const char *source, size_t length);
Token lexer_next(Lexer *l);

// Tokenize entire source, returns malloc'd array, sets *count
Token *lexer_tokenize(Lexer *l, int *count);

#endif
