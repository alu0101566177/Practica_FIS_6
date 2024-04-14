#ifndef SERIALIZE_MODELS_H_
#define SERIALIZE_MODELS_H_

#include "../../lib/crow_all.h"
#include <vector>

template <class Model>
crow::json::wvalue SerializeModels(const std::vector<Model>& models) {
  crow::json::wvalue::list result;
  for (const Model& model : models)
    result.push_back(model.ToJson());
  return result;
}

#endif
