# base.c

Base number conversion utility.

Convert numbers from one base to another (ex: from base64 to base10) and get results on standard output.

## Usage

Usage: `base [OPTIONS] NUMBER...`

## Install

### System dependencies
- git
- gnu make
- C compiler (gcc, clang, zig... )

### Install

Paste this commands on the terminal. It will clone, build and create a binary on `$HOME/.local/bin` directory by default.

```bash
git clone https://github.com/4ngelf/base.c.git base \
  && cd base \
  && make install
```

You can verify the installation using

```bash
base --version
```

### Makefile targets

```bash
# Build project
make

# Test project
make test

# Install on system
make install

# Uninstall from system
make uninstall
```

## License

[MIT License](./LICENSE)
