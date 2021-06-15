#include <_types/_uint8_t.h>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <string.h>
#include <string>

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
  bool write(const std::string &filename);
};
