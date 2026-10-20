#include "cursorgen.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  if (argc < 6) {
    fprintf(stderr, "Usage: %s <img_path> <xhot> <yhot> <delay> <out_path>\n", argv[0]);
    return 1;
  }

  const char *out_path = argv[5];

  int result = create_xcursor_file(
    argv[1],
    (uint32_t)atoi(argv[2]),
    (uint32_t)atoi(argv[3]),
    (uint32_t)atoi(argv[4]),
    out_path
  );

  if (result != 0) {
    fprintf(stderr, "Error: Failed to create xcursor file '%s': %s\n", out_path,
            strerror(errno));
    return 1;
  }

  return 0;
}
