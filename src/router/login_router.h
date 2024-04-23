#ifndef LOGIN_ROUTER_H_
#define LOGIN_ROUTER_H_

#include "../../lib/crow_all.h"
#include "../controllers/auth_controller.h"
#include "../controllers/user_controller.h"

inline crow::Blueprint CreateApiAuthBlueprint(AuthController& auth, UserController& users) {
  crow::Blueprint blueprint{"api/auth"};

  CROW_BP_ROUTE(blueprint, "/")
    .methods(crow::HTTPMethod::POST)
  ([&](const crow::request& req) {
    auto body_json{crow::json::load(req.body)};
    if (!body_json)
      return crow::response{crow::status::BAD_REQUEST};

    std::string email{body_json["email"].s()}, password{body_json["password"].s()};
    int id{users.GetUserId(email, password)};
    if (id == -1)
      return crow::response{crow::status::FORBIDDEN};

    return crow::response{auth.CreateToken(id)};
  });

  return blueprint;
}

#endif
