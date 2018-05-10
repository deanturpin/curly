#ifndef CURL_H
#define CURL_H

#include <sstream>
#include <fstream>

std::string curl(const std::string url) {

  const std::string command = "curl \'" + url + "\'";
  const std::string file = "/tmp/stdout.txt";
  const std::string pipe = " 2> /tmp/stderr.txt 1> ";
  const std::string complete_command = command + pipe + file;

  // Attempt to run command
  system(complete_command.c_str());

  // Read the result
  std::stringstream ss;
  std::ifstream in(file);
  if (in.good())
    ss << in.rdbuf();

  return ss.str();
}

#endif
