configure_file(armstrong_ide2.ui armstrong_ide2.ui COPYONLY)
configure_file(main-logo.gif main-logo.gif COPYONLY)

link_directories(
    ${GTKMM_LIBRARY_DIRS}
    ${GTKSOURCEVIEWMM_LIBRARY_DIRS}
    ${GDL_LIBRARY_DIRS}
    )

include_directories(
    ${GTKMM_INCLUDE_DIRS}
    ${GTKSOURCEVIEWMM_INCLUDE_DIRS}
    ${GDL_INCLUDE_DIRS}
    )

add_executable(armstrong_ide # name of the executable on Windows will be armstrong_ide.exe 
    main.cc 
    ui-shell.cc 
    ui-shell.h
    Iterable.h
    IProvider.h
    IEditor.h
    Editor.h
    Editor.cpp
    EditorFactory.h
    EditorFactory.cpp
    IEditorArea.h
    EditorArea.h
    EditorArea.cpp
    )

target_link_libraries(armstrong_ide
    ${GTKMM_LIBRARIES}
    ${GTKSOURCEVIEWMM_LIBRARIES}
    ${GDL_LIBRARIES}
    )

add_executable(testcases # name of the executable on Windows will be armstrong_ide.exe 
    ui-shell.cc 
    ui-shell.h
    Iterable.h
    IProvider.h
    IEditor.h
    Editor.h
    Editor.cpp
    EditorFactory.h
    EditorFactory.cpp
    IEditorArea.h
    EditorArea.h
    EditorArea.cpp
    testcases.cpp
    )

target_link_libraries(testcases
    ${GTKMM_LIBRARIES}
    ${GTKSOURCEVIEWMM_LIBRARIES}
    ${GDL_LIBRARIES}
    )
    
