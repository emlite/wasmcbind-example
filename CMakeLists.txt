cmake_minimum_required(VERSION 3.20)
project(wasmbind-example)

set(EMLITE_USE_DLMALLOC ON CACHE BOOL " " FORCE)
add_subdirectory(wasm-cbind)

add_executable(main src/main.c)
target_link_libraries(main PRIVATE webbind::webbind)
target_compile_options(main PRIVATE -Wno-incompatible-pointer-types)
set_target_properties(main PROPERTIES LINKER_LANGUAGE C SUFFIX .wasm LINK_FLAGS "-Wl,--no-entry,--allow-undefined,--export=main,--export-dynamic,--export-table,--import-memory,--export-memory,--strip-all")