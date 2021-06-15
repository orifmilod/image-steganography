#include <_types/_uint8_t.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Image.h"
#include "stb_image.h"
#include "stb_image_write.h"
#include <iostream>


Image::Image(int width, int height, int channels)
    : m_width(width), m_height(height), m_channels(channels) {
  set_data_size();
  m_data = new uint8_t[m_data_size];
}

Image::Image(const Image &img)
    : Image(img.m_width, img.m_height, img.m_channels) {
  memcpy(m_data, img.m_data, img.m_data_size);
}

Image::~Image() { stbi_image_free(m_data); }

Image::Image(const std::string &filename) {
  if (!read(filename)) {
    std::cout << "Error while reading the image!";
    return;
  }

  set_data_size();
  std::cout << "Successfuly read image!" << std::endl;
}

bool Image::read(const std::string &filename) {
  m_data = stbi_load(filename.c_str(), &m_width, &m_height, &m_channels, 0);
  m_image_type = get_file_type(filename);
  return m_data != nullptr;
}

bool Image::write(const std::string &filename) {
  ImageType img_type = get_file_type(filename);

  int success;
  switch (img_type) {
  case ImageType::PNG:
    success = stbi_write_png(filename.c_str(), m_width, m_height, m_channels,
                             m_data, m_width * m_channels);

  case ImageType::TGA:
    success =
        stbi_write_tga(filename.c_str(), m_width, m_height, m_channels, m_data);

  case ImageType::BMP:
    success =
        stbi_write_bmp(filename.c_str(), m_width, m_height, m_channels, m_data);

  case ImageType::JPG:
    success =
        stbi_write_bmp(filename.c_str(), m_width, m_height, m_channels, m_data);

  case ImageType::UNKNOWN:
    success = 0;
  }

  return success != 0;
}

void Image::set_data_size() { m_data_size = m_height * m_width * m_channels; }

ImageType get_file_type(const std::string &filename) {
  const char *extension = strrchr(filename.c_str(), '.');

  if (extension != NULL) {
    if (strcmp(extension, ".png") == 0) {
      return ImageType::PNG;
    }

    if (strcmp(extension, ".jpg") == 0) {
      return ImageType::PNG;
    }

    if (strcmp(extension, ".bmp") == 0) {
      return ImageType::BMP;
    }

    if (strcmp(extension, ".tga") == 0) {
      return ImageType::TGA;
    }
  }

  std::cerr << "Error getting image extension" << std::endl;
  return ImageType::UNKNOWN;
}
