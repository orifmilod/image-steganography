#include "Image.h"
#include "Steganography.h"

using namespace std;

int main() {
  Steg::Image img("img/cosmos.png");
  img.color_mask(0, 1, 1);
  img.write("color_masked.png");
}
