#include "Image.h"
#include <bitset>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

int main() {
  Image img("img/cosmos.png");

  Image avg_img = img;
  avg_img.grayscale_average();
  avg_img.write("grayscaled.png");

  Image luminance = img;
  luminance.grayscale_luminance();
  luminance.write("grayscaled_lum.png");
}
