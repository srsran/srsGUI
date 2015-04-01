########################################################################
# Build tests
########################################################################

ADD_EXECUTABLE(waterfallplot_test_c waterfallplot_test.c)
TARGET_LINK_LIBRARIES(waterfallplot_test_c srsgui m)
ADD_TEST(waterfallplot_test_c waterfallplot_test_c)

ADD_EXECUTABLE(complexplot_test_c complexplot_test.c)
TARGET_LINK_LIBRARIES(complexplot_test_c srsgui m)
ADD_TEST(complexplot_test_c complexplot_test_c)

ADD_EXECUTABLE(realplot_test_c realplot_test.c)
TARGET_LINK_LIBRARIES(realplot_test_c srsgui m)
ADD_TEST(realplot_test_c realplot_test_c)

ADD_EXECUTABLE(scatterplot_test_c scatterplot_test.c)
TARGET_LINK_LIBRARIES(scatterplot_test_c srsgui m)
ADD_TEST(scatterplot_test_c scatterplot_test_c)
