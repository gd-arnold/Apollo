cmake_minimum_required(VERSION 3.13.4)
set (CMAKE_CXX_STANDARD 17)

project(Apollo)

include_directories(src/core src/math src/shapes/ src/camera src/spectrum)

add_executable(${PROJECT_NAME} 
	src/main.cpp 
	src/core/film.cpp src/core/imageio.cpp src/core/primitive.cpp 
	src/math/interaction.cpp src/math/matrix.cpp src/math/ray.cpp src/math/transform.cpp
	src/shapes/shape.cpp src/shapes/sphere.cpp
	src/camera/camera.cpp
	src/spectrum/rgb.cpp
	src/core/apollo.h src/core/film.h src/core/imageio.h src/core/primitive.h src/core/stringprint.h
	src/math/bounds2.h src/math/bounds3.h src/math/bounds3.h src/math/interaction.h src/math/matrix.h src/math/normal3.h src/math/point2.h src/math/point3.h src/math/ray.h src/math/transform.h src/math/vector2.h src/math/vector3.h
	src/shapes/shape.h src/shapes/sphere.h
	src/camera/camera.h
	src/spectrum/rgb.h)
