cmake_minimum_required(VERSION 3.20)
project(wasmbind-example)

include(FetchContent)

FetchContent_Declare(
  wasmbind
  GIT_REPOSITORY https://github.com/emlite/wasm-cbind.git
  GIT_TAG        main
  GIT_SHALLOW    True
)

# if targeting wasm32-unknown-unknown (freestanding)
set(EMLITE_USE_DLMALLOC ON CACHE BOOL " " FORCE)
FetchContent_MakeAvailable(wasm-cbind)

add_executable(main src/main.c)
target_link_libraries(main PRIVATE webbind::webbind)
target_compile_options(main PRIVATE -Wno-incompatible-pointer-types)
set_target_properties(main PROPERTIES LINKER_LANGUAGE C SUFFIX .wasm LINK_FLAGS "-Wl,--no-entry,--allow-undefined,--export=main,--export-dynamic,--export-table,--import-memory,--export-memory,--strip-all")