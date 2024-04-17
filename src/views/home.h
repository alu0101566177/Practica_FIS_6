#ifndef VIEW_HOME_H_
#define VIEW_HOME_H_

#include "../../lib/crow_all.h"
#include "../models/book.h"
#include "../models/user.h"
#include "../utils/serialize_models.h"
#include <optional>

class Home {
  public:
    Home() : page_{crow::mustache::load("index.html")} {}

    crow::response Render(const std::vector<Book>& books, const std::optional<User>& user) const {
      crow::mustache::context ctx;
      ctx["books"] = SerializeModels(books);
      if (user.has_value())
        ctx["name"] = user->name;
      return crow::response{page_.render_string(ctx)};
    }

  private:
    crow::mustache::template_t page_;
};

#endif
