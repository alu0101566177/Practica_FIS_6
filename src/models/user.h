#ifndef MODELS_USER_H_
#define MODELS_USER_H_

#include "../../lib/crow_all.h"
#include <string>

struct User {
  int id;
  std::string name;
  std::string email;
  std::string password;
};

#endif
