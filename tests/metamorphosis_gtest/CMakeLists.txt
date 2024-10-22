project(metamorphosis_test)

include_directories(${PROJECT_SOURCE_DIR}/../../src)

set(GTEST_LIBRARIES gtest gtest_main)

set(METAMORPHOSIS_TEST_SOURCE_FILES
        program_test.cpp
)

add_executable(metamorphosis_test
        main.cpp
        ${METAMORPHOSIS_TEST_SOURCE_FILES}
)

target_link_libraries(metamorphosis_test metamorphosis ${GTEST_LIBRARIES})
