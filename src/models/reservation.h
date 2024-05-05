#ifndef MODELS_RESERVATION_H_
#define MODELS_RESERVATION_H_

#include "../../lib/crow_all.h"
#include <string>

struct Reservation {
  int id;
  int book_id;
  int user_id;
  long expire_date;

  Reservation() = default;
  Reservation(const int, const int);
  static Reservation FromJson(const crow::json::rvalue&);
  crow::json::wvalue ToJson() const;
};

#endif
