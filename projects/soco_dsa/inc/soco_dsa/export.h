// export.h
#pragma once

// This file must be included after defining:
//   - <LIBNAME>_PLATFORM   (1 = Windows, 2 = Linux, etc.)
//   - <LIBNAME>_COMPILER   (1 = GCC, 2 = Clang, 3 = MSVC, etc.)
//   - <LIBNAME>_INSIDE     (Defined if building the library)

#if !defined(soco_dsa_PLATFORM)
	#error "soco_dsa_PLATFORM not defined"
#endif

#if !defined(soco_dsa_COMPILER)
	#error "soco_dsa_COMPILER not defined"
#endif

#if soco_dsa_PLATFORM == 1	// Windows
	#if defined(soco_dsa_INSIDE)
		#define soco_dsa_API	__declspec(dllexport)
	#else
		#define soco_dsa_API	__declspec(dllimport)
	#endif

#elif soco_dsa_COMPILER == 1 || soco_dsa_COMPILER == 2	// GCC or Clang (Linux/macOS)
	#define soco_dsa_API	__attribute__((visibility("default")))

#else
	#define soco_dsa_API
#endif
