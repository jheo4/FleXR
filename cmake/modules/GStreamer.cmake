macro(use_gstreamer)
  pkg_search_module(GSTREAMER REQUIRED gstreamer-1.0)
  pkg_search_module(GST_VIDEO REQUIRED gstreamer-video-1.0)
  pkg_search_module(GST_AUDIO REQUIRED gstreamer-audio-1.0)
  if( GSTREAMER_FOUND AND GST_VIDEO_FOUND AND GST_AUDIO_FOUND )
    message(STATUS "[GStreamer Details]")
    message("\t GSTREAMER_INCLUDE_DIRS: ${GSTREAMER_INCLUDE_DIRS} ${GST_VIDEO_INCLUDE_DIRS} ${GST_AUDIO_INCLUDE_DIRS}")
    message("\t GST_VIDEO_INCLUDE_DIRS: ${GST_VIDEO_INCLUDE_DIRS}")
    message("\t GST_AUDIO_INCLUDE_DIRS: ${GST_AUDIO_INCLUDE_DIRS}")
    message("\t GSTREAMER_LDFLAGS: ${GSTREAMER_LDFLAGS}")
    message("\t GST_VIDEO_LDFLAGS: ${GST_VIDEO_LDFLAGS}")
    message("\t GST_AUDIO_LDFLAGS: ${GST_AUDIO_LDFLAGS}")

    include_directories(${GSTREAMER_INCLUDE_DIRS} ${GST_VIDEO_INCLUDE_DIRS} ${GST_AUDIO_INCLUDE_DIRS})
    list(APPEND MXRE_CXX_FLAGS ${GSTREAMER_CFLAGS_OTHER} ${GST_AUDIO_CFLAGS_OTHER} ${GST_VIDEO_CFLAGS_OTHER})
    list(APPEND MXRE_LINKER_FLAGS ${GSTREAMER_LDFLAGS} ${GST_VIDEO_LDFLAGS} ${GST_AUDIO_LDFLAGS})
  endif( GSTREAMER_FOUND AND GST_VIDEO_FOUND AND GST_AUDIO_FOUND )
endmacro()
