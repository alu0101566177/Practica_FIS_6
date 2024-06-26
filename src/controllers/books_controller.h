#ifndef BOOKS_CONTROLLER_H_
#define BOOKS_CONTROLLER_H_

#include "../db/database.h"
#include "../models/book.h"
#include "crud_controller.h"
#include <vector>

typedef CRUDController<Book> BooksController;

#endif
