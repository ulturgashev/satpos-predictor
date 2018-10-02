#include <iostream>

#include "Almanach.h"

#include "AglStream.h"

namespace Core
{
	AglStream::AglStream(std::istream &stream)
		: stream_(stream)
	{
	}

	std::istream &AglStream::operator>>(Almanach &almanach)
	{
		std::string buffer;

		std::getline(stream_, buffer);
		std::string first(buffer);

		std::getline(stream_, buffer);
		std::string second(buffer);

		std::getline(stream_, buffer);
		std::string third(buffer);

		almanach.initialize(first, second, third);

		return stream_;
	}

	Core::AglStream::operator bool() const
	{
		// TODO: Refactoring;
		if (stream_.eof()) {
			return false;
		}

		// Detect if there are tle lines, not read yet
		stream_.get();

		if (!stream_.good() || stream_.eof()) {
			return false;
		}

		stream_.unget();
		return true;
	}
}
