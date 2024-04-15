#include "movie.h"

Movie Movie::FromJson(const crow::json::rvalue& json) {
  Movie movie;
  movie.id = -1; 
  movie.title = json["title"].s();
  movie.director = json["director"].s();
  movie.description = json["description"].s();
  movie.image_url = json["image_url"].s();
  movie.rating = json["rating"].d();
  movie.stock = json["stock"].i();
  if (json.has("genre")) {
      for (const auto& genre : json["genre"]) {
          movie.genre.push_back(genre.s());
      }
  }
  if (json.has("library_id")) {
      if (json["library_id"].t() == crow::json::type::Number)
          movie.library_id = json["library_id"].i();
      else
          movie.library_id = std::nullopt;
  } else {
      movie.library_id = std::nullopt;
  }
  return movie;
}

crow::json::wvalue Movie::ToJson() const {
  crow::json::wvalue json;
  json["id"] = id;
  json["title"] = title;
  json["director"] = director;
  json["description"] = description;
  json["image_url"] = image_url;
  json["rating"] = rating;
  json["stock"] = stock;
  if (!genre.empty()) {
    for (const auto& g : genre) {
      json["genre"].push_back(g);
    }
  }
  if (library_id.has_value())
    json["library_id"] = *library_id;
  return json;
}