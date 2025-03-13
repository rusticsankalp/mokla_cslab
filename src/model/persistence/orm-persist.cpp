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
    language = lang;   

    t.commit();
  }
  catch (const odb::exception& e)
  {
    //:Do something useful here, e.g. logging
  }

  return language;
}

vector<shared_ptr<mokla::model::Language>> OrmPersist::GetAllActiveLanguages()
{
    vector<shared_ptr<mokla::model::Language> >  languages{};
    try 
    {
      transaction t(database_->begin());

      using language_query = odb::query<Language>;

      auto rows = database_->query<Language>(language_query::is_archived == false);
      for(auto l: rows)
      {
        languages.push_back(make_shared<Language>(l));
      }
      t.commit();
    }
    catch (const odb::exception& e)
    {
      //:Do something useful here, e.g. logging
    }
    return languages;
}
