# Security

## Overview

URUS is a compiled language that produces native binaries. Since there is no server, API, or network component, the main attack surface is:

1. **Compiler** — can crash or be exploited if given malicious input
2. **Generated code** — can contain vulnerabilities if codegen is incorrect
3. **Runtime** — memory safety depends on ref-counting and bounds checking

## Memory Safety

### Reference Counting

All heap-allocated values (str, array, struct) use ref-counting:

```c
typedef struct {
    char *data;
    int64_t len;
    int32_t refcount;  // tracked automatically
} urus_str;
```

| Operation | Effect |
|-----------|--------|
| Assignment `let b = a;` | `refcount++` |
| Scope exit | `refcount--`, free if 0 |
| Reassignment `a = new_val;` | release old, retain new |

**Limitation:** No cycle detection. Circular references cause memory leaks.

### Bounds Checking

Array access is checked at runtime:

```c
void *urus_array_get_ptr(urus_array *a, int64_t index) {
    if (index < 0 || index >= a->len) {
        fprintf(stderr, "Array index out of bounds: %lld (len=%lld)\n", index, a->len);
        exit(1);
    }
    return a->data + index * a->elem_size;
}
```

Buffer overflow via array index is **not possible** in URUS code — the compiler always uses checked access.

### Type Safety

- All variables have types verified at compile time
- No implicit type coercion (except explicit `to_str`/`to_int`/`to_float`)
- No pointer arithmetic or unsafe operations
- Immutable by default — must use explicit `mut` for mutation
- No null pointers — uninitialized variables are a compile error

## Compiler Security

### Input Validation

- Lexer rejects invalid UTF-8 bytes
- Parser rejects malformed syntax
- Sema rejects type errors, undefined variables, unused symbols
- Error reporting shows exact location without exposing internal state

### Potential Risks

| Risk | Severity | Status | Mitigation |
|------|----------|--------|------------|
| Buffer overflow in compiler | Low | Mitigated | Static buffers with size limit, round-robin |
| Stack overflow (deep recursion) | Low | Known | Usually only with very deeply nested code |
| Arbitrary code execution via import | Medium | Mitigated | Import only reads files, does not execute |
| Path traversal via import | Medium | Mitigated | Import is relative to the current file |
| CRLF injection in generated code | Low | Fixed | Binary mode write (`"wb"`) since V0.2/2(F) |

### Import Security

Imports are resolved relative to the importing file:

```urus
import "../../etc/passwd";  // Only read as URUS source, not executed
```

- Imported files must be valid URUS source (parsed and type-checked)
- No network imports
- No dynamic imports (all imports resolved at compile time)
- Circular imports are detected (max 64 files)

## Environment & Secrets

URUS does not use:
- Environment variables for configuration
- Config files with secrets
- Network connections
- Database connections
- Package registries or remote downloads

### File I/O Security

URUS programs can read/write files via built-in functions:

```urus
write_file("path", "content");
let data: str = read_file("path");
```

**Note:** There is no sandboxing — URUS programs have the same filesystem access as the user running them. This is the same as regular C programs.

## Best Practices

### For URUS Users

1. **Do not run URUS programs from untrusted sources** — same as any C binary
2. **Review generated C** with `--emit-c` before compiling third-party programs
3. **Avoid circular references** — they cause memory leaks
4. **Validate input** — URUS has no built-in input sanitization

### For Compiler Developers

1. **Always bounds-check** array and string access in the runtime
2. **Use `snprintf`** instead of `sprintf` for buffer writes
3. **Use `fopen("wb")`** for generated files on Windows
4. **Free all AST nodes** to avoid memory leaks in the compiler
5. **Test with malformed input** — fuzzing is recommended
6. **Never embed user input directly** in generated C code without escaping

## Reporting Vulnerabilities

If you find a security vulnerability, please report it via:
- GitHub Security Advisories: https://github.com/Urus-Foundation/Urus/security/advisories
- Or email: rasyaandrean@outlook.co.id

Please do **not** open a public issue for security vulnerabilities.

## Known Limitations

| Item | Description |
|------|-------------|
| No cycle detection | Circular ref-counted references = memory leak |
| No sandboxing | File I/O without restrictions |
| No input sanitization | Strings from `read_file` are not escaped |
| Single-threaded | No thread safety concerns, but also no concurrency |
| No ASLR/DEP control | Depends on the OS and GCC flags |
| No code signing | Compiled binaries are not signed |
