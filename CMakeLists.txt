cmake_minimum_required(VERSION 3.8)
project(type_name VERSION 1.0.0 LANGUAGES CXX)

add_library(type_name INTERFACE)
add_library(AdamBadura::type_name ALIAS type_name)
target_sources(type_name
	INTERFACE
		$<INSTALL_INTERFACE:include/type_name/type_name.hpp>
		$<INSTALL_INTERFACE:include/type_name/type_name.clang.hpp>
		$<INSTALL_INTERFACE:include/type_name/type_name.clang.5.hpp>
		$<INSTALL_INTERFACE:include/type_name/type_name.gcc.hpp>
		$<INSTALL_INTERFACE:include/type_name/type_name.gcc.7_3.hpp>
		$<INSTALL_INTERFACE:include/type_name/type_name.gcc.8_1.hpp>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/type_name/type_name.hpp>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/type_name/type_name.clang.hpp>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/type_name/type_name.clang.5.hpp>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/type_name/type_name.gcc.hpp>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/type_name/type_name.gcc.7_3.hpp>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/type_name/type_name.gcc.8_1.hpp>
)
target_include_directories(type_name
	INTERFACE
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_compile_features(type_name
	INTERFACE
		cxx_std_17
)

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/type_name)

install(
	TARGETS type_name
	EXPORT type_name-targets
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties(type_name PROPERTIES EXPORT_NAME TypeName)

install(
	DIRECTORY include/
	DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(
	EXPORT type_name-targets
	FILE TypeNameTargets.cmake
	NAMESPACE AdamBadura::
	DESTINATION ${INSTALL_CONFIGDIR}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/TypeNameConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion
)
configure_package_config_file(
	${CMAKE_CURRENT_LIST_DIR}/cmake/TypeNameConfig.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/TypeNameConfig.cmake
	INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/TypeNameConfig.cmake
		${CMAKE_CURRENT_BINARY_DIR}/TypeNameConfigVersion.cmake
	DESTINATION ${INSTALL_CONFIGDIR}
)

export(
	EXPORT type_name-targets
	FILE ${CMAKE_CURRENT_BINARY_DIR}/TypeNameTargets.cmake
	NAMESPACE AdamBadura::
)

export(PACKAGE TypeName)
