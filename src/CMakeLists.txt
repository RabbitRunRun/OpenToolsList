project(OTL)

set(OTL_SOURCE_DIR ${PROJECT_SOURCE_DIR}/..)

option(OTL_WITH_OPENSSL "Supporting AES, RAS and SSL with OpenSSL" OFF)

include_directories(${OTL_SOURCE_DIR}/include)
include_directories(${OTL_SOURCE_DIR}/src)
MESSAGE(STATUS "${OTL_SOURCE_DIR}")

set(OTL_MODULES codec io lego mem net sync tools utils)

if (OTL_WITH_OPENSSL)
    LIST(APPEND OTL_MODULES ssl)
endif (OTL_WITH_OPENSSL)

set(OTL_INCLUDE_FILES)
set(OTL_SRC_FILES)
set(OTL_SRC_INCLUDE_FILES)

foreach (module ${OTL_MODULES})
    FILE(GLOB_RECURSE OTL_INCLUDE_${module}_FILES ${OTL_SOURCE_DIR}/include/OTL/${module}/*.h)
    LIST(APPEND OTL_INCLUDE_FILES ${OTL_INCLUDE_${module}_FILES})

    FILE(GLOB_RECURSE OTL_SRC_${module}_FILES ${OTL_SOURCE_DIR}/src/OTL/${module}/*.cpp)
    LIST(APPEND OTL_SRC_FILES ${OTL_SRC_${module}_FILES})

    FILE(GLOB_RECURSE OTL_SRC_INCLUDE_${module}_FILES ${OTL_SOURCE_DIR}/src/OTL/${module}/*.h)
    LIST(APPEND OTL_SRC_INCLUDE_FILES ${OTL_SRC_INCLUDE_${module}_FILES})
endforeach ()

set(OTL_INCLUDE_DIR ${OTL_SOURCE_DIR}/include)

add_library(${PROJECT_NAME}_STATIC STATIC ${OTL_INCLUDE_FILES} ${OTL_SRC_INCLUDE_FILES} ${OTL_SRC_FILES})
# add_library(${PROJECT_NAME}_SHARED SHARED ${OTL_INCLUDE_FILES} ${OTL_SRC_INCLUDE_FILES} ${OTL_SRC_FILES})
# target_link_libraries(${PROJECT_NAME}_SHARED ${PROJECT_NAME}_STATIC)

if (OTL_WITH_OPENSSL)
    message(STATUS "Build with OpenSSL")
    add_definitions(-DOTL_WITH_OPENSSL)
    find_package(OpenSSL REQUIRED)
    include_directories(${OPENSSL_INCLUDE_DIR})
    # target_link_libraries(${PROJECT_NAME}_SHARED ${OPENSSL_CRYPTO_LIBRARY})
    target_link_libraries(${PROJECT_NAME}_STATIC ${OPENSSL_CRYPTO_LIBRARY})
    # target_link_libraries(${PROJECT_NAME}_SHARED ${OPENSSL_SSL_LIBRARY})
    target_link_libraries(${PROJECT_NAME}_STATIC ${OPENSSL_SSL_LIBRARY})
endif (OTL_WITH_OPENSSL)

if (WIN32)
    # target_link_libraries(${PROJECT_NAME}_SHARED wininet.lib)
    target_link_libraries(${PROJECT_NAME}_STATIC wininet.lib)
    # target_link_libraries(${PROJECT_NAME}_STATIC ole32.lib)
elseif (APPLE)
    # target_link_libraries(${PROJECT_NAME}_SHARED pthread)
    target_link_libraries(${PROJECT_NAME}_STATIC pthread)
elseif (UNIX)
    # target_link_libraries(${PROJECT_NAME}_SHARED pthread)
    target_link_libraries(${PROJECT_NAME}_STATIC pthread)
    # target_link_libraries(${PROJECT_NAME}_STATIC uuid)
endif ()

# set_target_properties(${PROJECT_NAME}_SHARED PROPERTIES OUTPUT_NAME ${PROJECT_NAME}${ENV_SUFFIX})
set_target_properties(${PROJECT_NAME}_STATIC PROPERTIES OUTPUT_NAME ${PROJECT_NAME}_static${ENV_SUFFIX})

if (OTL_INSTALL)
    install(TARGETS
            # ${PROJECT_NAME}_SHARED
            ${PROJECT_NAME}_STATIC
            RUNTIME DESTINATION ${ENV_RUNTIME_DIR}
            LIBRARY DESTINATION ${ENV_LIBRARY_DIR}
            ARCHIVE DESTINATION ${ENV_ARCHIVE_DIR}
            )

    install(DIRECTORY ${OTL_INCLUDE_DIR}/OTL
            DESTINATION ${ENV_HEADER_DIR}
            )

endif (OTL_INSTALL)
