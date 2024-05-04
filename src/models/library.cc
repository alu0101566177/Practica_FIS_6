#include "library.h"

Library Library::FromJson(const crow::json::rvalue& json) {
  Library library;
  library.id = -1;
  library.name = json["name"].s();
  library.library_url = json["library_url"].s();
  return library;
}

crow::json::wvalue Library::ToJson() const {
  crow::json::wvalue json;
  json["id"] = id;
  json["name"] = name;
  json["library_url"] = library_url;
  return json;
}
