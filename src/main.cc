#include "../lib/crow_all.h"
#include "api.h"
#include "db/database.h"
#include "controllers/auth_controller.h"
#include "controllers/user_controller.h"
#include "controllers/books_controller.h"
#include "controllers/events_controller.h"
#include "controllers/library_controller.h"
#include "utils/serialize_models.h"

// Sample main
int main() {
  crow::App<crow::CORSHandler> app;
  auto& cors{app.get_middleware<crow::CORSHandler>()};
  cors.global()
    .headers("X-Custom-Header", "Upgrade-Insecure-Requests")
    .methods("POST"_method, "GET"_method, "DELETE"_method, "PUT"_method);

  Storage storage{GetDatabase()};

  AuthController auth{storage};
  UserController users{storage};
  BooksController books{storage};
  EventsController events{storage};
  LibraryController library{storage};

  // Main library web page
  CROW_ROUTE(app, "/")([]() {
    auto page{crow::mustache::load("index.html")};
    return page.render();
  });
  // Admin panel
  CROW_ROUTE(app, "/admin")([]() {
    auto page{crow::mustache::load("admin.html")};
    return page.render();
  });

  // API

  // Auth
  CROW_ROUTE(app, "/api/auth")
    .methods(crow::HTTPMethod::POST)
  ([&auth, &users](const crow::request& req) {
    auto body_json{crow::json::load(req.body)};
    if (!body_json)
      return crow::response{crow::status::BAD_REQUEST};

    std::string email{body_json["email"].s()}, password{body_json["password"].s()};
    int id{users.GetUserId(email, password)};
    if (id == -1)
      return crow::response{crow::status::FORBIDDEN};

    return crow::response{auth.CreateToken(id)};
  });

  // Get
  CROW_ROUTE(app, "/api/users")([&auth, &users](const crow::request& req) {
    std::string token{req.get_header_value("Authorization")};
    if (token.length() == 0 || !auth.ValidAdminToken(token))
      return crow::response{crow::status::UNAUTHORIZED};

    return crow::response{SerializeModels(users.GetAll())};
  });
  CROW_ROUTE(app, "/api/books")([&books]() {
    return crow::response{SerializeModels(books.GetAll())};
  });
  CROW_ROUTE(app, "/api/events")([&events]() {
    return crow::response{SerializeModels(events.GetAll())};
  });
  CROW_ROUTE(app, "/api/librarys")([&library]() {
    return crow::response{SerializeModels(library.GetAll())};
  });

  // Create
  CROW_ROUTE(app, "/api/user")
    .methods(crow::HTTPMethod::POST)
  ([&auth, &users](const crow::request& req) {
    return CreateRoute(req, auth, users);
  });
  CROW_ROUTE(app, "/api/book")
    .methods(crow::HTTPMethod::POST)
  ([&auth, &books](const crow::request& req) {
    return CreateRoute(req, auth, books);
  });
  CROW_ROUTE(app, "/api/event")
    .methods(crow::HTTPMethod::POST)
  ([&auth, &events](const crow::request& req) {
    return CreateRoute(req, auth, events);
  });
  CROW_ROUTE(app, "/api/library")
    .methods(crow::HTTPMethod::POST)
  ([&auth, &library](const crow::request& req) {
    return CreateRoute(req, auth, library);
  });

  app.port(8080).run();
}
