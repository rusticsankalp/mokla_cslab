//:for database:hxx

#include "controller/LanguageController.hpp"
#include "AppComponent.hpp"

#include "oatpp/network/Server.hpp"

#include "model.hpp"
#include "model-odb.hxx"
#include "database.hxx"
#include <nlohmann/json.hpp>

#include <iostream>
using namespace odb::core;
using namespace mokla::model;

void run() {

  /* Register Components in scope of run() method */
  AppComponent components;

  /* Get router component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);

  /* Create MyController and add all of its endpoints to router */
  router->addController(std::make_shared<LanguageController>());

  /* Get connection handler component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);

  /* Get connection provider component */
  OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

  /* Create server which takes provided TCP connections and passes them to HTTP connection handler */
  oatpp::network::Server server(connectionProvider, connectionHandler);

  /* Print info about server port */
  OATPP_LOGi("MyApp", "Server running on port {}", connectionProvider->getProperty("port").toString());

  /* Run server */
  server.run();
  
}
class MoklaSerializer
{
    public:
    static void print (Language& lang)
    {
        cout << endl << "language :: id,name,code:" 
        << lang.id() << "," 
        << lang.name()<<','
        << lang.language_code();
    }
};

int dbTest(int argc,char* argv[])
{
  try
  {
    unique_ptr<database> db (create_database (argc, argv));
    {
        transaction t (db->begin());

        Language cppLanguage("g++ default", false,ELanguage_code::cpp);
        Language cLanguage = Language{"gcc default", false,ELanguage_code::c};

        nlohmann::json cppJson = cppLanguage;
        cout<<cppJson.dump();

        //This works ( may not pring in debug_console)
        std::string t0 = cppJson.dump();
        cout <<t0;

        auto cppLangId = db->persist(cppLanguage);
        auto cLangId = db->persist(cLanguage);

        t.commit();
    }
    /*

    {
        using query = odb::query<Language>;
        using result = odb::result<Language>;

        transaction t (db->begin());

        result r (db->query<Language> (query::language_code == ELanguage_code::cpp));

        for (result::iterator i (r.begin ()); i != r.end (); ++i)
        {
            MoklaSerializer::print(*i);
        }

        t.commit ();
    }
        */
    
  }
  catch (const odb::exception& e)
  {
    cerr <<"Threw exception" << e.what () << endl;
    return 1;
  }

  return 0;
}


/**
 *  main
 */
int main(int argc, char * argv[]) {

  
  oatpp::Environment::init();

  dbTest(argc,argv);

  run();
  
  /* Print how much objects were created during app running, and what have left-probably leaked */
  /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::Environment::getObjectsCreated() << "\n\n";
  
  oatpp::Environment::destroy();
  
  return 0;
}