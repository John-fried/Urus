# URUS Language Support for VS Code

Full language support for the [URUS programming language](https://github.com/Urus-Foundation/Urus) — a compiled language that transpiles to C.

## Features

### Syntax Highlighting

Complete TextMate grammar covering all URUS language constructs:

- **Keywords** — `fn`, `let`, `mut`, `struct`, `enum`, `import`, `if`, `else`, `while`, `for`, `in`, `return`, `break`, `continue`, `match`
- **Types** — `int`, `float`, `bool`, `str`, `void`, `Result<T, E>`, `[T]` array types
- **Built-in functions** — all 34 built-in functions with semantic grouping:
  - I/O: `print`, `input`, `read_file`, `write_file`, `append_file`
  - Array: `len`, `push`, `pop`
  - String: `str_len`, `str_upper`, `str_lower`, `str_trim`, `str_contains`, `str_find`, `str_slice`, `str_replace`, `str_starts_with`, `str_ends_with`, `str_split`, `char_at`
  - Conversion: `to_str`, `to_int`, `to_float`
  - Math: `abs`, `fabs`, `sqrt`, `pow`, `min`, `max`, `fmin`, `fmax`
  - Result: `is_ok`, `is_err`, `unwrap`, `unwrap_err`
  - Utility: `exit`, `assert`
- **Literals** — integers, floats, strings, booleans (`true`/`false`)
- **String interpolation** — `f"Hello {name}"` with expression highlighting inside `{}`
- **Enum variants** — `EnumName.Variant` and `EnumName.Variant(args)` patterns
- **Struct constructors** — `StructName { field: value }`
- **Method calls** — `obj.method()` and field access `obj.field`
- **Operators** — arithmetic, comparison, logical, assignment, ranges (`..`, `..=`), match arrow (`=>`)
- **Result constructors** — `Ok(value)` and `Err(message)`
- **Comments** — single-line `//` and block `/* */` with nesting support
- **Type annotations** — highlighted after `:` in variable and parameter declarations

### Code Snippets

50+ snippets for all common patterns:

| Prefix | Description |
|--------|-------------|
| `main` | `fn main(): void { }` entry point |
| `fn` | Function declaration |
| `fnr` | Function with return statement |
| `let` | Immutable variable |
| `letm` | Mutable variable (`let mut`) |
| `lets` | String variable |
| `leta` | Array variable |
| `if` | If statement |
| `ife` | If-else statement |
| `while` | While loop |
| `for` | For loop with exclusive range |
| `fori` | For loop with inclusive range |
| `fore` | For-each loop over array |
| `struct` | Struct declaration |
| `structi` | Struct instance creation |
| `enum` | Enum (tagged union) declaration |
| `match` | Match expression |
| `arm` | Single match arm |
| `fnresult` | Function returning `Result<T, E>` |
| `ok` | `Ok(value)` |
| `err` | `Err(message)` |
| `isok` | Result check pattern with `is_ok`/`unwrap` |
| `import` | Import module |
| `print` | Print value |
| `printf` | Print with f-string |
| `input` | Read from stdin |
| `readf` | Read file |
| `writef` | Write file |
| `appendf` | Append to file |
| `f"` | F-string interpolation |
| `slice` | String slice |
| `split` | String split |
| `replace` | String replace |
| `push` | Array push |
| `pop` | Array pop |
| `len` | Array length |
| `sqrt` | Square root |
| `pow` | Power |
| `tostr` | Convert to string |
| `toint` | Convert to int |
| `tofloat` | Convert to float |
| `assert` | Assert with message |
| `exit` | Exit with status code |

### Editor Features

- **Bracket matching** — `{}`, `[]`, `()`, `<>` (for generics)
- **Auto-closing pairs** — brackets, parentheses, quotes, block comments
- **Colorized bracket pairs** — nested brackets use different colors
- **Smart indentation** — auto-indent after `{`, auto-outdent on `}`
- **Code folding** — fold functions, structs, enums, control flow blocks
- **Comment toggling** — `Ctrl+/` for line comments, `Ctrl+Shift+/` for block comments
- **Auto-continue comments** — pressing Enter on a `//` comment line continues the comment

## Installation

### Manual Install

1. Copy the `vscode/` folder to your VS Code extensions directory:

   **Linux / macOS:**
   ```bash
   cp -r editor-support/vscode ~/.vscode/extensions/urus-language
   ```

   **Windows (PowerShell):**
   ```powershell
   Copy-Item -Recurse editor-support\vscode "$env:USERPROFILE\.vscode\extensions\urus-language"
   ```

2. Restart VS Code (or reload: `Ctrl+Shift+P` > "Reload Window")

3. Open any `.urus` file — syntax highlighting and snippets will activate automatically.

### Install from VSIX

If you have the `.vsix` package:

```bash
code --install-extension urus-language-0.2.0.vsix
```

Or in VS Code: `Ctrl+Shift+P` > "Extensions: Install from VSIX..."

### Build VSIX Package

To create a distributable `.vsix` file:

```bash
cd editor-support/vscode
npm install -g @vscode/vsce
vsce package
```

This creates `urus-language-0.2.0.vsix`.

## File Structure

```
vscode/
├── icon.png                           # Extension icon
├── language-configuration.json        # Brackets, comments, indentation, folding
├── package.json                       # Extension manifest
├── README.md                          # This file
├── snippets/
│   └── urus.code-snippets            # 50+ code snippets
└── syntaxes/
    └── urus.tmLanguage.json          # TextMate grammar (syntax highlighting)
```

## Example

```urus
import "math.urus";

struct Point {
    x: float;
    y: float;
}

enum Shape {
    Circle(radius: float);
    Rectangle(w: float, h: float);
    Point;
}

fn area(s: Shape): Result<float, str> {
    match s {
        Shape.Circle(r) => {
            return Ok(3.14159 * r * r);
        }
        Shape.Rectangle(w, h) => {
            return Ok(w * h);
        }
        Shape.Point => {
            return Err("Point has no area");
        }
    }
}

fn main(): void {
    let shapes: [Shape] = [
        Shape.Circle(5.0),
        Shape.Rectangle(3.0, 4.0),
        Shape.Point
    ];

    for shape in shapes {
        let result: Result<float, str> = area(shape);
        if is_ok(result) {
            print(f"Area: {unwrap(result)}");
        } else {
            print(f"Error: {unwrap_err(result)}");
        }
    }
}
```

## Contributing

Contributions are welcome! If you find a syntax highlighting issue or want to add features:

1. Fork the [URUS repository](https://github.com/Urus-Foundation/Urus)
2. Edit files in `editor-support/vscode/`
3. Test by copying to your extensions directory
4. Submit a PR targeting the `dev` branch

## Links

- [URUS Repository](https://github.com/Urus-Foundation/Urus)
- [Language Specification](https://github.com/Urus-Foundation/Urus/blob/main/SPEC.md)
- [Report Issues](https://github.com/Urus-Foundation/Urus/issues)

## License

Apache 2.0 — same as the URUS project.
