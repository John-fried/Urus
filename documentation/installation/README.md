# Installation

## Requirements

| Tool | Minimum Version | Purpose |
|------|----------------|---------|
| GCC | 8.0+ | C compiler backend |
| CMake | 3.10+ | Build system |
| Git | any | Cloning the repository |

## Quick Install

```bash
git clone https://github.com/Urus-Foundation/Urus.git
cd Urus/compiler
cmake -S . -B build
cmake --build build --config Release
```

The compiled binary will be at:
- **Windows:** `compiler/build/Release/urusc.exe`
- **Linux/macOS:** `compiler/build/urusc`

## Platform-Specific Setup

### Windows

#### Option A: MSYS2 (Recommended)

1. Download MSYS2 from https://www.msys2.org/
2. Open MSYS2 terminal and install:
   ```bash
   pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake
   ```
3. Add `C:\msys64\mingw64\bin` to your system PATH

#### Option B: WinLibs

1. Download from https://winlibs.com/
2. Extract and add the `bin/` folder to PATH

#### Option C: Chocolatey

```powershell
choco install mingw cmake
```

#### Option D: Visual Studio (MSVC)

1. Install Visual Studio with "Desktop development with C++" workload
2. Open "Developer Command Prompt for VS"
3. CMake will use MSVC automatically
4. You still need GCC/MinGW for the generated code compilation step

### Linux

#### Ubuntu / Debian
```bash
sudo apt update
sudo apt install gcc cmake git
```

#### Fedora / RHEL
```bash
sudo dnf install gcc cmake git
```

#### Arch Linux
```bash
sudo pacman -S gcc cmake git
```

### macOS

```bash
# Install Xcode Command Line Tools (includes GCC-compatible clang)
xcode-select --install

# Or install GCC via Homebrew
brew install gcc cmake
```

## Build Steps

### CMake Build (Recommended)

```bash
cd compiler

# Configure
cmake -S . -B build

# Build (Release)
cmake --build build --config Release

# Verify
./build/Release/urusc --version   # Windows
./build/urusc --version           # Linux/macOS
```

### CMake Build Types

| Type | Command | Notes |
|------|---------|-------|
| Release | `cmake --build build --config Release` | Optimized, recommended |
| Debug | `cmake --build build --config Debug` | With debug symbols |

## Environment Setup

### Add to PATH

To use `urusc` from anywhere:

**Linux/macOS:**
```bash
export PATH="$PATH:/path/to/Urus/compiler/build"
```

**Windows (PowerShell):**
```powershell
$env:PATH += ";C:\path\to\Urus\compiler\build\Release"
```

Or add permanently via System Settings > Environment Variables.

## Verification

```bash
# Check version
urusc --version

# Compile a test program
echo 'fn main(): void { print("Hello URUS!"); }' > test.urus
urusc test.urus -o test
./test
```

Expected output:
```
Hello URUS!
```

## Docker

```bash
docker build -t urus .
docker run --rm urus urusc --version
```

## Troubleshooting

### Common Errors

| Error | Cause | Solution |
|-------|-------|----------|
| `gcc: command not found` | GCC not installed or not in PATH | Install GCC and add to PATH |
| `cmake: command not found` | CMake not installed | Install CMake 3.10+ |
| `fatal error: cannot execute 'cc1'` | GCC internal tools not in PATH | The compiler auto-fixes this since V0.2/2(F). Ensure GCC bin dir is in PATH |
| `unresolved external symbol getline` | Using old compiler version | Update to V0.2/2(F) which uses portable `fgets()` |
| `LINK : fatal error LNK...` | MSVC linking issue | Use MinGW/GCC instead of MSVC for generated code |
| Double line breaks in output | CRLF issue on Windows | Fixed in V0.2/2(F) with binary mode file writing |

### Still Having Issues?

1. Check the [GitHub Issues](https://github.com/Urus-Foundation/Urus/issues)
2. Open a new issue using the Bug Report template
3. Or write in [Diary/COMPLAINTS.md](../../Diary/COMPLAINTS.md)
