#ifndef DTOs_hpp
#define DTOs_hpp

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class LanguageDto : public oatpp::DTO {
  
  DTO_INIT(LanguageDto, DTO)
  
  DTO_FIELD(Int32, id);
  DTO_FIELD(String, description);
  
};

#include OATPP_CODEGEN_END(DTO)

#endif /* DTOs_hpp */