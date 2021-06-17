#pragma once

#include <_types/_uint8_t.h>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <string.h>
#include <string>

namespace Steg {

enum class ImageType { PNG, JPG, BMP, TGA, UNKNOWN };

inline const char *to_string(ImageType img_type) {
  switch (img_type) {
  case ImageType::PNG:
    return "PNG";

  case ImageType::TGA:
    return "TGA";

  case ImageType::BMP:
    return "BMP";

  case ImageType::JPG:
    return "JPG";

  case ImageType::UNKNOWN:
    return "UNKNOWN";
  }
  // throw std::invalid_argument(
  // "Code error,  enum not suppored" +
  // 3 std::to_string(
  // static_cast<std::underlying_type<Type>::type>(type)));
  return "UNKNOWN";
}

ImageType get_file_type(const std::string &filename);

class Image {
private:
  uint8_t *m_data = nullptr;
  size_t m_data_size = 0;
  int m_width, m_height;
  int m_channels;
  ImageType m_image_type;
  void set_data_size();

public:
  Image(const std::string &filename);
  Image(int width, int height, int channels);
  Image(const Image &image);
  ~Image();

  bool read(const std::string &filename);

  /*
  * The functions create an image file defined by the parameters. The image
  * is a rectangle of pixels stored from left-to-right, top-to-bottom.
  * Each pixel contains 'comp' channels of data stored interleaved with 8-bits
  * per channel, in the following order: 1=Y, 2=YA, 3=RGB, 4=RGBA. (Y is
  * monochrome color.) The rectangle is 'w' pixels wide and 'h' pixels tall.
  * The *data pointer points to the first byte of the top-left-most pixel.
  * For PNG, "stride_in_bytes" is the distance in bytes from the first byte of
  * a row of pixels to the first byte of the next row of pixels.
  */
  bool write(const std::string &filename);

  // Adding all Red-Green-Blue image and dividing it by 3
  Image &grayscale_average();

  /**
   * Basically same as average but the colors have weights, the weights comes
   * from the fact that humans  are more sensitive to some colors over the
   * others.
   * Here is the formulea for it(0.2125 * red + 0.7152 * green + 0.0722 blue)
   * Reference: https://en.wikipedia.org/wiki/Grayscale
   */

  Image &grayscale_luminance();

  Image &color_mask(float red, float green, float blue);
};

} // namespace Steg
