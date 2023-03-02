

project (main LANGUAGES CXX)

set (CMAKE_CXX_FLAGS "-Ofast")

add_executable(main 
    main.cpp
    castling.cpp
    move.cpp
    moveGen.cpp
    pos.cpp
    search.cpp
)