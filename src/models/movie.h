#define MOVIE_H

#include <string>
#include <vector>
#include <optional>
#include "../../lib/crow_all.h"

class Movie {
public:
  int id;
  std::string title;
  std::string director;
  std::string description;
  std::string image_url;
  double rating;
  int stock;
  std::vector<std::string> genre;
  std::optional<int> library_id;

  static Movie FromJson(const crow::json::rvalue& json);
  crow::json::wvalue ToJson() const;
};


#endif // MOVIE_H
