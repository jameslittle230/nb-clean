project( man )
cmake_minimum_required( VERSION 2.8.3 )

set( MAN_SRCS main.cpp
  man.cpp
)

add_executable(
  man
  ${MAN_SRCS}
)
