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

#ifndef URUS_SEMA_SCOPE_H
#define URUS_SEMA_SCOPE_H

#include "sema.h"

// TODO: Add simple documentation about function here

SemaScope *scope_new(SemaScope *parent);
void scope_free(SemaScope *s);
SemaSymbol *scope_lookup_local(SemaScope *s, const char *name);
SemaSymbol *scope_lookup(SemaScope *s, const char *name);
SemaSymbol *scope_add(SemaScope *s, const char *name, Token tok);

#endif
