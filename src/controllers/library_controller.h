#ifndef LIBRARY_CONTROLLERS_H_
#define LIBRARY_CONTROLLERS_H_

#include "../db/database.h"
#include "../models/library.h"
#include "crud_controller.h"

class LibraryController : public CRUDController<Library> {
  public:
    LibraryController(Storage& storage) : CRUDController<Library>{storage} {}
};

#endif
