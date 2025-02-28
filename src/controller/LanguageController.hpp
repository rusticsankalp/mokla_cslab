#ifndef LanguageController_hpp
#define LanguageController_hpp

#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"

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
   if(languageId == 2 )
   {
    dto->id = 2;
    dto->description = "g++ 14";
   }
   else if(languageId == 3){
    dto->id = 3;
    dto->description = "g++ 13";
   }
   else{
    return createDtoResponse(Status::CODE_410,dto );
   }
   return createDtoResponse(Status::CODE_200, dto );
}
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* LanguageController_hpp */