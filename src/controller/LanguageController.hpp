#ifndef LanguageController_hpp
#define LanguageController_hpp

#include <iostream>
#include <memory>

#include <oatpp/web/server/api/ApiController.hpp>
#include <oatpp/macro/codegen.hpp>
#include <oatpp/macro/component.hpp>
#include <oatpp/Types.hpp>
#include <odb/database.hxx>

#include "dto/dto.hpp"
#include "model/entities/model.hpp"
#include "model/orm/model-odb.hxx"
#include "model/persistence/orm-persist.hpp" 

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

    //oatpp::Vector<oatpp::Object<LanguageDto>> result;
    auto result = oatpp::Vector<oatpp::Object<LanguageDto>>::createShared();
    //oatpp::Vector<LanguageDto> result{};   

    //vector<LanguageDto> result{};   

    auto languages = ormPersist_->GetAllActiveLanguages();
    for(auto lang : languages)
    {
      auto dto = LanguageDto::createShared();
      dto->id = lang->id();
      dto->description = lang->name();
      result->push_back(dto);
    }   
    return createDtoResponse(Status::CODE_200, result);
  }
  
  ENDPOINT("GET", "language/{languageId}", getLanguageById,
    PATH(Int32, languageId))
  {
    auto lang = ormPersist_->GetLanguageById(static_cast<long long>(languageId));
    auto dto = LanguageDto::createShared();
    dto->id = lang->id();
    dto->description = lang->name();

    return createDtoResponse(Status::CODE_200, dto );
  }

  private:
  OATPP_COMPONENT(std::shared_ptr<odb::core::database>, database_);
  OATPP_COMPONENT(std::shared_ptr<OrmPersist>, ormPersist_);
  
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* LanguageController_hpp */