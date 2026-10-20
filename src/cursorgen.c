#include "cursorgen.h"
#include "stb_image.h"

#include <stdint.h>
#include <errno.h>

// Problem 1 -> xcursor uses ARGB instead of RGB.
uint32_t pack_argb_premultiplied(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
  uint32_t pr = (r * a) / 255;
  uint32_t pg = (g * a) / 255;
  uint32_t pb = (b * a) / 255;

  return (a << 24) | (pr << 16) | (pg << 8) | pb; // 4 bytes -> [A][R][G][B]
}

int create_xcursor_file(const char *img_path, uint32_t xhot, uint32_t yhot,
                        uint32_t delay, const char *out_path)
{
  int img_w, img_h, img_channels;

  uint8_t *raw_pixels = stbi_load(img_path, &img_w, &img_h, &img_channels, 4);

  if (!raw_pixels)
  {
    errno = ENOENT;
    return EXIT_FAILURE;
  }

  FILE *out_file = fopen(out_path, "wb");

  if (!out_file)
  {
    errno = ENOENT;
    stbi_image_free(raw_pixels);

    return EXIT_FAILURE;
  }

  t_xcursor_h xcursor_header = {
      XCURSOR_SIGNATURE,
      sizeof(t_xcursor_h),
      1,
      1};

  fwrite(&xcursor_header, sizeof(xcursor_header), 1, out_file);
  uint32_t img_offset = sizeof(xcursor_header) + sizeof(t_xcursor_toc);

  t_xcursor_toc xcursor_toc = {
      XCURSOR_IMAGE_TYPE,
      (uint32_t)img_w,
      img_offset};

  fwrite(&xcursor_toc, sizeof(xcursor_toc), 1, out_file);

  t_xcursor_image_h xcursor_image_header = {
      sizeof(t_xcursor_image_h),
      XCURSOR_IMAGE_TYPE,
      (uint32_t)img_w,
      1,
      (uint32_t)img_w,
      (uint32_t)img_h,
      xhot,
      yhot,
      delay};

  fwrite(&xcursor_image_header, sizeof(xcursor_image_header), 1, out_file);

  for (int i = 0; i < (img_w * img_h); i++) {
    uint8_t r = raw_pixels[i + 4 + 0];
    uint8_t g = raw_pixels[i + 4 + 1];
    uint8_t b = raw_pixels[i + 4 + 2];
    uint8_t a = raw_pixels[i + 4 + 3];

    uint32_t pixel = pack_argb_premultiplied(r, g, b, a);
    fwrite(&pixel, sizeof(uint32_t), 1, out_file);
  }

  fclose(out_file);
  stbi_image_free(raw_pixels);

  return EXIT_SUCCESS;
}
