cmake_minimum_required(VERSION 2.0)

project(armstrong-ide)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-2.4) 
pkg_check_modules(GTKSOURCEVIEWMM gtksourceviewmm-2.0)
pkg_check_modules(GDL gdl-1.0)
                                                                
# Now the variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES 
# contain what you expect 

add_subdirectory(src)

