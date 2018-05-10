#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

int main() {

  const std::string command = "ls rah";
  const std::string file = "/tmp/arbitrage.txt";
  const std::string pipe = " 2>/dev/null > ";
  const std::string complete_command = command + pipe + file;

  std::stringstream ss("empty");

  // Attempt to run command and read the result
  if (system((command + pipe + file).c_str()) != 0) {
    std::ifstream in(file);
    ss << in.rdbuf();
  }

  std::cout << ss.str();

  // FILE *popen(const char *command, const char *type);
}
