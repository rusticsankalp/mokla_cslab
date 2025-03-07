// copyright : not copyrighted - public domain

#ifndef MODELS_HPP
#define MODELS_HPP

#include <vector>
#include <string>
#include <memory> 

#include <odb/core.hxx>
#include <nlohmann/json.hpp>

using namespace std;

namespace mokla::model
{
  class Language;
  class User;
  class Problem;
  class StarterProgram;
  class Submission;

  enum ELanguage_code
  {
      c,
      cpp,
      java
  };

  enum EDifficulty
  {
      easy,
      medium,
      hard
  };

  enum EProblemStatementType
  {
      markdown
  };

  enum ETestsType
  {
      StandardIO
  };

  #pragma db object
  class Language
  {
    public:
    Language(const string name, const bool is_archived, const ELanguage_code language_code ) :
        name_{name}, is_archived_{is_archived},language_code_{language_code} 
        {}

      Language(){}

        const long long  id(){return id_;}
        
        const string name() {return name_;}
        void name(string name){ name_ = name;}

        const bool is_Archived(){ return is_archived_;}
        void is_Archived(bool is_archived){ is_archived_ = is_archived;}

        const ELanguage_code language_code(){ return language_code_;}
        void language_code(ELanguage_code language_code){language_code_ = language_code;}
        
      NLOHMANN_DEFINE_TYPE_INTRUSIVE(Language, id_, name_,is_archived_,language_code_)

    private:
      friend class odb::access;
      

      #pragma db id auto
      long long id_{};
      string name_{};
      bool is_archived_{};
      ELanguage_code language_code_{}; 
  };

  #pragma db object
  class Problem
  {
    public: 
    Problem(string title, EDifficulty ,string problem_statement,EProblemStatementType problem_statement_type,ETestsType tests_type,
      string tests_version, string compact_tests, string complete_tests)
      : title_{title}, problem_statement_{problem_statement}, problem_statement_type_{problem_statement_type}, tests_type_{tests_type},
        tests_version_{tests_version},compact_tests_{compact_tests}, complete_tests_{complete_tests} {}

    Problem() {}      
      
    const long long id(){return id_;}

    const string title() {return title_;}
    void title(string title){ title_ = title;}

    const EDifficulty difficulty(){return difficulty_;}
    void difficulty(EDifficulty difficulty){difficulty_ = difficulty;}

    const string problem_statement(){return problem_statement_;}
    void problem_statement(string problem_statement){problem_statement_ = problem_statement;}

    const EProblemStatementType problem_statement_type() {return problem_statement_type_;}
    void problem_statement_type(EProblemStatementType problem_statement_type) { problem_statement_type_ = problem_statement_type;}

    const ETestsType tests_type(){return tests_type_;}
    void tests_type(ETestsType tests_type){ tests_type_ = tests_type;}

    const string tests_version() {return tests_version_;}
    void tests_version(string tests_version){ tests_version_ = tests_version;}

    const string compact_tests() {return compact_tests_;}
    void compact_tests(string compact_tests){ compact_tests_ = compact_tests;}

    const string complete_tests() {return complete_tests_;}
    void complete_tests(string complete_tests){ complete_tests_ = complete_tests;}
    
    private:
      friend class odb::access;

      #pragma db id auto
      long long id_{};
      string title_{};
      EDifficulty difficulty_{}; 
      string problem_statement_{};
      EProblemStatementType problem_statement_type_{}; 
      ETestsType tests_type_{}; 
      string tests_version_{}; //: research max size on string , or consider enum 
      string compact_tests_{}; //: how to convert to mediumText ?
      string complete_tests_{}; //: how to convert to mediumText ?

      //:Tests could be different class
  };


  //:separate user auth table 
  //:seprate user roles
  #pragma db object
  class User
  {
    public:
      User(string username,string first_name,string last_name,string email, string phone, string grade, string school) : 
        username_{username},first_name_{first_name},last_name_{last_name},email_{email}, phone_{phone}, grade_{grade}, school_{school} 
        {}
      User(){}

      const long long id(){return id_;}

      const string username() {return username_;}
      void username(string username){ username_ = username;}

      const string first_name() {return first_name_;}
      void first_name(string first_name){ first_name_ = first_name;}

      const string tlast_nameitle() {return last_name_;}
      void last_name(string last_name){ last_name_ = last_name;}

      const string email() {return email_;}
      void email(string email){ email_ = email;}

      const string phone() {return phone_;}
      void phone(string phone){ phone_ = phone;}

      const string grade() {return grade_;}
      void grade(string grade){ grade_ = grade;}

      const string school() {return school_;}
      void title(string school){ school_ = school;}

    private:
      friend class odb::access;

      #pragma db id auto
      long long id_;
      string username_;
      string first_name_;
      string last_name_;
      string email_;
      string phone_;
      //date_created
      string grade_;
      string school_;           
  };

  #pragma db object
  class StarterProgram
  {
    public:
    StarterProgram(ELanguage_code language_code,string program, shared_ptr<Problem> problem) :
      language_code_{language_code}, program_{program}, problem_{problem} 
    {}
    StarterProgram(){}

    ELanguage_code language_code(){return language_code_;}
    void language_code(ELanguage_code language_code){language_code_ = language_code;}

    string program() {return program_;}
    void program(string program){program_ = program;}

    shared_ptr<Problem> problem() {return problem_;}
    void problem(shared_ptr<Problem> problem){problem_ = problem;}

    private:
      friend class odb::access;

      #pragma db id auto
      long long id_;
      ELanguage_code language_code_; //: consider enum
      string program_;

      #pragma db not_null
      shared_ptr<Problem> problem_;
  };

  #pragma db object
  class Submission
  {
    public:
      Submission(string source_code,shared_ptr<Language> language, bool is_compact_run, ETestsType tests_type,string tests_version, 
          shared_ptr<User> user, shared_ptr<Problem> problem ):
          source_code_(source_code), language_{language}, is_compact_run_{is_compact_run}, tests_type_{tests_type}, tests_version_{tests_version},
          user_{user},problem_{problem}
          {}

      Submission(){}

      string source_code(){return source_code_;}
      void source_code(string source_code){source_code_ = source_code;}

      shared_ptr<Language> language(){return language_;}
      void language(shared_ptr<Language> language){language_ =language;}

      bool is_compact_run () {return is_compact_run_;}
      void is_compact_run (bool is_compact_run) {is_compact_run_ = is_compact_run;}

      ETestsType tests_type() { return tests_type_;}
      void tests_type(ETestsType tests_type){ tests_type_ = tests_type;}

      string tests_version(){return tests_version_;}
      void tests_version(string tests_version){tests_version_ = tests_version;}

      shared_ptr<User> user(){return user_;}
      void language(shared_ptr<User> user){user_ =user;}

      shared_ptr<Problem> problem(){return problem_;}
      void language(shared_ptr<Problem> problem){problem_ = problem;}

    private:
      friend class odb::access;

      #pragma db id auto
      long long id_;
      //date crated
      string source_code_;

      #pragma db not_null
      shared_ptr<Language> language_;

      bool is_compact_run_; //:Consider enum 
      ETestsType tests_type_;
      string tests_version_;

      #pragma db not_null
      shared_ptr<User> user_;

      #pragma db not_null
      shared_ptr<Problem> problem_;
  };

}

//( try this after model layer is complete)
//:Boost 
//:Datetime
//:MediumText 

#endif