#ifndef VIEW_HOME_H_
#define VIEW_HOME_H_

#include "../../lib/crow_all.h"
#include "../models/book.h"
#include "../utils/serialize_models.h"

class Home {
  public:
    Home() : page_{crow::mustache::load("index.html")} {}

    crow::response Render(const std::vector<Book>& books) const {
      crow::mustache::context ctx;
      ctx["books"] = SerializeModels(books);
      return crow::response{page_.render_string(ctx)};
    }

  private:
    crow::mustache::template_t page_;
};

#endif
