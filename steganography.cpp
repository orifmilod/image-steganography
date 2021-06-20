#include "Steganography.h"
#include <cstring>
#include <iostream>
#include <string>

using namespace Steg;
Status Coding::LSB_encode(const Image &image, const std::string &message) {
  std::cout << "Encoding stuff: " << message << std::endl;

  for (int i = 0; i < image.get_data_size(); i++) {
    // TODO: encode the message
  }

  return Status::SUCCESS;
}
