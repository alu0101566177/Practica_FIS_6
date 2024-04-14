#ifndef MODELS_LIBRARY_H_
#define MODELS_LIBRARY_H_

#include "../../lib/crow_all.h"
#include <string>

struct Library {
  int id;
  int capacity;
  std::string name;
  std::string location;

  static Library FromJson(const crow::json::rvalue&);
  crow::json::wvalue ToJson() const;
};

#endif
