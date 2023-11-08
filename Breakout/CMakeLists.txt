set(Breakout_SOURCES
    BallObject.cpp
    BlockObject.cpp
    Breakout.cpp
    main.cpp
    PaddleObject.cpp
)

set(Breakout_HEADERS
    BallObject.h
    BlockObject.h
    Breakout.h
    PaddleObject.h
)

add_library(Breakout-lib STATIC ${Breakout_SOURCES} ${Breakout_HEADERS})
target_link_libraries(Breakout-lib PUBLIC ImGui-SFML::ImGui-SFML)

add_executable(Breakout main.cpp)
target_link_libraries(Breakout PUBLIC Breakout-lib)