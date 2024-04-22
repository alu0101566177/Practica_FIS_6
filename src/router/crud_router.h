#ifndef CRUD_ROUTER_H_
#define CRUD_ROUTER_H_

#include "../../lib/crow_all.h"
#include "../controllers/crud_controller.h"
#include "../controllers/auth_controller.h"
#include "../utils/serialize_models.h"

template <class Model>
class CRUDRouter {
  public:
    CRUDRouter(AuthController& auth, CRUDController<Model>& controller, const bool admin_read = false) :
      auth_{auth}, controller_{controller}, admin_read_{admin_read} {}

    crow::Blueprint CreateBlueprint(const std::string& prefix) const;

  private:
    bool AdminAuth(const crow::request& req) const {
      std::string token{req.get_header_value("Authorization")};
      return token.length() != 0 && auth_.ValidAdminToken(token);
    }

    AuthController& auth_;
    CRUDController<Model>& controller_;
    bool admin_read_;
};

template <class Model>
crow::Blueprint CRUDRouter<Model>::CreateBlueprint(const std::string& prefix) const {
  crow::Blueprint blueprint{prefix};

  CROW_BP_ROUTE(blueprint, "/")([&](const crow::request& req) {
    if (this->admin_read_ && !this->AdminAuth(req)) {
      return crow::response{crow::status::UNAUTHORIZED};
    }
    return crow::response{SerializeModels(controller_.GetAll())};
  });

  CROW_BP_ROUTE(blueprint, "/<int>")([&](const crow::request& req, const int id) {
    if (this->admin_read_ && !this->AdminAuth(req))
      return crow::response{crow::status::UNAUTHORIZED};
    std::optional<Model> object{controller_.GetById(id)};
    if (!object.has_value())
      return crow::response{crow::status::NOT_FOUND};
    return crow::response{object->ToJson()};
  });

  CROW_BP_ROUTE(blueprint, "/")
    .methods(crow::HTTPMethod::POST)
  ([&](const crow::request& req) {
    if (!this->AdminAuth(req))
      return crow::response{crow::status::UNAUTHORIZED};

    auto body_json{crow::json::load(req.body)};
    if (!body_json)
      return crow::response{crow::status::BAD_REQUEST};

    int id{controller_.Create(Model::FromJson(body_json))};
    if (id == -1)
      return crow::response{crow::status::CONFLICT};

    crow::json::wvalue response_body{{"id", id}};
    return crow::response{crow::status::CREATED, response_body};
  });

  CROW_BP_ROUTE(blueprint, "/<int>")
    .methods(crow::HTTPMethod::DELETE)
  ([&](const crow::request& req, const int id) {
    if (!this->AdminAuth(req))
      return crow::response{crow::status::UNAUTHORIZED};
    if (!controller_.Delete(id))
      return crow::response{crow::status::NOT_FOUND};
    return crow::response{crow::status::OK};
  });

  return blueprint;
}

#endif
