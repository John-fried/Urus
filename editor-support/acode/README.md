# URUS Language Plugin for Acode

Adds syntax highlighting for `.urus` files in the [Acode editor](https://acode.app).

## Features

- Syntax highlighting for `.urus` files
- Keywords, types, and built-in function highlighting
- String and f-string interpolation highlighting
- Comment highlighting (single-line `//` and block `/* */`)

## Installation

1. Download or build the plugin (`main.js` + `plugin.json`)
2. Open Acode → Settings → Plugins → Install from file
3. Select the plugin folder
4. Open any `.urus` file — highlighting applies automatically

## Building

```bash
cd editor-support/acode
# No build step required — main.js is ready to use
```

For production, you can minify `main.js` with any JS minifier.
