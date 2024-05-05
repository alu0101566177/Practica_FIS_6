#ifndef CONTROLLERS_RESERVATION_H_
#define CONTROLLERS_RESERVATION_H_

#include "auth_controller.h"
#include "../models/reservation.h"
#include "../db/database.h"
#include <vector>
#include <ctime>

class ReservationController {
  public:
    ReservationController(Storage& storage) : storage_{storage} {}

    bool MakeReservation(const int book_id, const int user_id) {
      auto filter{where(c(&Reservation::user_id) == user_id and c(&Reservation::book_id) == book_id)};
      auto matches{storage_.select(columns(&Reservation::expire_date), filter)};
      time_t now{std::time(0)};
      if (matches.size() != 0) {
        time_t expire_time{get<0>(matches[0])};
        if (now < expire_time)
          return false;
      }

      Reservation reservation{book_id, user_id};
      storage_.insert(reservation);
      return true;
    }

    std::vector<Reservation> GetReservations(const int user_id) {
      return storage_.get_all<Reservation>(where(c(&Reservation::user_id) == user_id));
    }    

  private:
    Storage& storage_;
};

#endif
