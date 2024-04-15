#include "../lib/crow_all.h"
#include "db/database.h"
#include "controllers/auth_controller.h"
#include "controllers/user_controller.h"
#include "controllers/books_controller.h"
#include "router/crud_router.h"

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

  CRUDRouter<User> user_router{auth, users};
  CRUDRouter<Book> book_router{auth, books};

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
  CROW_ROUTE(app, "/api/users")([&user_router](const crow::request& req) {
    return user_router.GetAllRoute(req, true);
  });
  CROW_ROUTE(app, "/api/books")([&book_router](const crow::request& req) {
    return book_router.GetAllRoute(req, false);
  });

  // GetById
  CROW_ROUTE(app, "/api/user/<int>")([&user_router](const crow::request& req, const int id) {
    return user_router.GetByIdRoute(req, id, true);
  });
  CROW_ROUTE(app, "/api/book/<int>")([&book_router](const crow::request& req, const int id) {
    return book_router.GetByIdRoute(req, id, false);
  });

  // Create
  CROW_ROUTE(app, "/api/user")
    .methods(crow::HTTPMethod::POST)
  ([&user_router](const crow::request& req) {
    return user_router.CreateRoute(req, true);
  });
  CROW_ROUTE(app, "/api/book")
    .methods(crow::HTTPMethod::POST)
  ([&book_router](const crow::request& req) {
    return book_router.CreateRoute(req, true);
  });

  // Delete
  CROW_ROUTE(app, "/api/user/<int>")
    .methods(crow::HTTPMethod::DELETE)
  ([&user_router](const crow::request& req, const int id) {
    return user_router.DeleteRoute(req, id, true);
  });
  CROW_ROUTE(app, "/api/book/<int>")
    .methods(crow::HTTPMethod::DELETE)
  ([&book_router](const crow::request& req, const int id) {
    return book_router.DeleteRoute(req, id, true);
  });

  app.port(8080).run();
}
