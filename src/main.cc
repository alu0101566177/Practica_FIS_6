#include "../lib/crow_all.h"
#include "controllers/user_controller.h"
#include "db/database.h"
#include "utils/serialize_models.h"

// Sample main
int main() {
  crow::SimpleApp app;
  Storage storage{GetDatabase()};

  CROW_ROUTE(app, "/")([]() {
    auto page{crow::mustache::load("index.html")};
    return page.render();
  });

  CROW_ROUTE(app, "/api/users")([&storage]() {
    UserController controller{storage};
    return SerializeModels(controller.GetAll());
  });

  CROW_ROUTE(app, "/api/create-user")
    .methods(crow::HTTPMethod::POST)
  ([&storage](const crow::request& req) {
    auto body_json{crow::json::load(req.body)};
    if (!body_json)
      return crow::response{crow::status::BAD_REQUEST};

    UserController controller{storage};
    int id{controller.Create(User::FromJson(body_json))};
    if (id == -1)
      return crow::response{crow::status::BAD_REQUEST};

    crow::json::wvalue response_body{{"id", id}};
    return crow::response{crow::status::CREATED, response_body};
  });

  app.port(8080).run();
}
