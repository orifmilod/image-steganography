#include "Image.h"
#include "Steganography.h"
#include <string>

using namespace std;

int main() {
  Steg::Image img("new-image.png");
  Steg::Coding steg;
  img.color_mask(1, 0, 0);
  // img.write("new-image.png");
  Steg::Status status = steg.LSB_encode(img, "secret message");
  cout << "Status: " << to_string(status) << endl;
}
