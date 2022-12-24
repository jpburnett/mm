
subdir('lib/libgfxd')
subdir('ZAPDUtils')
subdir('ExporterTest')

# TODO include these options/args
#ASAN ?= 0
#DEPRECATION_ON ?= 1
#
#ifneq ($(ASAN),0)
#  CXXFLAGS += -fsanitize=address -fsanitize=pointer-compare -fsanitize=pointer-subtract -fsanitize=undefined
#endif
#ifneq ($(DEPRECATION_ON),0)
#  CXXFLAGS += -DDEPRECATION_ON
#endif

cpp = meson.get_compiler('cpp')

m_dep = cpp.find_library('m', required: true)
dl_dep = cpp.find_library('dl', required: true)
png_dep = dependency('png')

zapd_genbuildinfo = find_program('ZAPD/genbuildinfo.py')
if get_option('buildtype') == 'debug'
  r = run_command('python3', zapd_genbuildinfo, '--opath', meson.current_build_dir(), '--devel', check: true)
elif
  r = run_command('python3', zapd_genbuildinfo, '--opath', meson.current_build_dir(), check: true)
endif
message(r.stdout())

tinyxml2 = 'lib/tinyxml2/tinyxml2.cpp'

zapd_srcs = [
  join_paths(meson.current_build_dir(), 'BuildInfo.cpp'),
  'ZAPD/Declaration.cpp',
  'ZAPD/GameConfig.cpp',
  'ZAPD/Globals.cpp',
  'ZAPD/ImageBackend.cpp',
  'ZAPD/Main.cpp',
  'ZAPD/OutputFormatter.cpp',
  'ZAPD/WarningHandler.cpp',
  'ZAPD/ZAnimation.cpp',
  'ZAPD/ZArray.cpp',
  'ZAPD/ZBackground.cpp',
  'ZAPD/ZBlob.cpp',
  'ZAPD/ZCollision.cpp',
  'ZAPD/ZCollisionPoly.cpp',
  'ZAPD/ZCutscene.cpp',
  'ZAPD/ZDisplayList.cpp',
  'ZAPD/ZFile.cpp',
  'ZAPD/ZLimb.cpp',
  'ZAPD/ZMtx.cpp',
  'ZAPD/ZPath.cpp',
  'ZAPD/ZPlayerAnimationData.cpp',
  'ZAPD/ZPointer.cpp',
  'ZAPD/ZResource.cpp',
  'ZAPD/ZScalar.cpp',
  'ZAPD/ZSkeleton.cpp',
  'ZAPD/ZString.cpp',
  'ZAPD/ZSymbol.cpp',
  'ZAPD/ZTexture.cpp',
  'ZAPD/ZTextureAnimation.cpp',
  'ZAPD/ZVector.cpp',
  'ZAPD/ZVtx.cpp',
  'ZAPD/OtherStructs/CutsceneMM_Commands.cpp',
  'ZAPD/OtherStructs/Cutscene_Commands.cpp',
  'ZAPD/OtherStructs/SkinLimbStructs.cpp',
  'ZAPD/Overlays/ZOverlay.cpp',
  'ZAPD/ZRoom/ZRoom.cpp',
  'ZAPD/ZRoom/ZRoomCommand.cpp',
  'ZAPD/ZRoom/Commands/EndMarker.cpp',
  'ZAPD/ZRoom/Commands/SetActorCutsceneList.cpp',
  'ZAPD/ZRoom/Commands/SetActorList.cpp',
  'ZAPD/ZRoom/Commands/SetAlternateHeaders.cpp',
  'ZAPD/ZRoom/Commands/SetAnimatedMaterialList.cpp',
  'ZAPD/ZRoom/Commands/SetCameraSettings.cpp',
  'ZAPD/ZRoom/Commands/SetCollisionHeader.cpp',
  'ZAPD/ZRoom/Commands/SetCsCamera.cpp',
  'ZAPD/ZRoom/Commands/SetCutscenes.cpp',
  'ZAPD/ZRoom/Commands/SetEchoSettings.cpp',
  'ZAPD/ZRoom/Commands/SetEntranceList.cpp',
  'ZAPD/ZRoom/Commands/SetExitList.cpp',
  'ZAPD/ZRoom/Commands/SetLightList.cpp',
  'ZAPD/ZRoom/Commands/SetLightingSettings.cpp',
  'ZAPD/ZRoom/Commands/SetMesh.cpp',
  'ZAPD/ZRoom/Commands/SetMinimapChests.cpp',
  'ZAPD/ZRoom/Commands/SetMinimapList.cpp',
  'ZAPD/ZRoom/Commands/SetObjectList.cpp',
  'ZAPD/ZRoom/Commands/SetPathways.cpp',
  'ZAPD/ZRoom/Commands/SetRoomBehavior.cpp',
  'ZAPD/ZRoom/Commands/SetRoomList.cpp',
  'ZAPD/ZRoom/Commands/SetSkyboxModifier.cpp',
  'ZAPD/ZRoom/Commands/SetSkyboxSettings.cpp',
  'ZAPD/ZRoom/Commands/SetSoundSettings.cpp',
  'ZAPD/ZRoom/Commands/SetSpecialObjects.cpp',
  'ZAPD/ZRoom/Commands/SetStartPositionList.cpp',
  'ZAPD/ZRoom/Commands/SetTimeSettings.cpp',
  'ZAPD/ZRoom/Commands/SetTransitionActorList.cpp',
  'ZAPD/ZRoom/Commands/SetWind.cpp',
  'ZAPD/ZRoom/Commands/SetWorldMapVisited.cpp',
  'ZAPD/ZRoom/Commands/Unused09.cpp',
  'ZAPD/ZRoom/Commands/Unused1D.cpp',
  'ZAPD/ZRoom/Commands/ZRoomCommandUnk.cpp']

executable('ZAPD.out', [zapd_srcs, tinyxml2],
  include_directories: [zapd_utils_inc, 'ZAPD', 'lib/elfio', 'lib/libgfxd', 'lib/tinyxml2'],
  cpp_args: ['-std=c++17', '-Wextra', '-fno-omit-frame-pointer'],
  link_with: [libgfxd, libZAPDUtils, libExporterTest],
  dependencies: [m_dep, dl_dep, png_dep])
  #link_args:['-Wl,-force_load', 'ExporterTest/ExporterTest.a'])


