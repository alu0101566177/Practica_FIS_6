#include "database.h"
#include "../models/user.h"
#include "../models/book.h"
#include "../models/event.h"
#include "../models/library.h"

#include <sqlite3.h>

using namespace sqlite_orm;

Storage GetDatabase() {
  auto storage{make_storage("db.sqlite",
    make_table("users",
      make_column("id", &User::id, primary_key().autoincrement()),
      make_column("name", &User::name),
      make_column("email", &User::email, unique()),
      make_column("password", &User::password)
    ),
    make_table("books",
      make_column("id", &Book::id, primary_key().autoincrement()),
      make_column("title", &Book::title),
      make_column("author", &Book::author),
      make_column("description", &Book::description),
      make_column("image_url", &Book::image_url),
      make_column("libray_id", &Book::library_id),
      make_column("stock", &Book::stock)
    ),
    make_table("librarys",
      make_column("id", &Library::id, primary_key().autoincrement()),
      make_column("capacity", &Library::capacity),
      make_column("name", &Library::name),
      make_column("location", &Library::location)
    ),
    make_table("events",
      make_column("id", &Event::id, primary_key().autoincrement()),
      make_column("capacity", &Event::capacity),
      make_column("title", &Event::title),
      make_column("description", &Event::description),
      make_column("location", &Event::location),
      make_column("date", &Event::date)
    )
  )};
  storage.sync_schema();
  return storage;
}
