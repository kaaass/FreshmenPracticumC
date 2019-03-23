if(BUILD_TEST)
    set(unit_tests
            TestDatabase
            TestData
            TestUtil)
    set(_modules) # Stupid way
    foreach(mod ${modules})
        list(APPEND _modules "../${mod}")
    endforeach()

    foreach(unit_test ${unit_tests})
        add_executable("${unit_test}" "${unit_test}.c" "${_modules}")
        target_link_libraries("${unit_test}" unity cJson cstring_jslike)
        add_test(NAME "${unit_test}"
                COMMAND "./${unit_test}")
        add_coverage("${unit_test}")
    endforeach()
endif()