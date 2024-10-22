set(METAMORPHOSIS_SOURCE_FILES
        exception.hpp
        forward_declarations.hpp
        get_c_str_hash.hpp
        image_utils.cpp
        image_utils.hpp
        name_component.hpp
        number_name_component.hpp
        program.cpp
        program.hpp
        program_args.hpp
        sort_policies.hpp
        sort_strategies.cpp
        sort_strategies.hpp
        string_name_component.hpp
        target_file.cpp
        target_file.hpp
        target_image.hpp
)

add_library(metamorphosis STATIC ${METAMORPHOSIS_SOURCE_FILES})

set(suffix "$<IF:$<CONFIG:Debug>,d,>")

if(MSVC)
    target_link_libraries(metamorphosis windowscodecs speed${suffix})
else()
    target_link_libraries(metamorphosis speed${suffix})
endif()
