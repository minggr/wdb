add_executable(test_pf "test_pf.cc" "../src/pf.cc")

target_link_libraries(test_pf
    gtest
)

#install(TARGETS test_pf DESTINATION bin)
