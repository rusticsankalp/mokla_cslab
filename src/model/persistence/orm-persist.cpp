#include <odb/transaction.hxx>
#include <odb/database.hxx>

#include "model.hpp"
#include "model-odb.hxx"

#include "orm-persist.hpp" 


using namespace std;
using namespace odb::core;
using namespace mokla::model;

OrmPersist::OrmPersist(std::shared_ptr<odb::core::database> database) : 
  database_{database} {}

shared_ptr<mokla::model::Language> OrmPersist::GetLanguageById(long long id)
{

  shared_ptr<Language> language{nullptr};
  try
  {
    transaction t(database_->begin());

    shared_ptr<Language> lang(database_->load<Language>(id));
    Language language(lang);    

    t.commit();
  }
  catch (const odb::exception& e)
  {
    //:Do something useful here, e.g. logging
  }

  return language;
}

vector<Language> OrmPersist::GetAllActiveLanguages()
{
    return vector<Language> {};
}
