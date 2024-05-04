#ifndef CRUD_CONTROLLER_H_
#define CRUD_CONTROLLER_H_

#include "../db/database.h"
#include <optional>
#include <vector>

template <class Model>
class CRUDController {
  public:
    CRUDController(Storage& storage) : storage_{storage} {}

    virtual std::vector<Model> GetAll() const {
      return storage_.get_all<Model>();
    }

    virtual std::optional<Model> GetById(const int id) const {
      try {
        return storage_.get<Model>(id);
      } catch (const std::system_error& err) {
        return std::nullopt;
      }
    }

    virtual int Create(const Model& model) const {
      try {
        return storage_.insert(model);
      } catch (const std::system_error& err) {
        return -1;  
      }
    }

    virtual bool Delete(const int id) const {
      try {
        storage_.remove<Model>(id);
        return true;
      } catch (const std::system_error& err) {
        return false;
      }
    }

  protected:
    Storage& storage_;
};

#endif
