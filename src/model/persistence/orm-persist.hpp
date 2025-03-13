#ifndef OrmPersist_hpp
#define OrmPersist_hpp

#include <memory>

#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>

#include "model/orm/database.hxx"
#include "model/entities/model.hpp"

class OrmPersist
{
    public:
    OrmPersist(std::shared_ptr<odb::core::database> database);

    //Languages
    shared_ptr<mokla::model::Language> GetLanguageById(long long id);
    vector<shared_ptr<mokla::model::Language>> GetAllActiveLanguages();

    /*
    //Problem
    mokla::model::Problem GetProblemById(long long id);

    //User
    mokla::model::User GetUserByUserName(string username);
    */

    private:
    template <typename T>
    void runner()
    {

    }
    std::shared_ptr<odb::core::database> database_;
};
#endif