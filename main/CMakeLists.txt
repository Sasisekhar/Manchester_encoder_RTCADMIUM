idf_component_register(SRCS "main_rt_model.cpp"
                    INCLUDE_DIRS "." "include")

target_compile_options(${COMPONENT_LIB} PUBLIC -std=c++17)
target_compile_options(${COMPONENT_LIB} PRIVATE "-Wno-format")
target_compile_options(${COMPONENT_LIB} PRIVATE "-frtti")
target_compile_options(${COMPONENT_LIB} PRIVATE "-fexceptions")
target_compile_options(${COMPONENT_LIB} PRIVATE "-DRT_ESP32")
# target_compile_options(${COMPONENT_LIB} PRIVATE "-DNO_LOGGING")