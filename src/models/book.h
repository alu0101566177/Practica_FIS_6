#ifndef MODELS_BOOK_H_
#define MODELS_BOOK_H_

#include <optional>
#include <string>

struct Book {
  int id;
  std::string title;
  std::string description;
  std::string image_url;
  std::optional<int> library_id;
  int stock; // -1 if is an online book
};

#endif
