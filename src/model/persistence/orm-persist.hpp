#include <memory>

#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>

#include "model/orm/database.hxx"

class OrmPersist
{
    public:
    OrmPersist(std::shared_ptr<odb::core::database> database);

    private:
    std::shared_ptr<odb::core::database> database_;
};