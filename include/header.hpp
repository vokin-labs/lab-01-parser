// Copyright 2020 Your Name <your_email>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#endif // INCLUDE_HEADER_HPP_
// Copyright 2021 Vokin-labs <vokinsilok2305@mail.ru>

#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <any>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using nlohmann::json;

struct Student {
  std::string name;
  std::any group;
  std::any avg;
  std::any debt;
};

void Print(const Student &student, std::ostream &os);
void Print(const std::vector<Student> &students, std::ostream &os);

std::vector<Student> LoadFromFile(const std::string &filepath);

#endif  // INCLUDE_HEADER_HPP_
