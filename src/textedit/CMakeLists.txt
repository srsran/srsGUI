########################################################################
# Setup Qt and Qwt
########################################################################
FIND_PACKAGE(Qt4)
IF(QT4_FOUND)
    INCLUDE(${QT_USE_FILE})
ENDIF(QT4_FOUND)

FIND_PACKAGE(Qwt)
IF(QT4_FOUND AND QWT_FOUND)
    INCLUDE_DIRECTORIES(${QWT_INCLUDE_DIRS})
ENDIF(QT4_FOUND AND QWT_FOUND)

########################################################################
# Build our library
########################################################################
IF(QT4_FOUND AND QWT_FOUND)
  QT4_WRAP_CPP(MOCSrcs TextEditWidget.h TextEditWrapper.h)
  ADD_LIBRARY(textedit TextEditWidget.cpp TextEditWrapper.cpp TextEdit.cpp ${MOCSrcs})
  TARGET_LINK_LIBRARIES(textedit ${QT_LIBRARIES} ${QWT_LIBRARIES})
  SG_SET_PIC(textedit)
  SET(SG_HAVE_TEXTEDIT ON CACHE INTERNAL "Has Textedit been built?")
  #ADD_SUBDIRECTORY(test)
ELSE(QT4_FOUND AND QWT_FOUND)
  SET(SG_HAVE_TEXTEDIT OFF CACHE INTERNAL "Has Textedit been built?")
ENDIF(QT4_FOUND AND QWT_FOUND)
