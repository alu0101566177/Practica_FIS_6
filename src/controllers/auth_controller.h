#ifndef AUTH_CONTROLLER_H_
#define AUTH_CONTROLLER_H_

#include "../db/database.h"
#include "user_controller.h"
#include <optional>

const int kAdminId{1};

class AuthController {
  public:
    AuthController(Storage& storage) : users_{storage} {}

    std::string CreateToken(const int id) const {
      std::optional<User> user{users_.GetById(id)};
      if (!user.has_value()) return "";
      crow::json::wvalue json_token{
        {"email", user->email},
        {"password", user->password}
      };
      std::string raw_token{json_token.dump()};
      return crow::utility::base64encode(raw_token, raw_token.size());
    }

    bool ValidToken(const std::string& token) const {
      std::string raw_token{crow::utility::base64decode(token)};
      crow::json::rvalue json{crow::json::load(raw_token)};

      std::string email{json["email"].s()};
      std::string password{json["password"].s()};

      return users_.GetUserId(email, password) != -1;
    }

    bool ValidAdminToken(const std::string& token) const {
      std::string raw_token{crow::utility::base64decode(token)};
      crow::json::rvalue json{crow::json::load(raw_token)};

      std::string email{json["email"].s()};
      std::string password{json["password"].s()};

      return users_.GetUserId(email, password) == kAdminId;
    }

  private:
    UserController users_;
};

#endif
