#include "Steganography.h"
#include "Logger.h"
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace Steg;
using namespace std;

constexpr int HEADER_SIZE = 16;

// Number of bits to encode in every pixel 10101001 => 1010100[1]
// (most right bit(s) are used for encoding)
constexpr int ENCODE_BIT_SIZE = 1;
constexpr int NUM_OF_BITES = 8;

Status Coding::LSB_encode(const Image &image, const std::string &message) {
  // Please come up with better naming
  int chunk_size = (NUM_OF_BITES - ENCODE_BIT_SIZE + 1);
  Logger::info("Chunk size", chunk_size);

  if (message.length() * chunk_size) {
    Logger::error("The message is too large, deacrease message length or "
                  "provide larger image");

    return Status::FAIL;
  }

  u_int16_t message_size = message.size() * chunk_size;
  Logger::info("Encoding ", message);

  // Econde message size in the header
  for (int i = 0; i < HEADER_SIZE; i++) {
    image.m_data[i] &= 0xfe; // Clear the last bit

    // Reads from left to right (by shifting) and encode it in the image header
    image.m_data[i] |= (message_size >> (HEADER_SIZE - 1 - i)) & 1;
  }

  // Encode the message
  for (int i = 0; i < image.get_data_size(); i++) {
    image.m_data[i + HEADER_SIZE] &= 0xfe; // Clear the last bit (set it to 0)
    image.m_data[i + HEADER_SIZE] |=
        message[i]; // Encode the data in the last bit
  }

  return Status::SUCCESS;
}

Status Coding::LSB_decode(const Image &image) {
  std::cout << "Decoing the message from the image: " << std::endl;
  uint64_t msg_length = 0;

  // Get the message size from the header
  for (int i = 0; i < HEADER_SIZE; i++) {
    msg_length = (msg_length << 1) | (image.m_data[i] & 1);
  }
  std::cout << "Message length: " << msg_length << std::endl;

  // for (int i = 0; i < msg_length; i++) {
  // image.m_data[i]
  // }

  return Status::SUCCESS;
}
