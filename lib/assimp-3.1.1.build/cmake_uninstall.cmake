IF(NOT EXISTS "/home/arild/SpiderOak Hive/OpenGL/cpp-opengl-game-master/lib/assimp-3.1.1.build/install_manifest.txt")
  MESSAGE(FATAL_ERROR "Cannot find install manifest: \"/home/arild/SpiderOak Hive/OpenGL/cpp-opengl-game-master/lib/assimp-3.1.1.build/install_manifest.txt\"")
ENDIF(NOT EXISTS "/home/arild/SpiderOak Hive/OpenGL/cpp-opengl-game-master/lib/assimp-3.1.1.build/install_manifest.txt")

FILE(READ "/home/arild/SpiderOak Hive/OpenGL/cpp-opengl-game-master/lib/assimp-3.1.1.build/install_manifest.txt" files)
STRING(REGEX REPLACE "\n" ";" files "${files}")
FOREACH(file ${files})
  MESSAGE(STATUS "Uninstalling \"$ENV{DESTDIR}${file}\"")
  EXEC_PROGRAM(
    "/usr/bin/cmake" ARGS "-E remove \"$ENV{DESTDIR}${file}\""
    OUTPUT_VARIABLE rm_out
    RETURN_VALUE rm_retval
    )
  IF(NOT "${rm_retval}" STREQUAL 0)
    MESSAGE(FATAL_ERROR "Problem when removing \"$ENV{DESTDIR}${file}\"")
  ENDIF(NOT "${rm_retval}" STREQUAL 0)
ENDFOREACH(file)
