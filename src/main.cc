#include "../lib/crow_all.h"
#include "db/database.h"

// Sample main
int main() {
  crow::SimpleApp app;
  Storage storage{GetDatabase()};

  CROW_ROUTE(app, "/")([]() {
    auto page{crow::mustache::load("index.html")};
    return page.render();
  });

  CROW_ROUTE(app, "/api/create-user")
    .methods(crow::HTTPMethod::POST)
  ([](const crow::request& req) {
    auto body_json{crow::json::load(req.body)};
    // Rest of the code
  });

  app.port(8080).multithreaded().run();
}

// inline void AddUser(const UserController& controller) {
//   std::string name, email, password;
//   std::cout << "Insert the name: ";
//   std::cin >> name;
//
//   std::cout << "Insert email: ";
//   std::cin >> email;
//
//   std::cout << "Insert password: ";
//   std::cin >> password;
//
//   std::cout << "Created user uid = " << controller.CreateUser(name, email, password) << '\n';
// }
//
// inline void VerifyUser(const UserController& controller) {
//   std::string email, password;
//   std::cout << "Insert email: ";
//   std::cin >> email;
//   std::cout << "Insert password: ";
//   std::cin >> password;
//   std::cout << (controller.GetUser(email, password) ? "Usuario valido\n" : "Credenciales invalidas\n");
// }
//
// inline void PrintUsers(Storage& storage) {
//   auto users{storage.get_all<User>()};
//   for (auto& user : users)
//     std::cout << storage.dump(user) << '\n';
// }
//
// int main() {
//   while (true) {
//     std::cout << "Create user (1)\nVerify user (2)\nPrint users (3)\nSelect option: ";
//     Storage storage{GetDatabase()};
//     UserController controller{storage};
//     int option;
//     std::cin >> option;
//     switch (option) {
//       case 0:
//         return 0;
//       case 1:
//         AddUser(controller);
//         break;
//       case 2:
//         VerifyUser(controller);
//         break;
//       case 3:
//         PrintUsers(storage);
//         break;
//       default:
//         std::cout << "Not valid\n";
//         break;
//     }
//   }
//   return 0;
// }
