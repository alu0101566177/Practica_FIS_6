#ifndef CONTROLLERS_USER_H_
#define CONTROLLERS_USER_H_

#include "../db/database.h"
#include "../models/user.h"
#include <vector>

using namespace sqlite_orm;

class UserController {
  public:
    UserController(Storage& storage) : storage_{storage} {}

    int GetUser(const std::string email, const std::string password) const {
      auto filter{where(c(&User::email) == email and c(&User::password) == password)};
      auto matches{storage_.select(columns(&User::id), filter)};
      if (matches.size() == 0) return -1;
      return get<0>(matches[0]);
    }

    int CreateUser(const std::string& name,
                   const std::string& email,
                   const std::string& password) const {
      User user{-1, name, email, password};
      try {
        return storage_.insert(user);
      } catch (const std::system_error& err) {
        return -1;  
      }
    }

    bool DeleteUser(const std::string email, const std::string password) const {
      int id{GetUser(email, password)};
      if (id == -1) return false;
      storage_.remove<User>(id);
      return true;
    }

  private:
    Storage& storage_;
};

#endif
