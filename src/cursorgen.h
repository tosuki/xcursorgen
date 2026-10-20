#ifndef CURSORGEN_H
#define CURSORGEN_H

#define XCURSOR_SIGNATURE 0x72756358 // Xcur in hexadecimal

#include <stdint.h>

// 16 bytes header, uint32_t -> 32 bits, 4 bytes
typedef struct {
  uint32_t magic_signature;
  uint32_t header;
  uint32_t version;
  uint32_t ntoc; // number of images inside the file
} t_xcursor_h;

typedef struct {
  uint32_t type;
  uint32_t subtype;
  uint32_t position; // offset
} t_xcursor_toc;

typedef struct {
  uint32_t header;
  uint32_t type;
  uint32_t subtype;
  uint32_t version;
  uint32_t width;
  uint32_t height;
  uint32_t x_hot;
  uint32_t y_hot;
  uint32_t delay; // 0 for static
} t_xcursor_image_h;

#endif
