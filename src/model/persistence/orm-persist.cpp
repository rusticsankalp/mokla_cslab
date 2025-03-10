
#include "orm-persist.hpp" 

OrmPersist::OrmPersist(std::shared_ptr<odb::core::database> database) : 
  database_{database}
{ }
