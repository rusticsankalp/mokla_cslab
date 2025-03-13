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

  return 
    DBExecutor([this,id]{
      return (shared_ptr<Language>)database_->load<Language>(id);
    });
 
}

vector<shared_ptr<mokla::model::Language>> OrmPersist::GetAllActiveLanguages()
{

    return 
    DBExecutor([this]{
      vector<shared_ptr<mokla::model::Language> >  languages{};
      using language_query = odb::query<Language>;
      auto rows = database_->query<Language>(language_query::is_archived == false);
      for(auto l: rows)
      {
        languages.push_back(make_shared<Language>(l));
      }
      return languages;
    });
}
