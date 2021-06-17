#include "Image.h"
#include <bitset>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

int main() {
  Image img("img/cosmos.png");
  img.color_mask(0, 1, 1);
  img.write("color_masked.png");
}
