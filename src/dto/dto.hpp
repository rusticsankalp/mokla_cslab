#ifndef DTO_hpp
#define DTO_hpp

#include "oatpp/macro/codegen.hpp"
#include "oatpp/Types.hpp"

#include "model.hpp"

using namespace std;
using namespace odb::core;
using namespace mokla::model;

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

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class ProblemDto : public oatpp::DTO {
  
  DTO_INIT(ProblemDto, DTO)
  
  DTO_FIELD(UInt32,id);
  DTO_FIELD(String, title);
  DTO_FIELD(String, difficulty);
  DTO_FIELD(String, problem_statement);
  DTO_FIELD(String, problem_statement_type);
    
};

#include OATPP_CODEGEN_END(DTO)

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class StarterProgramDto : public oatpp::DTO {
  
  DTO_INIT(StarterProgramDto, DTO)
  
  DTO_FIELD(UInt32, id);
  DTO_FIELD(UInt32, problemId);
  DTO_FIELD(String, language_code);
  DTO_FIELD(String, program);
};

#include OATPP_CODEGEN_END(DTO)

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class SubmissionDto : public oatpp::DTO {
  
  DTO_INIT(SubmissionDto, DTO)
  
  DTO_FIELD(UInt32,id);
  DTO_FIELD(UInt32, problemId);
  DTO_FIELD(String, language_code);
  DTO_FIELD(String, program);
};

#include OATPP_CODEGEN_END(DTO)

#endif /* DTOs_hpp */