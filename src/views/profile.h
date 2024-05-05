#ifndef VIEW_PROFILE_H_
#define VIEW_PROFILE_H_

#include "../../lib/crow_all.h"
#include "../models/user.h"
#include "../models/reservation.h"
#include "../controllers/books_controller.h"

#include <ctime>
#include <vector>

class Profile {
  public:
    Profile() : page_{crow::mustache::load("profile.html")} {}

    crow::response Render(const User& user, const std::vector<Reservation>& reservations, BooksController& books) const {
      crow::mustache::context ctx;
      ctx["user"] = user.ToJson();
      ctx["reservations"] = SerializeReservations(reservations, books);
      return crow::response{page_.render_string(ctx)};
    }

  private:
    crow::json::wvalue SerializeReservations(const std::vector<Reservation>& reservations, BooksController& books) const {
      crow::json::wvalue::list reservations_list;
      for (const auto& reservation : reservations) {
        Book book{books.GetById(reservation.book_id).value()};
        reservations_list.push_back({
          {"name", book.title},
          {"expire_date", ctime(&reservation.expire_date)}
        });
      }
      return reservations_list;
    }

    crow::mustache::template_t page_;
};

#endif
