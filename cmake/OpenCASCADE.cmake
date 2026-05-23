find_package(OpenCASCADE CONFIG PATHS ${OpenCASCADE_DIR} NO_DEFAULT_PATH REQUIRED)

if(OpenCASCADE_FOUND)
    message(STATUS "OpenCASCADE_INCLUDE_DIR: ${OpenCASCADE_INCLUDE_DIR}")
    message(STATUS "OpenCASCADE_LIBRARY_DIR: ${OpenCASCADE_LIBRARY_DIR}")
    message(STATUS "OpenCASCADE_LIBRARIES: ${OpenCASCADE_LIBRARIES}")

    foreach(lib_name ${OpenCASCADE_LIBRARIES})
        find_library(OPEN_CASCADE_${lib_name}_LIBRARY
                NAMES ${lib_name}
                PATHS ${OpenCASCADE_LIBRARY_DIR}
        )
        if(OPEN_CASCADE_${lib_name}_LIBRARY)
            list(APPEND OpenCASCADE_LIBRARIES_FOUND ${OPEN_CASCADE_${lib_name}_LIBRARY})
            message(STATUS "Found ${lib_name}: ${OPEN_CASCADE_${lib_name}_LIBRARY}")
        else()
            message(WARNING "Could NOT find library: ${lib_name}")
        endif()
    endforeach()

    message(STATUS "OpenCASCADE_LIBRARIES_FOUND: ${OpenCASCADE_LIBRARIES_FOUND}")


    set(OpenCASCADE_INSTALL_PREFIX ${OpenCASCADE_INCLUDE_DIR}/../..)

    if (NOT TARGET OpenCASCADE::OpenCASCADE)
        add_library (OpenCASCADE::OpenCASCADE INTERFACE IMPORTED)

        set_target_properties(OpenCASCADE::OpenCASCADE PROPERTIES
                INTERFACE_LINK_LIBRARIES "${OpenCASCADE_LIBRARIES_FOUND}"
                INTERFACE_INCLUDE_DIRECTORIES "${OpenCASCADE_INCLUDE_DIR}"
        )
    endif ()
endif()
