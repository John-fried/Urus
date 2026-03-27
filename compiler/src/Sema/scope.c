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

#include "scope.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>

SemaScope *scope_new(SemaScope *parent)
{
    SemaScope *s = calloc(1, sizeof(SemaScope));
    s->parent = parent;
    s->cap = 8;
    s->syms = xmalloc(sizeof(SemaSymbol) * (size_t)s->cap);
    return s;
}

void scope_free(SemaScope *s)
{
    xfree(s->syms);
    xfree(s);
}

SemaSymbol *scope_lookup_local(SemaScope *s, const char *name)
{
    for (int i = 0; i < s->count; i++) {
        if (strcmp(s->syms[i].name, name) == 0)
            return &s->syms[i];
    }
    return NULL;
}

SemaSymbol *scope_lookup(SemaScope *s, const char *name)
{
    for (SemaScope *cur = s; cur; cur = cur->parent) {
        SemaSymbol *sym = scope_lookup_local(cur, name);
        if (sym)
            return sym;
    }
    return NULL;
}

SemaSymbol *scope_add(SemaScope *s, const char *name, Token tok)
{
    if (s->count >= s->cap) {
        s->cap *= 2;
        s->syms = xrealloc(s->syms, sizeof(SemaSymbol) * (size_t)s->cap);
    }
    SemaSymbol *sym = &s->syms[s->count++];
    memset(sym, 0, sizeof(SemaSymbol));
    sym->name = (char *)name;
    sym->tok = tok;
    return sym;
}
