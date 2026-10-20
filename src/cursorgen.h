#ifndef CURSORGEN_H
#define CURSORGEN_H

#define XCURSOR_SIGNATURE 0x72756358 // Xcur in hexadecimal
#define XCURSOR_IMAGE_TYPE 0xfffd0002

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


// ┌───────────────────────────────┐
// │ Cabeçalho do Arquivo (Header) │
// ├───────────────────────────────┤
// │ Índice de Blocos (TOC)        │ 
// ├───────────────────────────────┤
// │ Bloco de Imagem 1             │ 
// ├───────────────────────────────┤
// │ Bloco de Imagem 2 (outro DPI) │ 
// ├───────────────────────────────┤
// │ Bloco de Imagem 3 (próx. frame│
// └───────────────────────────────┘
int create_xcursor_file(const char *img_path, uint32_t xhot, uint32_t yhot,
                         uint32_t delay, const char *out_path);

#endif
