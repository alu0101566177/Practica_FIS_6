#ifndef VIEW_PROFILE_H_
#define VIEW_PROFILE_H_

#include "../../lib/crow_all.h"
#include "../models/user.h"

class Profile {
  public:
    Profile() : page_{crow::mustache::load("profile.html")} {}

    crow::response Render(const User& user) const {
      return crow::response{page_.render_string(user.ToJson())};
    }

  private:
    crow::mustache::template_t page_;
};

#endif
