########################################################################
# Setup Qt and Qwt
########################################################################
FIND_PACKAGE(Qwt)
IF(Qt5_FOUND AND QWT_FOUND)
    INCLUDE_DIRECTORIES(${QWT_INCLUDE_DIRS})
ENDIF(Qt5_FOUND AND QWT_FOUND)

########################################################################
# Build our library
########################################################################
IF(Qt5_FOUND AND QWT_FOUND)
  QT5_WRAP_CPP(MOCSrcs TextEditWidget.h TextEditWrapper.h)
  ADD_LIBRARY(textedit TextEditWidget.cpp TextEditWrapper.cpp TextEdit.cpp ${MOCSrcs})
  TARGET_LINK_LIBRARIES(textedit Qt5::Widgets ${QWT_LIBRARIES})
  SG_SET_PIC(textedit)
  SET(SG_HAVE_TEXTEDIT ON CACHE INTERNAL "Has Textedit been built?")
  #ADD_SUBDIRECTORY(test)
ELSE(Qt5_FOUND AND QWT_FOUND)
  SET(SG_HAVE_TEXTEDIT OFF CACHE INTERNAL "Has Textedit been built?")
ENDIF(Qt5_FOUND AND QWT_FOUND)
