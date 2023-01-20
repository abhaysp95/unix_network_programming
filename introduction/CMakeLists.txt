unset(s)

list(APPEND s "daytimetcpcli")
list(APPEND s "daytimetcpcliv6")

foreach(target IN LISTS s)
	unset(file)
	string(CONCAT file "${target}" ".c")
	add_executable("${target}" "${file}")
	add_dependencies("${target}" unp_library)
	target_link_libraries("${target}" unp_library)
endforeach()

# add_executable(test test.c)
# add_dependencies(test unp_library)
# target_link_libraries(test unp_library)
