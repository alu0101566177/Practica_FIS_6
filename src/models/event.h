#ifndef MODELS_EVENT_H_
#define MODELS_EVENT_H_

#include <string>

struct Event {
  int id;
  int capacity;
  std::string title;
  std::string description;
  std::string location;
  std::string date;
};

#endif
