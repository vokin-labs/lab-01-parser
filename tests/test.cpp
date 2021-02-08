// Copyright 2021 Vokin-labs <vokinsilok2305@mail.ru>

#include <gtest/gtest.h>
#include <fstream>
#include <header.hpp>

TEST(PrintTable, PrintTable) {
    std::fstream file{"file.json", std::ios::out};

    std::string jsonString = R"({
    "items": [
    {
      "name": "Ivanov Petr",
          "group": "1",
          "avg": "4.25",
          "debt": null
    },
    {
      "name": "Sidorov Ivan",
          "group": 31,
          "avg": 4,
          "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
          "group": "IU8-31",
          "avg": 3.33,
          "debt": [
      "C++",
          "Linux",
          "Network"
      ]
    }
    ],
    "_meta": {
      "count": 3
    }
 })";

    file << jsonString;
    file.close();

    auto students = LoadFromFile("file.json");
    Print(students, std::cout);
    EXPECT_TRUE(true);
}

TEST(Errors, NonExistingFile) {
    std::string exceptionString;
    try {
        auto students = LoadFromFile("non/existing/file.json");
    } catch (std::runtime_error &e) {
        exceptionString = e.what();
    }
    EXPECT_EQ(exceptionString, "non/existing/file.json not open");
}

TEST(Errors, ItemsIsNotArray) {
    std::fstream file{"file.json", std::ios::out};
    std::string exceptionString;

    std::string jsonString = R"({
    "items":
    {
      "name": "Ivanov Petr",
          "group": "1",
          "avg": "4.25",
          "debt": null
    },
    "_meta": {
      "count": 3
    }
 })";

    file << jsonString;
    file.close();

    try {
        auto students = LoadFromFile("file.json");
    } catch (std::runtime_error &e) {
        exceptionString = e.what();
    }
    EXPECT_EQ(exceptionString, "Items most be array type");
}

TEST(Errors, IncorrectMeta) {
    std::fstream file{"file.json", std::ios::out};
    std::string exceptionString;

    std::string jsonString = R"({
    "items": [
    {
      "name": "Ivanov Petr",
          "group": "1",
          "avg": "4.25",
          "debt": null
    },
    {
      "name": "Sidorov Ivan",
          "group": 31,
          "avg": 4,
          "debt": "C++"
    },
    {
      "name": "Pertov Nikita",
          "group": "IU8-31",
          "avg": 3.33,
          "debt": [
      "C++",
          "Linux",
          "Network"
      ]
    }
    ],
    "_meta": {
      "count": 123
    }
 })";

    file << jsonString;
    file.close();

    try {
        auto students = LoadFromFile("file.json");
    } catch (std::runtime_error &e) {
        exceptionString = e.what();
    }
    EXPECT_EQ(exceptionString, "meta_: count and items size mismatch");
}
