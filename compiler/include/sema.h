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

#ifndef URUS_SEMA_H
#define URUS_SEMA_H

#include "ast.h"
#include <stdbool.h>
#include <stdint.h>

enum {
    FN_SYM_TAG = 1,
    STRUCT_SYM_TAG,
    ENUM_SYM_TAG,
    TYPE_SYM_TAG
};

typedef struct {
    char *name;
    AstType *type;
    Token tok; // For error tracking
    uint8_t tag;
    bool is_mut;
    bool is_referenced;
    bool is_imported; // prevent unused warning on imported decl
    bool is_builtin; // prevent unused warning on builtin function/variable

    // function
    Param *params;
    int param_count;
    AstType *return_type;

    // struct
    Param *fields;
    int field_count;

    // enum
    EnumVariant *variants;
    int variant_count;

    // alias (type ID = int;);
    AstType *alias_type;
} SemaSymbol;

typedef struct Scope {
    SemaSymbol *syms;
    int count, cap;
    struct Scope *parent;
} SemaScope;

typedef struct {
    SemaScope *current;
    AstType *current_fn_return;
    const char *current_fn_name; // in function '...' tracking
    const char *filename;
    int errors;
    int loop_depth;
} SemaCtx;

// Returns true if analysis succeeded (no errors)
bool sema_analyze(AstNode *program, const char *filename);

// Builtin registration (sema_builtins.c)
void sema_register_builtins(SemaScope *global);

#endif
