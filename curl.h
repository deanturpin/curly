#ifndef TINY_CURL_H
#define TINY_CURL_H

#include <sstream>
#include <string>
#include <fstream>

namespace tiny {

std::string curl(const std::string url) {

  // Construct the full command with redirects to stdout and stderr
  const std::string command = "/usr/bin/curl \'" + url + "\'";
  const std::string stdout_file = "/tmp/stdout.txt";
  const std::string stderr_file = " 2> /tmp/stderr.txt 1> ";
  const std::string complete = command + stderr_file + stdout_file;

  // Attempt to run command
  system(complete.c_str());

  // Read the result from stdout
  std::stringstream ss;
  std::ifstream in(stdout_file);
  ss << in.rdbuf() << '\n';

  // Return the response or an empty string if there wasn't one
  return ss.str();
}

}

#endif
