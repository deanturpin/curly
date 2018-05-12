#ifndef CURLY_H
#define CURLY_H

#include <sstream>
#include <string>
#include <map>
#include <fstream>
#include <regex>

auto curly(const std::string url, const bool use_network = true) {

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

  // Attempt to run command (unless network access is disable)
  const unsigned int error_code = use_network ? system(command.c_str()) : 0;

  // Look up string for error code
  const auto it = errors.find(error_code);
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

// Parse JSON string and return map of tokens
auto jsony(const std::string s) noexcept {

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
        const auto key = tokens[i];
        const auto value = tokens[i + 1];
        json_map[key] = value;
        ++i;
      }

  } catch (std::regex_error e) {
    // Quietly discard exceptions
  }

  return json_map;
}

#endif
