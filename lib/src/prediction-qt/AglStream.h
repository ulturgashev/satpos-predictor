#pragma once

#include <iostream>

namespace Core
{
	class Almanach;

	class AglStream
	{
	public:
		explicit AglStream(std::istream &stream);
		~AglStream() = default;

		std::istream &operator>>(Almanach &almanach);

#if 0	// TODO: Реализовать.
		std::istream &operator<<(Almanach &almanach);
#endif

		operator bool() const;

	private:
		std::istream &stream_;
	};
}
