#ifndef VIEW_ADMIN_H_
#define VIEW_ADMIN_H_

#include "../../lib/crow_all.h"
#include "../models/book.h"
#include "../utils/serialize_models.h"

class Admin {
  public:
    Admin() : page_{crow::mustache::load("admin.html")} {}

    crow::response Render(const std::string& token) const {
      crow::mustache::context ctx;
      ctx["token"] = token;
      return crow::response{page_.render_string(ctx)};
    }

  private:
    crow::mustache::template_t page_;
};

#endif
