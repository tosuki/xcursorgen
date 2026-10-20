# cursorgen

A lightweight command-line tool written in C to generate X11 cursor files (`Xcur`) directly from standard image formats.

## Features

- **Format Support**: Loads input images (PNG, JPEG, BMP, etc.) using `stb_image`.
- **Xcursor Compliant**: Packages images according to the X11 Xcursor binary specification (magic signature, TOC, and image chunks).
- **Pixel Conversion**: Automatically handles premultiplied ARGB pixel conversion required by X11.
- **Hotspot & Delay Control**: Allows configuring custom hotspot coordinates (`xhot`, `yhot`) and frame delay for cursors.
- **Zero Heavy Dependencies**: Built in pure C11 using only standard libraries and single-header dependencies.

## Project Structure

```text
.
├── Makefile
├── README.md
├── include/
│   └── stb_image.h       # Single-header image loader
└── src/
    ├── cursorgen.h       # Xcursor binary structures and function prototypes
    ├── cursorgen.c       # Xcursor generator and pixel packing implementation
    └── main.c            # CLI entrypoint and argument parser
```

## Prerequisites

- C compiler (`clang` or `gcc`) supporting C11
- `make`

## Building

Compile the binary:

```bash
make
```

The compiled binary will be placed at `bin/main`.

To clean build artifacts:

```bash
make clean
```

## Usage

```bash
./bin/main <img_path> <xhot> <yhot> <delay> <out_path>
```

Alternatively, you can run via `make`:

```bash
make run ARGS="<img_path> <xhot> <yhot> <delay> <out_path>"
```

### Arguments

| Parameter | Type | Description |
| :--- | :--- | :--- |
| `img_path` | String | Path to the input image file (e.g. `assets/pointer.png`). |
| `xhot` | Integer | X coordinate of the cursor hotspot (the active click point). |
| `yhot` | Integer | Y coordinate of the cursor hotspot. |
| `delay` | Integer | Frame duration in milliseconds (set to `0` for static cursors). |
| `out_path` | String | Output path for the generated Xcursor file. |

### Example

Generate a standard static cursor with the hotspot at `(0, 0)`:

```bash
./bin/main pointer.png 0 0 0 pointer
```

## File Format Overview

`cursorgen` outputs binary files matching the X11 cursor structure:

1. **File Header**: Magic signature `0x72756358` (`Xcur`), header size, version, and TOC entry count.
2. **Table of Contents (TOC)**: Type identifier (`0xfffd0002`), subtype (image dimension), and byte offset to the image chunk.
3. **Image Header**: Chunk dimensions (width, height), hotspots, and delay.
4. **Pixel Data**: Packed 32-bit premultiplied ARGB values (`[A][R][G][B]`).
