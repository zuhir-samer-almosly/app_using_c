# app_using_c

A simple interactive text application written in C. No GUI, no background — just plain console I/O.

## Files

| File | Description |
|------|-------------|
| `main.c` | Main source file |
| `Makefile` | Build rules |

## Build

```bash
make
```

## Run

```bash
./text_app
```

## Usage

The app presents a menu with four options:

1. **Enter text** — type any text and it will be stored in memory
2. **Show text** — display the currently stored text
3. **Clear text** — erase the stored text
4. **Exit** — quit the program

## Clean

```bash
make clean
```