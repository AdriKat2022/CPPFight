add_library(lib_cppfight
    "Include/Game.h"
    "Include/Baby.h"
    "Include/Dialogue.h"
    "Include/Player.h"
    "Include/Damageable.h"
    "Include/Enemy.h"
    "Include/ActionData.h"
    "Include/Action.h"
    "Include/IDrawable.h"
    "Include/Clickable.h"
    "Include/TextBox.h"
    "Include/SpecificActionButton.h"
    "Include/Button.h"
    "Include/FightButton.h"
    "Include/ActionButton.h"
    "Include/EncounterState.h"
    "Include/Encounter.h"
    "Include/EncounterFighting.h"
    "Include/EncounterActing.h"
    "Include/EncounterIdle.h"
    "Include/EncounterMonsterTurn.h"
    "Include/EnemyData.h"
    "Include/EnemyLoader.h"
 "Include/FilePaths.h" "Include/Main.h")

target_sources(lib_cppfight
    PRIVATE
    "Source/Game.cpp"
    "Source/Baby.cpp"
    "Source/Dialogue.cpp"
    "Source/Player.cpp"
    "Source/Damageable.cpp"
    "Source/Enemy.cpp"
    "Source/Encounter.cpp"
    "Source/EnemyLoader.cpp"
 "Source/ActionButton.cpp" "Source/FightButton.cpp" "Source/Button.cpp" "Source/IDrawable.cpp" "Source/Clickable.cpp")

target_include_directories(lib_cppfight
    PUBLIC
    Include
)

target_link_libraries(lib_cppfight
    PUBLIC
    sfml-graphics
    sfml-audio
)

add_executable(cppfight
    Source/Main.cpp
)

target_link_libraries(cppfight
    PRIVATE
    lib_cppfight
    sfml-graphics
    sfml-audio
)

# The following command is executed only when cmake is executed
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../media DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Copy resources to build directory
add_custom_target(copy-resources ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${CMAKE_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources
)

add_dependencies(cppfight copy-resources)