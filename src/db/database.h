#ifndef DATABASE_H_
#define DATABASE_H_

#include "../../lib/sqlite_orm.h"
#include "../models/user.h"
#include "../models/book.h"
#include "../models/event.h"
#include "../models/library.h"
#include <string>
#include <optional>

using namespace sqlite_orm;
using namespace sqlite_orm::internal;

typedef storage_t<
  table_t<User, false,
    column_t<int User::*, empty_setter, primary_key_with_autoincrement<primary_key_t<>>>,
    column_t<std::string User::*, empty_setter>,
    column_t<std::string User::*, empty_setter, unique_t<>>,
    column_t<std::string User::*, empty_setter>
  >,
  table_t<Book, false,
    column_t<int Book::*, empty_setter, primary_key_with_autoincrement<primary_key_t<>>>,
    column_t<std::string Book::*, empty_setter>,
    column_t<std::string Book::*, empty_setter>,
    column_t<std::string Book::*, empty_setter>,
    column_t<std::optional<int> Book::*, empty_setter>,
    column_t<int Book::*, empty_setter>
  >,
  table_t<Library, false,
    column_t<int Library::*, empty_setter, primary_key_with_autoincrement<primary_key_t<>>>,
    column_t<int Library::*, empty_setter>,
    column_t<std::string Library::*, empty_setter>,
    column_t<std::string Library::*, empty_setter>
  >,
  table_t<Event, false,
    column_t<int Event::*, empty_setter, primary_key_with_autoincrement<primary_key_t<>>>,
    column_t<int Event::*, empty_setter>,
    column_t<std::string Event::*, empty_setter>,
    column_t<std::string Event::*, empty_setter>,
    column_t<std::string Event::*, empty_setter>,
    column_t<std::string Event::*, empty_setter>
  >
> Storage;

Storage GetDatabase();

#endif
