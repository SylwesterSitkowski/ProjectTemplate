CMAKE_MINIMUM_REQUIRED (VERSION 3.16)
PROJECT                (Test)

SET (ExternalName External)
SET (ProjectName  Project)
SET (TestName     Test)
SET (LibraryName  ${CMAKE_PROJECT_NAME}Lib)
SET (CurrentPath  ${CMAKE_CURRENT_SOURCE_DIR})

MACRO (LOG_ERROR msg)
    EXECUTE_PROCESS (COMMAND ${CMAKE_COMMAND} -E cmake_echo_color --red --bold ${msg})
ENDMACRO ()

SET  (ExternalIncludePath                          ${CurrentPath}/../../${ExternalName})
FILE (GLOB_RECURSE ExternalFilesAndFolders         ${ExternalIncludePath}/*)

SET  (ProjectIncludePath                           ${CurrentPath}/../../${ProjectName}/Logic)
FILE (GLOB_RECURSE ProjectLogicFilesAndFolders     ${ProjectIncludePath}/*)

SET  (ProjectHardwareIncludePath                   ${CurrentPath}/../../${ProjectName}/Hardware)
FILE (GLOB_RECURSE ProjectHardwareFilesAndFolders  ${ProjectHardwareIncludePath}/*.h)

SET  (ProjectGeneratedIncludePath                  ${CurrentPath}/../../${ProjectName}/Generated)
FILE (GLOB_RECURSE ProjectGeneratedFilesAndFolders ${ProjectGeneratedIncludePath}/*)

SET  (TestIncludePath                              ${CurrentPath})
FILE (GLOB_RECURSE TestFilesAndFolders             ${TestIncludePath}/*)

FUNCTION (EXCLUDE_PATHS paths filter)
    FOREACH (path ${${paths}})
        if ("${path}" MATCHES ${filter})
            LIST (REMOVE_ITEM ${paths} ${path})
        endif ("${path}" MATCHES ${filter})
    ENDFOREACH (path)
    SET (${paths} ${${paths}} PARENT_SCOPE)
ENDFUNCTION (EXCLUDE_PATHS)

EXCLUDE_PATHS (ExternalFilesAndFolders        /modbus/*)
EXCLUDE_PATHS (ExternalFilesAndFolders        /Documents/*)
EXCLUDE_PATHS (ProjectLogicFilesAndFolders    /Process/Process.c)
EXCLUDE_PATHS (ProjectHardwareFilesAndFolders /OldLib/*)
EXCLUDE_PATHS (TestFilesAndFolders            /build/*)
EXCLUDE_PATHS (TestFilesAndFolders            /.vscode/*)

MACRO (PARSE_SUBDIRECTORIES_PATHS search_directory paths)
    SET (directoryPaths "")
    FOREACH (subdirectoryPath ${search_directory})
        GET_FILENAME_COMPONENT (directoryPath ${subdirectoryPath} PATH)
        SET (directoryPaths ${directoryPaths} ${directoryPath})
    ENDFOREACH ()

    LIST (REMOVE_DUPLICATES directoryPaths)
    SET  (${paths} ${directoryPaths})
ENDMACRO ()

PARSE_SUBDIRECTORIES_PATHS ("${ExternalFilesAndFolders}"         ExternalPathsLists)
PARSE_SUBDIRECTORIES_PATHS ("${ProjectLogicFilesAndFolders}"     ProjectLogicPathsLists)
PARSE_SUBDIRECTORIES_PATHS ("${ProjectHardwareFilesAndFolders}"  ProjectHardwarePathsLists)
PARSE_SUBDIRECTORIES_PATHS ("${ProjectGeneratedFilesAndFolders}" ProjectGeneratedPathsLists)
PARSE_SUBDIRECTORIES_PATHS ("${TestFilesAndFolders}"             TestPathsLists)
SET                        (ExternalPathsLists ${ExternalPathsLists} ${ExternalIncludePath})                 

MACRO (REMOVE_FILES directory)
    FILE (GLOB removeLists ${directory}/*)
    FOREACH (FILE ${removeLists})
        IF (EXISTS ${file})
            FILE (REMOVE ${file})
        ENDIF ()
    ENDFOREACH (FILE)
ENDMACRO ()

SET          (BuildPath ${CurrentPath}/build)
REMOVE_FILES ("${BuildPath}")

INCLUDE (FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
#SET                        (CMAKE_CXX_FLAGS "-pthread" )
SET                        (gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable (googletest)
ENABLE_TESTING             ()
ADD_EXECUTABLE             (${TestName}                    ${ExternalFilesAndFolders} ${ProjectLogicFilesAndFolders} ${ProjectHardwareFilesAndFolders} ${ProjectGeneratedFilesAndFolders} ${TestFilesAndFolders})
TARGET_INCLUDE_DIRECTORIES (${TestName} PUBLIC             ${ExternalPathsLists} ${ProjectLogicPathsLists} ${ProjectHardwarePathsLists} ${ProjectGeneratedPathsLists} ${TestPathsLists})
TARGET_LINK_LIBRARIES      (${TestName}                    gtest_main)
TARGET_COMPILE_FEATURES    (${TestName} PUBLIC cxx_std_17)
TARGET_COMPILE_DEFINITIONS (${TestName} PUBLIC USE_STDPERIPH_DRIVER IO_VERBOSITY=2 ARM_MATH_CM3 PACK_STRUCT_END MODBUS=1 STM32F10X_CL)

INCLUDE                    (GoogleTest)