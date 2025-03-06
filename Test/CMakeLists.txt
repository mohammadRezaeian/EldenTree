enable_testing()

find_package(GTest REQUIRED)

add_executable(test test.cpp ${HEADER_FILES})

target_link_libraries( test  GTest::gtest GTest::gtest_main)



include_directories(${PROJECT_SOURCE_DIR}/Include)

# i use this because i think, i need see headers and functions on qtcreator
# but in clion i don't need to do that Because it shows that by default

file(GLOB_RECURSE HEADER_FILES "Include/*.h")

add_test(NAME AllTestsInTest COMMAND test)
