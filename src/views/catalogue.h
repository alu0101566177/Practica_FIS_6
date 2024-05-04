#ifndef VIEW_CATALOGUE_H_
#define VIEW_CATALOGUE_H_

#include "../../lib/crow_all.h"
#include "../models/book.h"
#include "../utils/serialize_models.h"

#include <vector>

class Catalogue {
  public:
    Catalogue() : page_{crow::mustache::load("catalogue.html")} {}

    crow::response Render(const std::vector<Book>& books) const {
      crow::mustache::context ctx;
      ctx["books"] = SerializeModels(books);
      return crow::response{page_.render_string(ctx)};
    }

  private:
    crow::mustache::template_t page_;
};

#endif
