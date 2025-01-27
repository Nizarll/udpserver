#pragma once
#include <iostream>
#include <cstdlib>

#define ANSI_RED     "\033[31m"
#define ANSI_GREEN   "\033[32m"
#define ANSI_RESET   "\033[0m"
#define ANSI_RED "\033[31m"
#define ANSI_RESET "\033[0m"

#ifdef __WIN32
#define DBG_TOK _DEBUG
#else
#define DBG_TOK DEBUG
#endif

namespace logger {
	template <typename... Args>
	void error_recurse(Args&&... args)
	{
		if constexpr (sizeof...(args) > 0) {
			//std::cout << args... << " ";
			(std::cout << ... << args);
		}
	}
	template <typename... Args>
	inline void error(Args&&... args)
	{
#ifdef DBG_TOK
		std::cout << ANSI_RED "[!] error: ";//TODO:
		error_recurse(std::forward<Args>(args)...);
		std::cout << ANSI_RESET << '\n' << std::flush;
#endif
	}
	template <typename... Args>
  inline void fatal(Args&&... args)
  {
    error(std::forward<Args>(args)...);
    std::exit(-1);
  }
};
