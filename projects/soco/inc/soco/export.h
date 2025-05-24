// export.h
#pragma once

// This file must be included after defining:
//   - <LIBNAME>_PLATFORM   (1 = Windows, 2 = Linux, etc.)
//   - <LIBNAME>_COMPILER   (1 = GCC, 2 = Clang, 3 = MSVC, etc.)
//   - <LIBNAME>_INSIDE     (Defined if building the library)

#if !defined(soco_PLATFORM)
	#error "soco_PLATFORM not defined"
#endif

#if !defined(soco_COMPILER)
	#error "soco_COMPILER not defined"
#endif

#if soco_PLATFORM == 1	// Windows
	#if defined(soco_INSIDE)
		#define soco_API	__declspec(dllexport)
	#else
		#define soco_API	__declspec(dllimport)
	#endif

#elif soco_COMPILER == 1 || soco_COMPILER == 2	// GCC or Clang (Linux/macOS)
	#define soco_API	__attribute__((visibility("default")))

#else
	#define soco_API
#endif
