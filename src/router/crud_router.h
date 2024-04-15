#ifndef CRUD_ROUTER_H_
#define CRUD_ROUTER_H_

#include "../../lib/crow_all.h"
#include "../controllers/crud_controller.h"
#include "../controllers/auth_controller.h"
#include "../utils/serialize_models.h"

template <class Model>
class CRUDRouter {
  public:
    CRUDRouter(AuthController& auth, CRUDController<Model>& controller) : auth_{auth}, controller_{controller} {}

    crow::response CreateRoute(const crow::request& req, const bool admin_required) const {
      if (admin_required && !AdminAuth(req))
        return crow::response{crow::status::UNAUTHORIZED};

      auto body_json{crow::json::load(req.body)};
      if (!body_json)
        return crow::response{crow::status::BAD_REQUEST};

      int id{controller_.Create(Model::FromJson(body_json))};
      if (id == -1)
        return crow::response{crow::status::CONFLICT};

      crow::json::wvalue response_body{{"id", id}};
      return crow::response{crow::status::CREATED, response_body};
    }

    crow::response GetAllRoute(const crow::request& req, const bool admin_required) const {
      if (admin_required && !AdminAuth(req))
        return crow::response{crow::status::UNAUTHORIZED};
      return crow::response{SerializeModels(controller_.GetAll())};
    }

    crow::response GetByIdRoute(const crow::request& req, const int id, const bool admin_required) const {
      if (admin_required && !AdminAuth(req))
        return crow::response{crow::status::UNAUTHORIZED};
      std::optional<Model> object{controller_.GetById(id)};
      if (!object.has_value())
        return crow::response{crow::status::NOT_FOUND};
      return crow::response{object->ToJson()};
    }

    crow::response DeleteRoute(const crow::request& req, const int id, const bool admin_required) const {
      if (admin_required && !AdminAuth(req))
        return crow::response{crow::status::UNAUTHORIZED};
      if (!controller_.Delete(id))
        return crow::response{crow::status::NOT_FOUND};
      return crow::response{crow::status::OK};
    }

  private:
    bool AdminAuth(const crow::request& req) const {
      std::string token{req.get_header_value("Authorization")};
      return token.length() != 0 && auth_.ValidAdminToken(token);
    }

    AuthController& auth_;
    CRUDController<Model>& controller_;
};

#endif
