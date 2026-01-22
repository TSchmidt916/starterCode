add_library (cs4212-util
  ArgumentParsing.cpp ArgumentParsing.h
  handleGraphicsArgs.cpp handleGraphicsArgs.h
  model_obj.cpp model_obj.h
  vec3.h
  framebuffer.h framebuffer.cpp
)

add_executable(fbMain
fbMain.cpp
)
target_link_libraries(fbMain cs4212-util)
target_link_libraries(fbMain ${Boost_PROGRAM_OPTIONS_LIBRARIES})
target_link_libraries(fbMain PNG::PNG)
target_link_libraries(fbMain ZLIB::ZLIB)

target_compile_definitions(cs4212-util PUBLIC HAS_GLM)
target_link_libraries(cs4212-util PRIVATE Boost::program_options)
target_link_libraries(cs4212-util PUBLIC glm::glm)  
