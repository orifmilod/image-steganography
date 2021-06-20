#include "Image.h"
#include "Steganography.h"
#include <string>

using namespace std;

int main() {
  Steg::Image img("img/cosmos.png");
  Steg::Coding steg;
  Steg::Status status = steg.LSB_encode(img, "secret message");
  cout << "Status: " << to_string(status) << endl;
}
