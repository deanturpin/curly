#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>

int main() {

  const std::string command =
    "curl 'https://min-api.cryptocompare.com/data/all/exchanges"
    "?extraParams=https://github.com/deanturpin/arbitrage'";

  const std::string file = "/tmp/stdout.txt";
  const std::string pipe = " 2> /tmp/stderr.txt 1> ";
  const std::string complete_command = command + pipe + file;

  // Attempt to run command
  std::stringstream ss("empty");
  system(complete_command.c_str());

  // Read the result
  std::ifstream in(file);
  if (in.good())
    ss << in.rdbuf();

  std::cout << ss.str() << '\n';
}
