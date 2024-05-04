#ifndef VIEW_BOOK_H_
#define VIEW_BOOK_H_

#include "../../lib/crow_all.h"
#include "../models/book.h"

class BookView {
  public:
    BookView() : page_{crow::mustache::load("book.html")} {}

    crow::response Render(const Book& book) const {
      return crow::response{page_.render_string(book.ToJson())};
    }

  private:
    crow::mustache::template_t page_;
};

#endif
