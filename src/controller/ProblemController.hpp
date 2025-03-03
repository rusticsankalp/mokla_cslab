#ifndef ProblemController_hpp
#define ProblemController_hpp

#include "dto/DTOs.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/macro/codegen.hpp"
#include "oatpp/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen

/**
 * Sample Api Controller.
 */
class ProblemController : public oatpp::web::server::api::ApiController {
public:
  /**
   * Constructor with object mapper.
   * @param apiContentMappers - mappers used to serialize/deserialize DTOs.
   */
  ProblemController(OATPP_COMPONENT(std::shared_ptr<oatpp::web::mime::ContentMappers>, apiContentMappers))
    : oatpp::web::server::api::ApiController(apiContentMappers)
  {}
public:
  
  ENDPOINT("GET", "problems", getProblems) {
    auto dto = LanguageDto::createShared();
    dto->id = 2;
    
    return createDtoResponse(Status::CODE_200, dto);
  }
  
  ENDPOINT("GET", "problem/{problemId}", getProblemById,
    PATH(Uint32, problemId))
{
   return createDtoResponse(Status::CODE_410,dto );
}
  
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* ProblemController_hpp */