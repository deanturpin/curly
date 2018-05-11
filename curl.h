#ifndef TINY_CURL_H
#define TINY_CURL_H

#include <sstream>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <regex>

namespace tiny {

auto curl(const std::string url) {

  // Known errors
  const std::map<unsigned int, std::string> errors {
  {0, "ok"},
  {1536, "no-network"},
  {32512, "path-to-curl-incorrect"},
  };

  // Construct the command with redirects to stdout and stderr
  const std::string file = "/tmp/stdout.txt";
  const std::string command =
    "/usr/bin/curl \'" + url + "\' 2> /tmp/stderr.txt 1> " + file;

  // Attempt to run command
  const unsigned int error_code = system(command.c_str());

  // Look up string for error code
  const auto it = errors.find(error_code);
  const std::string error_string =
    (it != errors.cend() ? it->second : std::to_string(error_code));

  // Read the response written to the stdout file
  std::stringstream ss("{\"error\" : \"" + error_string + "\"}");
  ss << std::ifstream(file).rdbuf();

  // Return the response (or error)
  return ss.str();
}

// Parse JSON string and return map of tokens
auto json(const std::string s) noexcept {

  // Return a map of string/strings
  std::map<std::string, std::string> json_map;

  try {

    // Token delimiters
    std::regex r(R"([ ,:'"\{\}]+)");

    // Iterate over the tokens and push them onto a container
    std::vector<std::string> tokens;
    std::copy(std::sregex_token_iterator(s.begin(), s.end(), r, -1),
              std::sregex_token_iterator(), std::back_inserter(tokens));

    // Create map, stripping empty tokens
    for (unsigned long i = 0; i < tokens.size(); ++i)
      if (tokens[i] != "") {
        json_map[tokens[i]] = tokens[i + 1];
        ++i;
      }

  } catch (std::regex_error e) {
    // Quietly discard exceptions
  }

  return json_map;
}

}

#endif
