# c-stripper : A Self-Cleaning C Preprocessor

**c-stripper** is a minimalist comment-stripping preprocessor for C source files.  
It removes both `//` and `/* ... */` comments safely including multi-line block comments that span across buffer boundaries and preserves the structure of the original file where appropriate.

This tool is robust enough to process and clean its own source code, making it a self-stripping program.

---

## Features
- Strips `//` single-line comments
- Handles `/* ... */` multi-line comments, including those spanning multiple buffer reads
- Preserves valid code and original structure where applicable
- Ignores comment-like sequences inside string literals or unrelated syntax
- Filters out empty or whitespace-only lines to maintain clean output
- Self-hosted: capable of running on and cleaning its own source

---

## Usage

To compile the program, just run:

```bash
make
```

By default, this uses Clang (recommended for macOS).  
To use GCC instead, run:

```bash
make CC=gcc
```

You can also compile and immediately run it in one step:

```bash
make run
```

To remove the compiled binary:

```bash
make clean
```

---

Once compiled, run the program:

```bash
./c-stripper
```

You will be prompted to enter:
1. The name of the input C file
2. A name for the output file (or press enter to automatically use `[original_name]_stripped.c`)

---

## Example

**Input:**

```c
int main() {
	// this is a comment
	printf("hello world"); /* this gets removed */
	return 0;
}
```

**Output:**

```c
int main() {
	printf("hello world");
	return 0;
}
```

---

## Why This Exists

This project began as an exercise in building a compiler pipeline from scratch.  
Rather than relying on regular expressions or fragile heuristics, it tracks syntax deliberately much like an actual compiler would — while aiming to preserve programmer intent and logical structure.

It serves as a lightweight preprocessing pass and a stepping stone toward a full lexer/tokenizer.

---

## License & Usage

This project is free to use and open source.  
You may copy, modify, and extend it as needed.  
All I ask is that you credit the original author (`Armand Bouillet`) in your work or documentation if you use or build upon this code.

---

## Planned Improvements

- Tokenization and basic lexical analysis
- Tab-aware structure inference (e.g. scope mismatch detection)
- Line number tracking for error reporting
- Integration into a complete compiler toolchain

---

## Author

Created by [@the-armand](https://github.com/the-armand)  
Written in C and tested by running on itself.
