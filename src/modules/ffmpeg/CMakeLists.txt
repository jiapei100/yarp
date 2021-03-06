# Copyright: (C) 2009 RobotCub Consortium
# Author: Paul Fitzpatrick
# CopyPolicy: Released under the terms of the LGPLv2.1 or later, see LGPL.TXT

if(COMPILE_DEVICE_LIBRARY)
  yarp_prepare_device(ffmpeg_grabber
                      TYPE yarp::dev::FfmpegGrabber
                      INCLUDE FfmpegGrabber.h
                      WRAPPER grabber)
  yarp_prepare_device(ffmpeg_writer
                      TYPE yarp::dev::FfmpegWriter
                      INCLUDE FfmpegWriter.h)
  yarp_install(FILES ffmpeg.ini
               COMPONENT runtime
               DESTINATION ${YARP_PLUGIN_MANIFESTS_INSTALL_DIR})
endif()

if(NOT SKIP_ffmpeg_grabber OR NOT SKIP_ffmpeg_writer)
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
  get_property(YARP_OS_INCLUDE_DIRS TARGET YARP_OS PROPERTY INCLUDE_DIRS)
  get_property(YARP_sig_INCLUDE_DIRS TARGET YARP_sig PROPERTY INCLUDE_DIRS)
  get_property(YARP_dev_INCLUDE_DIRS TARGET YARP_dev PROPERTY INCLUDE_DIRS)
  include_directories(${YARP_OS_INCLUDE_DIRS}
                      ${YARP_sig_INCLUDE_DIRS}
                      ${YARP_dev_INCLUDE_DIRS})
  include_directories(SYSTEM ${FFMPEG_INCLUDE_DIR})
  yarp_add_plugin(yarp_ffmpeg FfmpegGrabber.cpp
                              FfmpegWriter.cpp
                              FfmpegGrabber.h
                              FfmpegWriter.h
                              ffmpeg_api.h
                              ffmpeg_api.cpp)
  target_link_libraries(yarp_ffmpeg YARP_OS
                                    YARP_sig
                                    YARP_dev
                                    ${FFMPEG_LIBRARIES})
  if(MINGW)
    target_link_libraries(yarp_ffmpeg ws2_32)
  endif()
  yarp_install(TARGETS yarp_ffmpeg
               EXPORT YARP
               COMPONENT runtime
               LIBRARY DESTINATION ${YARP_DYNAMIC_PLUGINS_INSTALL_DIR}
               ARCHIVE DESTINATION ${YARP_STATIC_PLUGINS_INSTALL_DIR})
endif()
