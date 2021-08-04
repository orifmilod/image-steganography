#include <stdint.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "Image.h"
#include "stb/stb_image.h"
#include <iostream>

constexpr float RED_COLOR_WEIGHT = 0.2126;
constexpr float GREEN_COLOR_WEIGHT = 0.7152;
constexpr float BLUE_COLOR_WEIGHT = 0.0722;
using namespace Steg;

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

ImageType Steg::get_file_type(const std::string &filename) {
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

Image &Image::grayscale_average() {
  if (m_channels < 3) {
    std::cout << "Less than 3 channels found in the image (assuming that image "
                 "is grayscaled) \n";
    return *this;
  }

  for (int i = 0; i < m_data_size; i += m_channels) {
    int avg_gray = (m_data[i] + m_data[i + 1] + m_data[i + 2]) / 3;

    // set all the 3 color to their average
    memset(m_data + i, avg_gray, 3);
  }
  return *this;
}

Image &Image::grayscale_luminance() {
  if (m_channels < 3) {
    std::cout << "Less than 3 channels found in the image (assuming that image "
                 "is grayscaled) \n";
    return *this;
  }

  for (int i = 0; i < m_data_size; i += m_channels) {
    int avg_weighted =
        (RED_COLOR_WEIGHT * m_data[i] + GREEN_COLOR_WEIGHT * m_data[i + 1] +
         BLUE_COLOR_WEIGHT * m_data[i + 2]) /
        3;

    // set all the 3 color to their average
    memset(m_data + i, avg_weighted, 3);
  }
  return *this;
}

Image &Image::color_mask(float red, float green, float blue) {
  if (m_channels < 3) {
    std::cout << "Less than 3 channels found in the image (assuming that image "
                 "is grayscaled) \n";
    return *this;
  }

  for (int i = 0; i < m_data_size; i += m_channels) {
    m_data[i] *= red;
    m_data[i + 1] *= green;
    m_data[i + 2] *= blue;
  }

  return *this;
}

int Image::get_width() const { return m_width; }
int Image::get_height() const { return m_height; }
int Image::get_channels() const { return m_channels; }
int Image::get_data_size() const { return m_data_size; }
