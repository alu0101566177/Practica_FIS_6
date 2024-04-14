#ifndef MODELS_EVENT_H_
#define MODELS_EVENT_H_

#include "../../lib/crow_all.h"
#include <string>

struct Event {
  int id;
  int capacity;
  std::string title;
  std::string description;
  std::string location;
  std::string date;

  static Event FromJson(const crow::json::rvalue&);
  crow::json::wvalue ToJson() const;
};

#endif
