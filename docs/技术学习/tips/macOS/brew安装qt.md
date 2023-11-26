```bash
~ 6m 5s 11:27:14
 brew install qt
==> Fetching dependencies for qt: double-conversion and sqlite
==> Fetching double-conversion
==> Downloading https://ghcr.io/v2/homebrew/core/double-conversion/manifests/3.3.0
Already downloaded: /Users/hahajiukanjian/Library/Caches/Homebrew/downloads/3f6c03611d69daaddcd2d467993bfc4e75cc54a55e2900fd5f383411c445a5b4--double-conversion-3.3.0.bottle_manifest.json
==> Downloading https://ghcr.io/v2/homebrew/core/double-conversion/blobs/sha256:8945e3
Already downloaded: /Users/hahajiukanjian/Library/Caches/Homebrew/downloads/cefff1990825a82c7133225e09ed087b2066e1befb0a4cd00f1669c517aeff9a--double-conversion--3.3.0.arm64_ventura.bottle.tar.gz
==> Fetching sqlite
==> Downloading https://ghcr.io/v2/homebrew/core/sqlite/manifests/3.42.0
Already downloaded: /Users/hahajiukanjian/Library/Caches/Homebrew/downloads/9054dbd2014cfa67115dbd42da881a047783b58c96344ba1d65317539985b631--sqlite-3.42.0.bottle_manifest.json
==> Downloading https://ghcr.io/v2/homebrew/core/sqlite/blobs/sha256:c9b11a8dd4fd8996b
Already downloaded: /Users/hahajiukanjian/Library/Caches/Homebrew/downloads/5444b51621164538ed0be721bdef9c3edae6832e69069a50af092aeee1a07f0a--sqlite--3.42.0.arm64_ventura.bottle.tar.gz
==> Fetching qt
==> Downloading https://ghcr.io/v2/homebrew/core/qt/manifests/6.5.0
Already downloaded: /Users/hahajiukanjian/Library/Caches/Homebrew/downloads/e13e6b0aede5faf96865cb3b66febc4735f3860bdf2cb9047a26d54e9bc7e41f--qt-6.5.0.bottle_manifest.json
==> Downloading https://ghcr.io/v2/homebrew/core/qt/blobs/sha256:681f393770afb634173d3
==> Downloading from https://pkg-containers.githubusercontent.com/ghcr1/blobs/sha256:6
###########################################################                      75.0%############################################################################### 100.0%
==> Installing dependencies for qt: double-conversion and sqlite
==> Installing qt dependency: double-conversion
==> Pouring double-conversion--3.3.0.arm64_ventura.bottle.tar.gz
🍺  /opt/homebrew/Cellar/double-conversion/3.3.0: 26 files, 260.5KB
==> Installing qt dependency: sqlite
==> Pouring sqlite--3.42.0.arm64_ventura.bottle.tar.gz
🍺  /opt/homebrew/Cellar/sqlite/3.42.0: 11 files, 4.5MB
==> Installing qt
==> Pouring qt--6.5.0.arm64_ventura.bottle.tar.gz
==> Caveats
You can add Homebrew's Qt to QtCreator's "Qt Versions" in:
  Preferences > Qt Versions > Link with Qt...
pressing "Choose..." and selecting as the Qt installation path:
  /opt/homebrew
==> Summary
🍺  /opt/homebrew/Cellar/qt/6.5.0: 14,025 files, 601.8MB
==> Running `brew cleanup qt`...
Disable this behaviour by setting HOMEBREW_NO_INSTALL_CLEANUP.
Hide these hints with HOMEBREW_NO_ENV_HINTS (see `man brew`).
==> Upgrading 1 dependent of upgraded formulae:
Disable this behaviour by setting HOMEBREW_NO_INSTALLED_DEPENDENTS_CHECK.
Hide these hints with HOMEBREW_NO_ENV_HINTS (see `man brew`).
llvm 16.0.2 -> 16.0.4
==> Fetching dependencies for llvm: z3
==> Fetching z3
==> Downloading https://ghcr.io/v2/homebrew/core/z3/manifests/4.12.2
############################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/z3/blobs/sha256:e8006cc04b33c0d2f834c
==> Downloading from https://pkg-containers.githubusercontent.com/ghcr1/blobs/sha256:e
############################################################################### 100.0%
==> Fetching llvm
==> Downloading https://ghcr.io/v2/homebrew/core/llvm/manifests/16.0.4
############################################################################### 100.0%
==> Downloading https://ghcr.io/v2/homebrew/core/llvm/blobs/sha256:993db0d54d22dd0fd14
==> Downloading from https://pkg-containers.githubusercontent.com/ghcr1/blobs/sha256:9
############################################################################### 100.0%
==> Upgrading llvm
  16.0.2 -> 16.0.4

==> Installing dependencies for llvm: z3
==> Installing llvm dependency: z3
==> Pouring z3--4.12.2.arm64_ventura.bottle.tar.gz
🍺  /opt/homebrew/Cellar/z3/4.12.2: 118 files, 30.6MB
==> Installing llvm
==> Pouring llvm--16.0.4.arm64_ventura.bottle.tar.gz
==> Caveats
To use the bundled libc++ please add the following LDFLAGS:
  LDFLAGS="-L/opt/homebrew/opt/llvm/lib/c++ -Wl,-rpath,/opt/homebrew/opt/llvm/lib/c++"

llvm is keg-only, which means it was not symlinked into /opt/homebrew,
because macOS already provides this software and installing another version in
parallel can cause all kinds of trouble.

If you need to have llvm first in your PATH, run:
  echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc

For compilers to find llvm you may need to set:
  export LDFLAGS="-L/opt/homebrew/opt/llvm/lib"
  export CPPFLAGS="-I/opt/homebrew/opt/llvm/include"
==> Summary
🍺  /opt/homebrew/Cellar/llvm/16.0.4: 6,779 files, 1.5GB
==> Running `brew cleanup llvm`...
Removing: /opt/homebrew/Cellar/llvm/16.0.2... (6,779 files, 1.5GB)
==> Checking for dependents of upgraded formulae...
==> No broken dependents found!
==> Caveats
==> qt
You can add Homebrew's Qt to QtCreator's "Qt Versions" in:
  Preferences > Qt Versions > Link with Qt...
pressing "Choose..." and selecting as the Qt installation path:
  /opt/homebrew
==> llvm
To use the bundled libc++ please add the following LDFLAGS:
  LDFLAGS="-L/opt/homebrew/opt/llvm/lib/c++ -Wl,-rpath,/opt/homebrew/opt/llvm/lib/c++"

llvm is keg-only, which means it was not symlinked into /opt/homebrew,
because macOS already provides this software and installing another version in
parallel can cause all kinds of trouble.

If you need to have llvm first in your PATH, run:
  echo 'export PATH="/opt/homebrew/opt/llvm/bin:$PATH"' >> ~/.zshrc

For compilers to find llvm you may need to set:
  export LDFLAGS="-L/opt/homebrew/opt/llvm/lib"
  export CPPFLAGS="-I/opt/homebrew/opt/llvm/include"
```