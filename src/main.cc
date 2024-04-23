#include "../lib/crow_all.h"

#include "db/database.h"

#include "controllers/auth_controller.h"
#include "controllers/user_controller.h"
#include "controllers/books_controller.h"
#include "controllers/movie_controller.h"
#include "controllers/events_controller.h"
#include "controllers/library_controller.h"

#include "models/event.h"
#include "models/library.h"
#include "models/movie.h"

#include "router/crud_router.h"
#include "router/login_router.h"

#include "views/admin.h"
#include "views/home.h"
#include "views/login.h"

#include <optional>

// Sample main
int main() {
  crow::App<crow::CORSHandler, crow::CookieParser> app;

  auto& cors{app.get_middleware<crow::CORSHandler>()};
  cors.global()
    .headers("X-Custom-Header", "Upgrade-Insecure-Requests")
    .methods("POST"_method, "GET"_method, "DELETE"_method, "PUT"_method);

  Storage storage{GetDatabase()};

  AuthController auth{storage};
  UserController users{storage};
  BooksController books{storage};
  MovieController movies{storage};
  EventsController events{storage};
  LibraryController libraries{storage};

  CRUDRouter<User> user_router{auth, users, true};
  CRUDRouter<Book> book_router{auth, books};
  CRUDRouter<Movie> movie_router{auth, movies};
  CRUDRouter<Event> events_router{auth, events};
  CRUDRouter<Library> libraries_router{auth, libraries};

  crow::Blueprint auth_blueprint{CreateApiAuthBlueprint(auth, users)};
  crow::Blueprint user_blueprint{user_router.CreateBlueprint("api/user")};
  crow::Blueprint book_blueprint{book_router.CreateBlueprint("api/book")};
  crow::Blueprint movie_blueprint{movie_router.CreateBlueprint("api/movie")};
  crow::Blueprint events_blueprint{events_router.CreateBlueprint("api/event")};
  crow::Blueprint libraries_blueprint{libraries_router.CreateBlueprint("api/library")};

  app.register_blueprint(auth_blueprint);
  app.register_blueprint(user_blueprint);
  app.register_blueprint(book_blueprint);
  app.register_blueprint(movie_blueprint);
  app.register_blueprint(events_blueprint);
  app.register_blueprint(libraries_blueprint);

  // Main library web page
  CROW_ROUTE(app, "/")([&app, &auth, &books](const crow::request& req) {
    auto& ctx = app.get_context<crow::CookieParser>(req);
    auto token = ctx.get_cookie("auth");
    std::optional<User> user{std::nullopt};
    if (token.size() != 0)
      user = auth.GetUserByToken(token);
    return Home{}.Render(books.GetAll(), user);
  });

  // Admin panel
  CROW_ROUTE(app, "/admin")([&app, &auth](const crow::request& req, crow::response& res) {
    auto& ctx = app.get_context<crow::CookieParser>(req);
    auto token = ctx.get_cookie("auth");
    if (token.size() == 0 || !auth.ValidAdminToken(token))
      res.redirect("/admin-login");
    else
      res = Admin{}.Render(token);
    res.end();
  });

  // Login
  CROW_ROUTE(app, "/login")([&app](const crow::request& req) {
    return Login{}.Render("");
  });

  // Admin login
  CROW_ROUTE(app, "/admin-login")([&app](const crow::request& req) {
    return Login{}.Render("admin");
  });

  // Login POST
  CROW_ROUTE(app, "/login")
    .methods(crow::HTTPMethod::POST)
  ([&app, &users, &auth](const crow::request& req) {
    auto body_json{crow::json::load(req.body)};
    if (!body_json)
      return crow::response{crow::status::BAD_REQUEST};

    std::string email{body_json["email"].s()}, password{body_json["password"].s()};
    int id{users.GetUserId(email, password)};
    if (id == -1)
      return crow::response{crow::status::FORBIDDEN};

    auto token = auth.CreateToken(id);
    auto& ctx = app.get_context<crow::CookieParser>(req);
    ctx.set_cookie("auth", token);
    return crow::response{crow::status::OK};
  });

  // Login delete
  CROW_ROUTE(app, "/login")
    .methods(crow::HTTPMethod::DELETE)
  ([&app](const crow::request& req) {
    auto& ctx = app.get_context<crow::CookieParser>(req);
    ctx.set_cookie("auth", "");
    return crow::response{crow::status::OK};
  });

  app.port(8080).run();
}
