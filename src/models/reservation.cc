#include "reservation.h"
#include <ctime>
#include <string>

Reservation::Reservation(const int book, const int user) {
  id = -1;
  book_id = book;
  user_id = user;
  // Actual date
  time_t date{time(0) + 3600 * 24 * 15};
  expire_date = date;
}

Reservation Reservation::FromJson(const crow::json::rvalue& json) {
  int book = json["book_id"].i();
  int user = json["user_id"].i();
  return Reservation{book, user};
}

crow::json::wvalue Reservation::ToJson() const {
  crow::json::wvalue result;
  result["id"] = id;
  result["book_id"] = book_id;
  result["user_id"] = user_id;
  result["expire_date"] = std::string{ctime(&expire_date)};
  return result;
}
