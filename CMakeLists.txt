
cmake_minimum_required(VERSION 3.0)
project(sdl_example)


set(APP_NAME ${CMAKE_PROJECT_NAME}_app)

# Set module include path
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Includes
# include(FindOpenGL)
# include(FindThreads)


# Set standard
set(CMAKE_CXX_STANDARD 14)

# Find dependencies
# find_package(OpenGL  REQUIRED)
find_package(SDL2 REQUIRED)
# find_package(lSDL2_image REQUIRED)
# find_package(Threads REQUIRED)

# Set ${APP_NAME} sources
set(SRCS main.cpp)

# include_directories(${SDL2_INCLUDE_DIRS})

# Add binary target
add_executable(${APP_NAME}
                  ${SRCS})

target_include_directories(${APP_NAME} PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(${APP_NAME} ${SDL2_LIBRARIES} SDL2_image)


