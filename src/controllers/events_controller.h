#ifndef EVENTS_CONTROLLER_H_
#define EVENTS_CONTROLLER_H_

#include "../db/database.h"
#include "../models/event.h"
#include "crud_controller.h"

typedef CRUDController<Event> EventsController;

#endif
