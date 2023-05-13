cmake_minimum_required(VERSION 3.23)
project(project_tsp)

set(CMAKE_CXX_STANDARD 14)

add_executable(project_tsp
        main.cpp
        src/Graph.cpp
        src/VertexEdge.cpp
        src/Scraper.cpp
        )
