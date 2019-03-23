option(BUILD_TEST "Build the unit tests" ON)
if(BUILD_TEST)
    add_library(unity STATIC
            unity/src/unity.c)

    target_include_directories(unity PUBLIC
            unity/src)
endif()

add_library(cJson STATIC
        cJson/cJSON.c)

target_include_directories(cJson PUBLIC
        cJson)

add_library(cstring_jslike STATIC
        cstring_jslike/cstring_jslike.c)

target_include_directories(cstring_jslike PUBLIC
        cstring_jslike)
