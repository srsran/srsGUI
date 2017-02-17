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
# Build the graphics library
########################################################################

file(GLOB modules *) 

SET(SOURCES_ALL "")
FILE(GLOB tmp "*.cpp")
LIST(APPEND SOURCES_ALL ${tmp})
FOREACH (_module ${modules})
	IF(IS_DIRECTORY ${_module})
		FILE(GLOB tmp "${_module}/*.cpp")
		LIST(APPEND SOURCES_ALL ${tmp})		
	ENDIF(IS_DIRECTORY ${_module})
ENDFOREACH(_module ${modules})

IF(QWT_MAJOR_VERSION LESS 6)
	MESSAGE(STATUS "QWT6 is required.")
ENDIF(QWT_MAJOR_VERSION LESS 6)

IF(QT4_FOUND AND QWT_FOUND AND QWT_MAJOR_VERSION EQUAL 6)
  QT4_WRAP_CPP(lineplotwraps ../include/srsgui/common/Lineplot.h)
  QT4_WRAP_CPP(pointplotwraps ../include/srsgui/common/Pointplot.h)
  QT4_WRAP_CPP(spectrogramplotwraps ../include/srsgui/common/Spectrogramplot.h)
  QT4_WRAP_CPP(complex complexplot/ComplexWidget.h complexplot/ComplexplotWrapper.h)
  QT4_WRAP_CPP(real realplot/RealWidget.h realplot/RealplotWrapper.h)
  QT4_WRAP_CPP(scatter scatterplot/ScatterWidget.h scatterplot/ScatterplotWrapper.h)
  QT4_WRAP_CPP(waterfall waterfallplot/WaterfallWidget.h waterfallplot/WaterfallplotWrapper.h)
  QT4_WRAP_CPP(textedit textedit/TextEditWidget.h textedit/TextEditWrapper.h ../include/srsgui/plot/text_edit.h)
  QT4_WRAP_CPP(keyvalue keyvalue/KeyValueWidget.h keyvalue/KeyValueWrapper.h ../include/srsgui/plot/key_value.h)

  INCLUDE_DIRECTORIES(common complexplot realplot scatterplot waterfallplot textedit keyvalue ${Boost_INCLUDE_DIRS})
  
  ADD_LIBRARY(srsgui SHARED ${eventwraps} ${lineplotwraps} ${pointplotwraps} ${spectrogramplotwraps} ${complex} ${real} ${scatter} ${waterfall} ${textedit} ${keyvalue} ${SOURCES_ALL} )
  TARGET_LINK_LIBRARIES(srsgui pthread ${QT_LIBRARIES} ${QWT_LIBRARIES})
  INSTALL(TARGETS srsgui DESTINATION ${LIBRARY_DIR})
  SG_SET_PIC(srsgui)

  MESSAGE(STATUS "   srsGUI library will be installed.")

ELSE(QT4_FOUND AND QWT_FOUND AND AND QWT_MAJOR_VERSION EQUAL 6) 

  MESSAGE(STATUS "   QT4 or Qwt6 not found. srsGUI library is not generated")
  
ENDIF(QT4_FOUND AND QWT_FOUND AND QWT_MAJOR_VERSION EQUAL 6)




