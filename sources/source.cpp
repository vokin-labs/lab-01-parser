// Copyright 2021 Vokin-labs <vokinsilok2305@mail.ru>

#include <fstream>
#include <header.hpp>
#include <iomanip>
#include <nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>

std::string GetName(const json &j) { return j.get<std::string>(); }

std::any GetGroup(const json &j) {
    if (j.is_string())
        return j.get<std::string>();
    else
        return j.get<int>();
}

std::any GetAvg(const json &j) {
    if (j.is_null()) {
        return nullptr;
    } else if (j.is_string()) {
        return j.get<std::string>();
    } else if (j.is_number_float()) {
        return j.get<float>();
    } else {
        return j.get<int>();
    }
}

std::any GetDebt(const json &j) {
    if (j.is_null()) {
        return nullptr;
    } else if (j.is_string()) {
        return j.get<std::string>();
    } else {
        return j.get<std::vector<std::string>>();
    }
}

std::vector<Student> LoadFromFile(const std::string &filepath) {
    std::fstream file;
    file.open(filepath, std::ios::in);
    if (!file.is_open()) {
        throw std::runtime_error(filepath + " not open");
    }

    json j;
    file >> j;
    file.close();

    std::vector<Student> result;

    if (!j.at("items").is_array()) {
        throw std::runtime_error("Items most be array type");
    }

    if (j.at("items").size() != j.at("_meta").at("count")) {
        throw std::runtime_error("meta_: count and items size mismatch");
    }

    for (std::size_t i = 0; i < j.at("items").size(); i++) {
        Student student;
        student.name = GetName(j.at("items")[i].at("name"));
        student.group = GetGroup(j.at("items")[i].at("group"));
        student.avg = GetAvg(j.at("items")[i].at("avg"));
        student.debt = GetDebt(j.at("items")[i].at("debt"));
        result.push_back(student);
    }

    return result;
}

void Print(const Student &student, std::ostream &os) {
    os << "| " << std::left << std::setw(16) << student.name;

    if (student.group.type() == typeid(int)) {
        os << "| " << std::setw(10) << std::left
           << std::any_cast<int>(student.group);
    } else {
        os << "| " << std::setw(10) << std::left
           << std::any_cast<std::string>(student.group);
    }

    if (student.avg.type() == typeid(float)) {
        os << "| " << std::setw(5) << std::left
           << std::any_cast<float>(student.avg);
    } else if (student.avg.type() == typeid(int)) {
        os << "| " << std::setw(5) << std::left << std::any_cast<int>(student.avg);
    } else {
        os << "| " << std::setw(5) << std::left
           << std::any_cast<std::string>(student.avg);
    }

    if (student.debt.type() == typeid(std::nullptr_t)) {
        os << "| " << std::setw(10) << std::left << "null" << std::right << "|";
    } else if (student.debt.type() == typeid(std::string)) {
        os << "| " << std::setw(10) << std::left
           << std::any_cast<std::string>(student.debt) << std::right << "|";
    } else {
        os << "| " << std::setw(5) << std::left
           << std::any_cast<std::vector<std::string>>(student.debt).size()
           << std::setw(5) << std::left << "items" << std::right << "|";
    }
}

void Print(const std::vector<Student> &students, std::ostream &os) {
    std::string separator;

    separator += "|-";
    for (int i = 0; i < 16; ++i) {
        separator += "-";
    }
    separator += "|-";
    for (int i = 0; i < 10; ++i) {
        separator += "-";
    }
    separator += "|-";
    for (int i = 0; i < 5; ++i) {
        separator += "-";
    }
    separator += "|-";
    for (int i = 0; i < 10; ++i) {
        separator += "-";
    }
    separator += "|";

    os << "| " << std::left << std::setw(16) << "name";
    os << "| " << std::left << std::setw(10) << "group";
    os << "| " << std::left << std::setw(5) << "avg";
    os << "| " << std::left << std::setw(10) << "debt";
    os << std::right << "|";
    os << std::endl << separator << std::endl;
    for (auto &student : students) {
        Print(student, os);
        os << std::endl << separator << std::endl;
    }
}
