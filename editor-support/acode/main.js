// URUS Language Plugin for Acode Editor
// Adds syntax highlighting for .urus files using Ace editor mode

const acequire = window.acequire || require;

function defineUrusMode() {
  ace.define(
    "ace/mode/urus_highlight_rules",
    ["require", "exports", "module", "ace/lib/oop", "ace/mode/text_highlight_rules"],
    function (require, exports, module) {
      const oop = require("ace/lib/oop");
      const TextHighlightRules = require("ace/mode/text_highlight_rules").TextHighlightRules;

      const UrusHighlightRules = function () {
        const keywords =
          "if|else|while|for|in|return|break|continue|match|fn|let|mut|struct|enum|import";
        const resultKeywords = "Ok|Err";
        const types = "int|float|bool|str|void|Result";
        const constants = "true|false";
        const builtins =
          "print|input|read_file|write_file|append_file|" +
          "len|push|pop|" +
          "str_len|str_upper|str_lower|str_trim|str_contains|str_find|" +
          "str_slice|str_replace|str_starts_with|str_ends_with|str_split|char_at|" +
          "to_str|to_int|to_float|" +
          "abs|fabs|sqrt|pow|min|max|fmin|fmax|" +
          "is_ok|is_err|unwrap|unwrap_err|" +
          "exit|assert";

        this.$rules = {
          start: [
            { token: "comment.block", regex: /\/\*/, next: "block_comment" },
            { token: "comment.line", regex: /\/\/.*$/ },
            { token: "string.fstring.start", regex: /f"/, next: "fstring" },
            { token: "string.start", regex: /"/, next: "string" },
            { token: "constant.numeric.float", regex: /\b\d+\.\d+\b/ },
            { token: "constant.numeric.integer", regex: /\b\d+\b/ },
            { token: "keyword.control", regex: new RegExp(`\\b(${keywords})\\b`) },
            { token: "keyword.other", regex: new RegExp(`\\b(${resultKeywords})\\b`) },
            { token: "storage.type", regex: new RegExp(`\\b(${types})\\b`) },
            { token: "constant.language", regex: new RegExp(`\\b(${constants})\\b`) },
            { token: "support.function.builtin", regex: new RegExp(`\\b(${builtins})(?=\\s*\\()`) },
            { token: "entity.name.function", regex: /\b([a-zA-Z_][a-zA-Z0-9_]*)(?=\s*\()/ },
            { token: "keyword.operator.range", regex: /\.\.=?/ },
            { token: "keyword.operator.arrow", regex: /=>/ },
            { token: "keyword.operator.comparison", regex: /==|!=|<=|>=|<|>/ },
            { token: "keyword.operator.logical", regex: /&&|\|\||!/ },
            { token: "keyword.operator.assignment", regex: /\+=|-=|\*=|\/=|=/ },
            { token: "keyword.operator.arithmetic", regex: /\+|-|\*|\/|%/ },
          ],
          block_comment: [
            { token: "comment.block.end", regex: /\*\//, next: "start" },
            { defaultToken: "comment.block" },
          ],
          string: [
            { token: "constant.character.escape", regex: /\\./ },
            { token: "string.end", regex: /"/, next: "start" },
            { defaultToken: "string" },
          ],
          fstring: [
            { token: "meta.interpolation.start", regex: /\{/, next: "fstring_interp" },
            { token: "constant.character.escape", regex: /\\./ },
            { token: "string.fstring.end", regex: /"/, next: "start" },
            { defaultToken: "string.fstring" },
          ],
          fstring_interp: [
            { token: "meta.interpolation.end", regex: /\}/, next: "fstring" },
            { token: "constant.numeric", regex: /\b\d+(\.\d+)?\b/ },
            { token: "support.function.builtin", regex: new RegExp(`\\b(${builtins})(?=\\s*\\()`) },
            { token: "entity.name.function", regex: /\b([a-zA-Z_][a-zA-Z0-9_]*)(?=\s*\()/ },
            { token: "variable", regex: /\b[a-zA-Z_][a-zA-Z0-9_]*\b/ },
          ],
        };

        this.normalizeRules();
      };

      oop.inherits(UrusHighlightRules, TextHighlightRules);
      exports.UrusHighlightRules = UrusHighlightRules;
    }
  );

  ace.define(
    "ace/mode/urus",
    ["require", "exports", "module", "ace/lib/oop", "ace/mode/text", "ace/mode/urus_highlight_rules"],
    function (require, exports, module) {
      const oop = require("ace/lib/oop");
      const TextMode = require("ace/mode/text").Mode;
      const UrusHighlightRules = require("ace/mode/urus_highlight_rules").UrusHighlightRules;

      const Mode = function () {
        this.HighlightRules = UrusHighlightRules;
        this.lineCommentStart = "//";
        this.blockComment = { start: "/*", end: "*/" };
      };

      oop.inherits(Mode, TextMode);
      exports.Mode = Mode;
    }
  );
}

// Acode Plugin Entry Point
if (typeof acode !== "undefined") {
  const plugin = {
    async init(baseUrl) {
      defineUrusMode();

      // Register ace mode
      const aceModes = acode.require("aceModes");
      if (aceModes && aceModes.addMode) {
        aceModes.addMode("urus", ["urus"], "URUS");
      }

      const iconUrl = baseUrl + "icon.png";

      // Register icon
      if (acode.addIcon) {
        acode.addIcon("urus", iconUrl);
      }

      // Inject CSS untuk file icon di file explorer
      const style = document.createElement("style");
      style.id = "urus-file-icon-style";
      style.textContent = `
        [data-ext="urus"] .file-icon,
        .file-icon.urus,
        span.icon.urus {
          background-image: url('${iconUrl}') !important;
          background-size: contain !important;
          background-repeat: no-repeat !important;
          background-position: center !important;
        }
      `;
      document.head.appendChild(style);
    },

    async destroy() {
      try {
        const aceModes = acode.require("aceModes");
        if (aceModes && aceModes.removeMode) {
          aceModes.removeMode("urus");
        }
      } catch(e) {}
      document.getElementById("urus-file-icon-style")?.remove();
    },
  };

  acode.setPluginInit(
    "acode.plugin.urus",
    async (baseUrl, $page, { cacheFileUrl }) => {
      await plugin.init(baseUrl);
    }
  );

  acode.setPluginUnmount("acode.plugin.urus", () => {
    plugin.destroy();
  });
}
