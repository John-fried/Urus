# URUS Language Support for VS Code

Provides syntax highlighting for the [URUS programming language](https://github.com/Urus-Foundation/Urus).

## Features

- Syntax highlighting for `.urus` files
- Keyword, type, and built-in function highlighting
- String and f-string interpolation highlighting
- Comment highlighting (single-line and block)
- Bracket matching and auto-closing pairs
- Auto-indentation

## Installation

### Manual

1. Copy the `vscode/` folder to your VS Code extensions directory:
   - **Linux/macOS:** `~/.vscode/extensions/urus-language`
   - **Windows:** `%USERPROFILE%\.vscode\extensions\urus-language`
2. Restart VS Code.
3. Open any `.urus` file — highlighting will apply automatically.

### From VSIX (coming soon)

Once published to the marketplace, install via:
```
ext install urus-foundation.urus-language
```

## Usage

Open any `.urus` file and syntax highlighting will be applied automatically.
