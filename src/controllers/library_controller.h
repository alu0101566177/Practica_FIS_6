#ifndef LIBRARY_CONTROLLERS_H_
#define LIBRARY_CONTROLLERS_H_

#include "../db/database.h"
#include "../models/library.h"
#include "crud_controller.h"

typedef CRUDController<Library> LibraryController;

#endif
