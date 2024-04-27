#ifndef CONTROLLERS_USER_H_
#define CONTROLLERS_USER_H_

#include "../db/database.h"
#include "../models/user.h"
#include "crud_controller.h"

using namespace sqlite_orm;

class UserController : public CRUDController<User> {
  public:
    UserController(Storage& storage) : CRUDController<User>{storage} {}

    int GetUserId(const std::string email, const std::string password) const {
      auto filter{where(c(&User::email) == email and c(&User::password) == password)};
      auto matches{storage_.select(columns(&User::id), filter)};
      if (matches.size() == 0) return -1;
      return get<0>(matches[0]);
    }

    bool Delete(const int id) const {
      try {
        if (id == 1) return false;
        storage_.remove<User>(id);
        return true;
      } catch (const std::system_error& err) {
        return false;
      }
    }
};

#endif
