#pragma once

#include "Image.h"
#include <string>

namespace Steg {

class Coding {

public:
  void LSB_encode(const Image &image, const std::string &message);
  void LSB_decode(const Image &image);

  void LSB_encode_odd(const std::string &imageName, const std::string &message);
  void LSB_decode_odd(const std::string &imageName);

  void LSB_encode_even(const std::string &imageName,
                       const std::string &message);
  void LSB_decode_even(const std::string &imageName);

  void LSB_decode_max(const std::string &imageName, const std::string &message);
  void LSB_encode_max(const std::string &imageName);

  void LSB_decode_min(const std::string &imageName, const std::string &message);
  void LSB_encode_min(const std::string &imageName);

  void LSB_decode_prime(const std::string &imageName,
                        const std::string &message);
  void LSB_encode_prime(const std::string &imageName);

  void LSB_encode_spiral(const std::string &imageName,
                         const std::string &message);
  void LSB_decode_spiral(const std::string &imageName);

  void LSB_encode_magic_square(const std::string &imageName,
                               const std::string &message);
  void LSB_decode_magic_square(const std::string &imageName);
};

} // namespace Steg
