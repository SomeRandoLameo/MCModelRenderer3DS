cmake_minimum_required(VERSION 3.22)

# ImGui
add_subdirectory(imgui-ctr)

# AMY
set(AMY_BUILD_STB_IMAGE CACHE BOOL 1)
add_subdirectory(amethyst)