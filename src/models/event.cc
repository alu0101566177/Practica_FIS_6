#include "event.h"

Event Event::FromJson(const crow::json::rvalue& json) {
  Event event;
  event.id = -1;
  event.capacity = json["capacity"].i();
  event.description = json["description"].s();
  event.location = json["location"].s();
  event.date = json["date"].s();
  return event;
}

crow::json::wvalue Event::ToJson() const {
  crow::json::wvalue json;
  json["id"] = id;
  json["capacity"] = capacity;
  json["title"] = title;
  json["description"] = description;
  json["location"] = location;
  json["date"] = date;
  return json;
}
