#ifndef MOVIE_CONTROLLERS_H_
#define MOVIE_CONTROLLERS_H_

#include "../db/database.h"
#include "../models/movie.h"
#include "crud_controller.h"

typedef CRUDController<Movie> MovieController;

#endif
