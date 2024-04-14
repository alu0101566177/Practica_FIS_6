#include "user.h"

User User::FromJson(const crow::json::rvalue& json) {
  User user;
  user.id = -1;
  user.name = json["name"].s();
  user.email = json["email"].s();
  user.password = json["password"].s();
  return user;
}

crow::json::wvalue User::ToJson() const {
  crow::json::wvalue json;
  json["id"] = id;
  json["name"] = name;
  json["email"] = email;
  json["password"] = password;
  return json;
}
