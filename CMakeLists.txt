cmake_minimum_required(VERSION 3.25)

set(project_name cslab) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 17)

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/model/model-odb.cxx
        src/db/database.hxx
)

## link libs
include(GNUInstallDirs)
find_package(oatpp 1.4.0 REQUIRED)
find_package(nlohmann_json 3.11.2 REQUIRED)

target_link_libraries(${project_name}-lib
        PRIVATE nlohmann_json::nlohmann_json
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        odb
        odb-pgsql
)

target_include_directories(${project_name}-lib PUBLIC src)

## add executables

add_executable(${project_name}-exe
        src/App.cpp
)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

set_target_properties(${project_name}-lib ${project_name}-exe PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

