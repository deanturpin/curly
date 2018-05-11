#ifndef TINY_CURL_H
#define TINY_CURL_H

#include <sstream>
#include <string>
#include <fstream>

namespace tiny {

std::string curl(const std::string url) {

  // Construct the command with redirects to stdout and stderr
  const std::string file = "/tmp/stdout.txt";
  const std::string command =
    "/usr/bin/curl \'" + url + "\' 2> /tmp/stderr.txt 1> " + file;

  // Attempt to run command
  const auto error = system(command.c_str());

  // Read the response written to the stdout file
  std::stringstream ss("{\"error\" : \"" + std::to_string(error) + "\"}");
  ss << std::ifstream(file).rdbuf();

  // Return the response (or error)
  return ss.str() + '\n';
}

}

#endif
