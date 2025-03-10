#ifndef LanguageController_hpp
#define LanguageController_hpp

#include <iostream>
#include <memory>

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/macro/codegen.hpp>
#include <oatpp/macro/component.hpp>
#include <odb/database.hxx>

#include "dto/dto.hpp"
#include "model/entities/model.hpp"
#include "model/orm/model-odb.hxx"

using namespace std;
using namespace odb::core;
using namespace mokla::model;

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class LanguageController : public oatpp::web::server::api::ApiController {
public:
  /**
   * Constructor with object mapper.
   * @param apiContentMappers - mappers used to serialize/deserialize DTOs.
   */
  LanguageController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
    : oatpp::web::server::api::ApiController(apiContentMappers)
  {}
public:
  
  ENDPOINT("GET", "languages", getLanguages) {
    auto dto = LanguageDto::createShared();
    dto->id = 2;
    
    return createDtoResponse(Status::CODE_200, dto);
  }
  
  ENDPOINT("GET", "language/{languageId}", getLanguageById,
    PATH(Int32, languageId))
  {
    
    auto dto = LanguageDto::createShared();
    //long long langId = languageId.cast<long long>();
    long long langId = static_cast<long long>(languageId);
    try
    {
      transaction t (database_ ->begin());
     //lang = make_unique<Language>(database_->load<Language>(languageId));
     unique_ptr<Language> lang(database_->load<Language>(langId));

     t.commit();
     dto->id = languageId;
     dto->description = lang->name();
    }
    catch (const odb::exception& e)
    {
      cerr << e.what () << endl;
      return createDtoResponse(Status::CODE_410,dto );
    }
    return createDtoResponse(Status::CODE_200, dto );
  }

  private:
  OATPP_COMPONENT(std::shared_ptr<odb::core::database>, database_);
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* LanguageController_hpp */