#ifndef CURLY_H
#define CURLY_H

#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>

std::string curly(const std::string &url, const bool use_network = true) {

  // Known errors
  const std::vector<std::pair<unsigned int, std::string>> errors {
  {0, "ok"},
  {1536, "no-network"},
  {32512, "path-to-curl-incorrect"},
  };

  // Construct the command with redirects to stdout and stderr
  const std::string file = "/tmp/stdout.txt";
  const std::string command =
    "/usr/bin/curl \'" + url + "\' 2> /tmp/stderr.txt 1> " + file;

  // Attempt to run command (unless network access is disable)
  const unsigned int error_code = use_network ? system(command.c_str()) : 0;

  // Look up string for error code
  const auto it = std::find_if(errors.cbegin(), errors.cend(), [&error_code](const auto &e){
                                return e.first == error_code;
                               });

  const std::string error_string =
    (it != errors.cend() ? it->second : std::to_string(error_code));

  // Read the response written to the stdout file
  std::stringstream ss("{\"error\" : \"" + error_string + "\"}");
  std::ifstream in(file);
  if (error_code == 0 && in.good()) {
    ss.str("");
    ss << in.rdbuf();
  }

  // Return the response (or error)
  return ss.str();
}

// Search for a JSON key/value pair
std::string find_token(const std::string &token, const std::string &s) noexcept {

  std::string token_value = "";

  const auto i = s.find('"' + token + '"');
  if (i != std::string::npos) {
    token_value = s.substr(i + 3 + token.size());

    // Refine token, try to find the end of the value definition
    const auto end = token_value.find_first_of("},");

    if (end != std::string::npos)
      token_value = token_value.substr(0, end);
  }

  return token_value;
}

#endif
