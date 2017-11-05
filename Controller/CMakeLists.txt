
if(NOT ENABLE_GUI)
  return()
endif()

option(BUILD_InMoovPlugin "Building a sample plugin \"InMoovPlugin\"" ON)

if(BUILD_InMoovPlugin)
  set(target CnoidInMoovPlugin)
  add_cnoid_plugin(${target} SHARED InMoovPlugin.cpp)
  target_link_libraries(${target} CnoidBodyPlugin)
  apply_common_setting_for_plugin(${target})

  if(QT5)
    qt5_use_modules(${target} Widgets)
  endif()
endif()

install_sample_source(InMoovPlugin.cpp)

add_cnoid_simple_controller(InMoovController InMoovController.cpp)
configure_file(InMoovC.cnoid ${CNOID_SOURCE_SHARE_DIR}/project COPYONLY)
