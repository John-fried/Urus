# Architecture

## Architecture Diagram

```
+--------------------------------------------------------------+
|                       URUS Compiler                          |
|                                                              |
|  .urus file                                                  |
|      |                                                       |
|      v                                                       |
|  +--------+   tokens   +--------+   AST   +------+          |
|  | Lexer  |----------->| Parser |-------->| Sema |          |
|  |        |            |        |         |      |          |
|  +--------+            +--------+         +--+---+          |
|   lexer.c               parser.c             |               |
|   token.h                ast.h/c             |               |
|                                              v               |
|                                         +---------+         |
|                                         | Codegen |         |
|                                         |         |         |
|                                         +----+----+         |
|                                              |               |
|                                         .c output            |
|                                              |               |
+----------------------------------------------+--------------+
                                               |
                                               v
                                          +---------+
                                          |   GCC   |
                                          +----+----+
                                               |
                                          native binary
```

## System Flow

### 1. Lexing (Tokenization)
- **Input:** source code string
- **Output:** array of tokens
- **Files:** `lexer.c`, `token.h`
- **Recognizes:** keywords, identifiers, literals, operators, f-strings
- **Special:** f-string tokenization creates sub-lexer for embedded expressions

### 2. Parsing
- **Input:** token stream
- **Output:** Abstract Syntax Tree (AST)
- **Files:** `parser.c`, `ast.h`, `ast.c`
- **Method:** Recursive descent parser with Pratt parsing for operator precedence
- **Desugaring:** f-strings converted to `to_str()` + concat operations

### 3. Semantic Analysis (Sema)
- **Input:** AST
- **Output:** AST with resolved types
- **File:** `sema.c`
- **Two-pass approach:**
  1. Register all top-level declarations (functions, structs, enums)
  2. Type-check all function bodies
- **Validates:** types, scopes, mutability, break/continue placement, unused symbols

### 4. Code Generation
- **Input:** type-checked AST
- **Output:** C source code string
- **File:** `codegen.c`
- **Generates:** standard C11 (no GCC extensions)
- **Runtime:** `urus_runtime.h` embedded as C array in compiler binary

### 5. Compilation
- **Input:** generated C file (`_urus_tmp.c`)
- **Output:** native binary
- **File:** `main.c` (orchestrator)
- **Invokes:** GCC with `-std=c11 -O2 -lm`
- **Cleanup:** temp file deleted after successful compilation

## Folder Structure

```
Urus/
+-- compiler/
|   +-- src/                    # Source files (.c)
|   |   +-- main.c             # CLI entry point, import resolution, GCC invocation
|   |   +-- lexer.c            # Tokenizer
|   |   +-- parser.c           # Recursive descent parser
|   |   +-- ast.c              # AST utilities (print, clone, free)
|   |   +-- sema.c             # Semantic analysis & type checking
|   |   +-- codegen.c          # C code generation
|   |   +-- error.c            # Error reporting with source context
|   |   +-- util.c             # String/memory helpers
|   |
|   +-- include/               # Header files (.h)
|   |   +-- token.h            # Token types enum
|   |   +-- lexer.h            # Lexer API
|   |   +-- parser.h           # Parser API
|   |   +-- ast.h              # AST node types, AstType definitions
|   |   +-- sema.h             # Sema API
|   |   +-- codegen.h          # Codegen API, CodeBuf struct
|   |   +-- error.h            # Error reporting API
|   |   +-- util.h             # Utility API
|   |   +-- urus_runtime.h     # Header-only runtime library
|   |
|   +-- cmake/
|   |   +-- embed-string.cmake # Embeds runtime header into binary as C array
|   |
|   +-- CMakeLists.txt         # Build configuration
|   +-- config.h.in            # Version string template
|
+-- examples/                  # Example URUS programs
+-- tests/                     # Test suite (valid, invalid, run)
+-- documentation/             # Project documentation
+-- Diary/                     # Development notes & complaints
+-- assets/                    # Images and media
+-- .github/                   # Issue templates, CI, funding
+-- SPEC.md                    # Language specification
+-- README.md                  # Project README
+-- CHANGELOG.md               # Version history
+-- CONTRIBUTING.md            # Contribution guide
+-- SECURITY.md                # Security policy
+-- CODE_OF_CONDUCT.md         # Community guidelines
+-- Dockerfile                 # Container build
+-- LICENSE                    # Apache 2.0
```

## Inter-Module Dependencies

```
main.c
  +-- lexer.h    (tokenize source)
  +-- parser.h   (parse tokens -> AST)
  +-- sema.h     (type-check AST)
  +-- codegen.h  (generate C from AST)
  +-- error.h    (error reporting)
  +-- ast.h      (AST data structures)
  +-- util.h     (string helpers)

lexer.c
  +-- lexer.h
  +-- token.h    (token type enum)

parser.c
  +-- parser.h
  +-- lexer.h    (sub-lexer for f-strings)
  +-- ast.h      (create AST nodes)
  +-- token.h

sema.c
  +-- sema.h
  +-- ast.h      (traverse/modify AST)

codegen.c
  +-- codegen.h
  +-- ast.h      (traverse AST)

error.c
  +-- error.h
  +-- token.h    (token position info)
```

## Data Flow

```
Source (.urus) -> Token[] -> AstNode* (tree) -> AstNode* (typed) -> char* (C code) -> binary
                  Lexer      Parser              Sema               Codegen          GCC
```

## Runtime Embedding

Since V0.2/2(F), the runtime (`urus_runtime.h`) is embedded directly into the compiler binary:

```
cmake/embed-string.cmake
  |
  v
urus_runtime.h --> C array (urus_runtime_data[]) --> compiled into urusc binary
  |
  v
At compile time: compiler writes runtime + generated code to _urus_tmp.c
```

This makes the compiler fully standalone — no external files needed.
