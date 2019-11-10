project(bin2woz)

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug CACHE STRING
       "Choose the type of build, options are: None Debug Release RelWithDebInfo
MinSizeRel."
       FORCE )
endif()

add_executable( bin2woz
	bin2woz.c
	# files not necessary to build target
	README.md
	LICENSE
)
