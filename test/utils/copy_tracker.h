//------------------------------------------------------------------------------
/**
 * @license
 * Copyright (c) Daniel Pauli <dapaulid@gmail.com>
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */
//------------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------
// includes
//------------------------------------------------------------------------------
//
// project
//
// C++
#include <memory>
//
//------------------------------------------------------------------------------
// class declaration
//------------------------------------------------------------------------------
//
class CopyTracker {
 public:
	//! constructor
	CopyTracker();
	//! destructor
	virtual ~CopyTracker();
	//! copy constructor
	CopyTracker(const CopyTracker& other);
	//! move constructor
	CopyTracker(CopyTracker&& other) noexcept;
	//! copy assignment
	CopyTracker& operator=(const CopyTracker& other);
	//! move assignment
	CopyTracker& operator=(CopyTracker&& other) noexcept;

	unsigned int get_copy_count() const;
	unsigned int get_move_count() const;
	unsigned int get_destroy_count() const;

	void print_copy_info() const;

 private:
	//! state shared by copies of the original instance
	struct State;
	std::shared_ptr<State> m_state;
};


//------------------------------------------------------------------------------
// end of file
