#include "Steganography.h"
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace Steg;
using namespace std;

Status Coding::LSB_encode(const Image &image, const std::string &message) {
  std::cout << "Encoding: " << message << std::endl;
  // TODO: Add tests
  if (message.length() < image.get_data_size()) {
    __throw_invalid_argument("The message is too large, deacrease message "
                             "length or provide larger image");
  }

  for (int i = 0; i < image.get_data_size(); i++) {
    image.m_data[i] &= 0xfe; // Clear the last bit (set it to 0)
    image.m_data[i] |= message[i]; // Encode the data in the last bit
  }

  return Status::SUCCESS;
}
