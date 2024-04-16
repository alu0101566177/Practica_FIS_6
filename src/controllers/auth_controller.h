#ifndef AUTH_CONTROLLER_H_
#define AUTH_CONTROLLER_H_

#include "../db/database.h"
#include "../utils/hex_codec.h"
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
      return StringToHex(raw_token);
    }

    bool ValidToken(const std::string& token) const {
      std::string raw_token{HexToString(token)};
      crow::json::rvalue json{crow::json::load(raw_token)};

      std::string email{json["email"].s()};
      std::string password{json["password"].s()};

      return users_.GetUserId(email, password) != -1;
    }

    bool ValidAdminToken(const std::string& token) const {
      std::string raw_token{HexToString(token)};
      crow::json::rvalue json{crow::json::load(raw_token)};

      std::string email{json["email"].s()};
      std::string password{json["password"].s()};

      return users_.GetUserId(email, password) == kAdminId;
    }

    std::optional<User> GetUserByToken(const std::string& token) {
      std::string raw_token{HexToString(token)};
      crow::json::rvalue json{crow::json::load(raw_token)};

      std::string email{json["email"].s()};
      std::string password{json["password"].s()};
      
      int id{users_.GetUserId(email, password)};
      if (id == -1) return std::nullopt;
      return users_.GetById(id);
    }

  private:
    UserController users_;
};

#endif
