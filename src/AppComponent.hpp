#ifndef AppComponent_hpp
#define AppComponent_hpp

#include <memory>
#include <fstream>

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/mime/ContentMappers.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/json/ObjectMapper.hpp"
#include "oatpp/macro/component.hpp"
#include "oatpp/network/Server.hpp"
#include "oatpp/base/Log.hpp"

#include <nlohmann/json.hpp>

#include <odb/database.hxx>
#include <odb/session.hxx>
#include <odb/transaction.hxx>

#include "model/orm/database.hxx" // create_database

class AppConfig
{
  public:
   class Database
   {
    public:
      NLOHMANN_DEFINE_TYPE_INTRUSIVE(AppConfig::Database, username, password,name,host)
      string username;
      string password;
      string name;
      string host;
   };
   
   class Network 
   {
    public:
      NLOHMANN_DEFINE_TYPE_INTRUSIVE(AppConfig::Network, address, port)
      string address;
      short unsigned int port;
   };
   
   NLOHMANN_DEFINE_TYPE_INTRUSIVE(AppConfig, database, network)
   AppConfig::Database database;
   AppConfig::Network network;
  
};

/**
 *  Class which creates and holds Application components and registers components in oatpp::base::Environment
 *  Order of components initialization is from top to bottom
 */
class AppComponent {
  private :
  string configFilePath_{};
public:

  AppComponent(){}
  AppComponent(string configFilePath) : configFilePath_{configFilePath}
  {
  }

  public:
    /**
   *  Create ConnectionProvider component which listens on the port
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<AppConfig>, appConfig)([this]{

    //: this is too prone to failure. May be try catch or something else ?
    ifstream ifs(configFilePath_);
    std::stringstream buffer;
    buffer << ifs.rdbuf();

    string jsonString = buffer.str();
    return make_shared<AppConfig>(nlohmann::json::parse(jsonString));
   
  }());
  
  /**
   *  Create ConnectionProvider component which listens on the port
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([]() {
    OATPP_COMPONENT(std::shared_ptr<AppConfig>, appConfig);
    return oatpp::network::tcp::server::ConnectionProvider::createShared({appConfig->network.address, appConfig->network.port, oatpp::network::Address::IP_4});//static_cast<v_uint16>(network.port
  }());

  /**
   *  Create odb database provider
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<odb::core::database>, databaseConnector)([] {
   
    OATPP_COMPONENT(std::shared_ptr<AppConfig>, appConfig);
    auto dbConfig  = appConfig->database;
    std::shared_ptr<odb::core::database> database (new odb::pgsql::database (
      dbConfig.username, 
      dbConfig.password, 
      dbConfig.name,
      dbConfig.host
    ));

    return database;
  }());
  
  /**
   *  Create Router component
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
    return oatpp::web::server::HttpRouter::createShared();
  }());
  
  /**
   *  Create ConnectionHandler component which uses Router component to route requests
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([] {
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
    return oatpp::web::server::HttpConnectionHandler::createShared(router);
  }());
  
  /**
   *  Create ObjectMapper component to serialize/deserialize DTOs in Contoller's API
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers)([] {

    auto json = std::make_shared<oatpp::json::ObjectMapper>();
    json->serializerConfig().json.useBeautifier = true;

    auto mappers = std::make_shared<oatpp::web::mime::ContentMappers>();
    mappers->putMapper(json);

    return mappers;

  }());

};

#endif /* AppComponent_hpp */
