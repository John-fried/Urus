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

#ifndef URUS_UTIL_H
#define URUS_UTIL_H

#include <stddef.h>

char *read_file(const char *path, size_t *out_len);

// --  Memory Management  --
#define xfree(ptr) __xfree((void **)&(ptr))
#define xrealloc(ptr, size) __xrealloc((void **)&(ptr), size)
void *xmalloc(size_t size);
void *__xrealloc(void **ptr, size_t size);
void __xfree(void **ptr);

#endif
