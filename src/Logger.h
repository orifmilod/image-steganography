#include "Steganography.h"
#include <iostream>
#include <string>

const std::string RED = "\e[0;91m";
const std::string BLUE = "\e[0;96m";
const std::string YELLOW = "\e[0;93m";

enum class Severity { INFO, WARN, ERROR };

class Logger {
private:
  static void print_colored(const char *log, Severity severity) {
    const char *color_code = nullptr;

    switch (severity) {
    case Severity::INFO:
      color_code = BLUE.c_str();
      break;
    case Severity::WARN:
      color_code = YELLOW.c_str();
      break;
    case Severity::ERROR:
      color_code = RED.c_str();
      break;
    }

    std::cout << "\033" << color_code << log << "\033[0m -- ";
  }

  template <class... Args> static void print_args(Args... args) {
    (std::cout << ... << args) << std::endl;
  }

public:
  template <class... Args> static void info(Args... args) {
    print_colored("[INFO] ", Severity::INFO);
    print_args(args...);
  }

  template <class... Args> static void warn(Args... args) {
    print_colored("[WARN] ", Severity::WARN);
    print_args(args...);
  }

  template <class... Args> static void error(Args... args) {
    print_colored("[ERROR]", Severity::ERROR);
    print_args(args...);
  }
};

