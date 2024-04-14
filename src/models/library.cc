#include "library.h"

Library Library::FromJson(const crow::json::rvalue& json) {
  Library library;
  library.id = -1;
  library.capacity = json["capacity"].i();
  library.name = json["name"].s();
  library.location = json["location"].s();
  return library;
}

crow::json::wvalue Library::ToJson() const {
  crow::json::wvalue json;
  json["id"] = id;
  json["capacity"] = capacity;
  json["name"] = name;
  json["location"] = location;
  return json;
}
