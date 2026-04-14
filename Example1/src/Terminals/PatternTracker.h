// ANONYS FINITE STATE MACHINE FRAMEWORK
// Copyright (c) 2026 Jan Hofmann <anonys@noloops.ch>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://apache.org

#ifndef EXAMPLE1_TERMINALS_PATTERNTRACKER_H
#define EXAMPLE1_TERMINALS_PATTERNTRACKER_H

namespace terminals {

	class PatternTracker {
	public:
		void setPattern1() { m_isPattern1 = true; }
		void setPattern2() { m_isPattern1 = false; }
		bool isPattern1() const { return m_isPattern1; }

	private:
		bool m_isPattern1{ true };
	};

}

#endif // EXAMPLE1_TERMINALS_PATTERNTRACKER_H
