#ifndef EVENTS_CONTROLLER_H_
#define EVENTS_CONTROLLER_H_

#include "../db/database.h"
#include "../models/event.h"
#include "crud_controller.h"

class EventsController : public CRUDController<Event> {
  public:
    EventsController(Storage& storage) : CRUDController<Event>{storage} {}
};

#endif
