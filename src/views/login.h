#ifndef LOGIN_H_
#define LOGIN_H_

#include "../../lib/crow_all.h"
#include <string>

class Login {
  public:
    Login() : page_{crow::mustache::load("login.html")} {}

    crow::response Render(const std::string& redirect_url) const {
      crow::mustache::context ctx;
      ctx["redirect_url"] = redirect_url;
      return crow::response{page_.render_string(ctx)};
    }

  private:
    crow::mustache::template_t page_;
};

#endif
