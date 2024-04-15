#ifndef API_H_
#define API_H_

#include "../lib/crow_all.h"
#include "db/database.h"
#include "controllers/auth_controller.h"
#include "controllers/crud_controller.h"

template <class Model>
inline crow::response CreateRoute(const crow::request& req, AuthController& auth, CRUDController<Model>& controller) {
  std::string token{req.get_header_value("Authorization")};
  if (token.length() == 0 || !auth.ValidAdminToken(token))
    return crow::response{crow::status::UNAUTHORIZED};

  auto body_json{crow::json::load(req.body)};
  if (!body_json)
    return crow::response{crow::status::BAD_REQUEST};

  int id{controller.Create(Model::FromJson(body_json))};
  if (id == -1)
    return crow::response{crow::status::CONFLICT};

  crow::json::wvalue response_body{{"id", id}};
  return crow::response{crow::status::CREATED, response_body};  
}

#endif
