add_library(lib_cppfight
	"Include/Game.h"
	"Source/Game.cpp"
	"Include/Baby.h"
	"Source/Baby.cpp"
	"Include/Dialogue.h"
	"Source/Dialogue.cpp"
	"Include/Player.h"
	"Source/Player.cpp"
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
 "Source/Damageable.cpp" "Source/Enemy.cpp")

target_include_directories(lib_cppfight
	PRIVATE
	Include
)

target_link_libraries(lib_cppfight PUBLIC sfml-graphics sfml-audio)

add_executable(cppfight
	Source/Main.cpp
)

target_include_directories(cppfight
	PRIVATE
	Include
)

target_link_libraries(cppfight PUBLIC lib_cppfight sfml-graphics sfml-audio)

# The following command is executed only when cmake is executed
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/../media DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


# Copy resources to build directory
add_custom_target(copy-resources ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different ${CMAKE_SOURCE_DIR}/resources ${CMAKE_CURRENT_BINARY_DIR}/resources)

add_dependencies(cppfight copy-resources)