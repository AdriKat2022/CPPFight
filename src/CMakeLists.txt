add_library(lib_cppfight
	Include/Game.h
	Source/Game.cpp
 "Include/Baby.h"
 "Source/Baby.cpp"
 "Include/Dialogue.h"
 "Source/Dialogue.cpp"
 "Include/Player.h"
 "Source/Player.cpp"
 "Include/IDamageable.h"
 "Include/Enemy.h"
 "Include/ActionData.h"
 "Include/Action.h"
 "Include/IDrawable.h"
 "Include/Clickable.h"
  "Include/TextBox.h" "Include/SpecificActionButton.h" "Include/Button.h" "Include/FightButton.h" "Include/ActionButton.h")

target_include_directories(lib_cppfight
 PRIVATE
  Include
)

target_link_libraries(lib_cppfight PUBLIC sfml-graphics)

add_executable(cppfight
	Source/Main.cpp
)

target_include_directories(cppfight
 PRIVATE
  Include
)

target_link_libraries(cppfight PUBLIC lib_cppfight sfml-graphics)

# The following command is executed only when cmake is executed
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../media DESTINATION ${CMAKE_CURRENT_BINARY_DIR})