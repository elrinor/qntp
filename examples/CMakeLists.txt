add_executable(qntp_example qntp_example.cpp)
target_link_libraries(qntp_example qntp Qt::Core)

enable_testing()
add_test(NAME qntp_example COMMAND qntp_test)
