#include "book.h"

Book Book::FromJson(const crow::json::rvalue& json) {
  Book book;
  book.id = -1;
  book.title = json["title"].s();
  book.author = json["author"].s();
  book.description = json["description"].s();
  book.image_url = json["image_url"].s();
  book.stock = json["stock"].i();
  if (json["library_id"].t() == crow::json::type::Number)
    book.library_id = json["library_id"].i();
  else
    book.library_id = std::nullopt;
  return book;
}

crow::json::wvalue Book::ToJson() const {
  crow::json::wvalue json;
  json["id"] = id;
  json["title"] = title;
  json["author"] = author;
  json["description"] = description;
  json["image_url"] = image_url;
  json["stock"] = stock;
  if (library_id.has_value())
    json["library_id"] = library_id.value();
  else
    json["library_id"] = nullptr;
  return json;
}
