project (AKBot)
cmake_minimum_required (VERSION 3.0)
enable_testing()
option(AKBOT_SSCAIT "Generate SSCAIT supported version")

cmake_policy(SET CMP0028 NEW)
cmake_policy(SET CMP0003 NEW)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BWAPI_SSCAIT_DIR "$ENV{BWAPI_SSCAIT_DIR}")
set(BWAPI_DIR "$ENV{BWAPI_DIR}")
STRING(REPLACE "\\" "/" BWAPI_SSCAIT_DIR ${BWAPI_SSCAIT_DIR})
STRING(REPLACE "\\" "/" BWAPI_DIR ${BWAPI_DIR})

add_subdirectory (BOSS)
add_subdirectory (SparCraft) 
add_subdirectory (UAlbertaBot) 
add_subdirectory (AKBot.Tests) 
add_subdirectory (AKBot.CombatSimulation) 
