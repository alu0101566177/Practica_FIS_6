#include "../lib/crow_all.h"

int main() {
  crow::SimpleApp app;

  CROW_ROUTE(app, "/")([](std::string name) {
    auto page{crow::mustache::load("index.html")};
    return page.render();
  });

  app.port(8080).multithreaded().run();
}
