cmake_minimum_required(VERSION 3.25)

set(project_name cslab) ## rename your project here
set(CMAKE_BUILD_TYPE Debug)

project(${project_name})

set(CMAKE_CXX_STANDARD 17)

include_directories(${INCLUDE_DIR}
    src/model/entities
    src/model/orm
    src/dto
)

add_library(${project_name}-lib
        src/model/orm/model-odb.cxx
        src/model/persistence/orm-persist.cpp
        src/AppComponent.hpp
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
target_compile_definitions(${project_name}-lib PUBLIC DATABASE_PGSQL)
target_link_libraries(${project_name}-exe ${project_name}-lib)
add_dependencies(${project_name}-exe ${project_name}-lib)

#add_executable(${project_name}-driver  src/driver/driver.cpp )
#target_compile_definitions(${project_name}-driver PRIVATE DATABASE_PGSQL)
#target_link_libraries(${project_name}-driver ${project_name}-lib)
#add_dependencies(${project_name}-driver ${project_name}-lib)

file(COPY ${CMAKE_SOURCE_DIR}/config.json
    DESTINATION ${CMAKE_BINARY_DIR}
)

set_target_properties(${project_name}-lib ${project_name}-exe PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

