//------------------------------------------------------------------------------
/**
 * @license
 * Copyright (c) Daniel Pauli <dapaulid@gmail.com>
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
//
// project
#include "copy_tracker.h"
//
// C++
#include <utility>
#include <atomic>
#include <iostream>
//
//------------------------------------------------------------------------------
// struct definition
//------------------------------------------------------------------------------
//
struct CopyTracker::State {
	std::atomic_uint copy_count {};
	std::atomic_uint move_count {};
	std::atomic_uint destroy_count {};
};

//------------------------------------------------------------------------------
// class definition
//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
//! constructor
//
CopyTracker::CopyTracker():
	m_state(std::make_shared<State>())
{
}

//------------------------------------------------------------------------------
//! destructor
//
CopyTracker::~CopyTracker()
{
	std::cout << "destroyed" << std::endl;
	m_state->destroy_count++;
}

//------------------------------------------------------------------------------
//! copy constructor
//
CopyTracker::CopyTracker(const CopyTracker& other):
	m_state(other.m_state)
{
	std::cout << "copied" << std::endl;
	m_state->copy_count++;
}

//------------------------------------------------------------------------------
//! move constructor
//
CopyTracker::CopyTracker(CopyTracker&& other) noexcept:
	m_state(other.m_state)
{
	std::cout << "moved" << std::endl;
	m_state->move_count++;
}

//------------------------------------------------------------------------------
//! copy assignment
//
CopyTracker& CopyTracker::operator=(const CopyTracker& other)
{
	m_state = other.m_state;
	std::cout << "copied" << std::endl;
	m_state->copy_count++;
	return *this;
}

//------------------------------------------------------------------------------
//! move assignment
//
CopyTracker& CopyTracker::operator=(CopyTracker&& other) noexcept
{
	m_state = other.m_state;
	std::cout << "moved" << std::endl;
	m_state->move_count++;
	return *this;
}

//------------------------------------------------------------------------------
//
unsigned int CopyTracker::get_copy_count() const
{
	return m_state->copy_count;
}

//------------------------------------------------------------------------------
//
unsigned int CopyTracker::get_move_count() const
{
	return m_state->move_count;
}

//------------------------------------------------------------------------------
//
unsigned int CopyTracker::get_destroy_count() const
{
	return m_state->destroy_count;
}

//------------------------------------------------------------------------------
//
void CopyTracker::print_copy_info() const
{
	std::cout << "copied: " << get_copy_count()
		<< ", moved: " << get_move_count()
		<< ", destroyed: " << get_destroy_count()
		<< std::endl;
}

//------------------------------------------------------------------------------
// end of file
