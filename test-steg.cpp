

const string ZERO_WIDTH_SPACE = "\u200b";
const string ZERO_WIDTH_NON_JOINER = "\u200c";
const string ZERO_WIDTH_NO_BREAK_SPACE = "\u200d";

string text_to_bin(string &text) {
  string encoded = "";
  // TODO: fix this garbage
  for (size_t i = 0; i < text.size(); i++) {
    if (i == 0) {
      encoded += bitset<8>(text[i]).to_string();
    } else {
      encoded += ' ' + bitset<8>(text[i]).to_string();
    }
  }

  return encoded;
}

string bin_to_zero_width(string bin) {
  string zero_width_string = "";

  // TODO: fix this garbage
  for (size_t i = 0; i < bin.size(); i++) {
    if (bin[i] == '1') {
      zero_width_string += ZERO_WIDTH_SPACE;
    } else if (bin[i] == '0') {
      zero_width_string += ZERO_WIDTH_NON_JOINER;
    } else {
      zero_width_string += ZERO_WIDTH_NO_BREAK_SPACE;
    }
  }
  return zero_width_string;
}

