/*
 * armstrong-ide
 * Copyright (C) 2010 Saleem Ansari <tuxdna@gmail.com>
 *
 * Armstrong-IDE is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Armstrong-IDE is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifndef __ITERABLE__
#define __ITERABLE__

#include <glibmm.h>

namespace armstrong {

/**
 * @title: Iterable
 * @short_description: Implemented by objects that can iterate
 */

class Iterable {
public:
	// default vritual destructor
	virtual ~Iterable() {
	}

	/**
	 * Set iter to first element position. Returns FALSE if
	 * there is no element in the iterable (hence does not have first).
	 * The iter points to the first valid item.
	 * Returns: TRUE if sucessful, other FALSE.
	 */
	virtual gboolean first() = 0;

	/**
	 * Set the iter position to next element position. Iter can go until one
	 * item past the last item and lands in end-iter. end-iter does not point
	 * to any valid item and signifies end of the list. Returns FALSE if iter
	 * was already at end-iter (iter can not go past it) and remains pointed
	 * to the end-iter.
	 * Returns: TRUE if sucessful, otherwise FALSE if already at end-iter.
	 */
	virtual gboolean next() = 0;

	/**
	 * Set the iter position to previous element position. Returns FALSE if
	 * there is no previous element and the iter remains pointed to the first
	 * element.
	 * Returns: TRUE if sucessful, other FALSE.
	 */
	virtual gboolean previous() = 0;

	/**
	 * Set iter position to end-iter (one past last element) position.
	 * Returns FALSE if there is no element in the iterable (already
	 * at end-iter).
	 * Returns: TRUE if sucessful, other FALSE.
	 */
	virtual gboolean last() = 0;

	/**
	 * Call callback for each element in the list. Call back is passed the
	 * same iter, but with different position set (from first to last). This
	 * method does not affect current position. i.e. current position is
	 * restored at the end of this method.
	 * @callback: Callback to call for each element.
	 * @user_data: user data that is passed back to the callback.
	 */
	virtual void foreach(GFunc callback, gpointer user_data) = 0;

	/**
	 * Sets the current position of the iter to @position. The given @position
	 * must be from 0 to length - 1 (get_length()) to point to
	 * a valid element. Passing @position < 0 will set it to end-iter. It
	 * returns TRUE for the above cases. FLASE will be returned, if
	 * out-of-range @position is passed (@position > length - 1) and iter is
	 * set to end-iter.
	 * @position: New position for the iter.
	 * Returns: TRUE if successfully set (i.e. @position is within the range or
	 * end-iter). otherwise returns FALSE (i.e. @position is out of data range).
	 */
	virtual gboolean set_position(gint position) = 0;

	/**
	 * Index of the current iter in the iterable. It will be
	 * from 0 to length - 1 (get_length()) if iter is pointed
	 * at valid element. It will return -1 if iter is pointed at end-iter.
	 * Returns: integer index, or -1 for end-iter.
	 */
	virtual gint get_position() = 0;

	/**
	 * Length of the iterable (number of elements indexable by it).
	 * Returns: total length of the list.
	 */
	virtual gint get_length() = 0;

	/**
	 * Clones the iterable. The returned iterable object must be unreffed
	 * when done.
	 * Returns: A new instance of this iterable pointing at the same location.
	 */
	virtual Iterable *clone() = 0;

	/**
	 * Assigns the iter position from @src_iter.
	 * @src_iter: Source iter from which to copy the assignment.
	 */
	virtual void assign(Iterable *src_iter) = 0;

	/**
	 * Compares the position of @iter2 with this @obj. Returns -1
	 * value if this @obj is smaller than @iter2. Returns +1 value
	 * if this @obj is larger than @iter2. And returns 0 if both are equal.
	 * If you want difference of the iter positions, use
	 * #iterable_diff(). This method is meant for fast comparision.
	 * @iter2: Second iter to compare.
	 * Returns: 0 if equal, -1 if @obj is smaller than @iter2
	 * or +1 if @obj is larger than @iter2.
	 *
	 */
	virtual gint compare(Iterable *iter2) = 0;

	/**
	 * Compares the position of @iter2 with this @obj and returns difference
	 * in position of the two (@obj - @iter2).
	 * @iter2: Second iter to differenciate.
	 * @err: Error propagation and reporting
	 * Returns: The position difference of @obj - @iter2
	 */
	virtual gint diff(Iterable *iter2) = 0;

};
/**
 * @title: IterableTree
 * @short_description: Implemented by tree objects that can iterate
 */

class IterableTree: public Iterable {
public:
	// default virtual destructor
	virtual ~IterableTree() {
	}

	/**
	 * Set iter position to parent of curernt iter. If there is no parent,
	 * returns FALSE (current iter position is not changed)
	 * Returns: TRUE if sucessful, otherwise FALSE.
	 */
	virtual gboolean parent() = 0;

	/**
	 * Iter position set to first child of current iter. If there is no
	 * children, return NULL (iter position is not changed).
	 * Returns: TRUE if sucessful, otherwise FALSE.
	 */
	virtual gboolean children() = 0;

	/**
	 * @err: Error propagation and reporting
	 *
	 * Returns true if current iter has children
	 *
	 * Returns: TRUE if there are children, otherwise FALSE.
	 */
	virtual gboolean has_children() = 0;

	/**
	 * @callback: Callback to call for each element.
	 * @user_data: User data to pass back to callback.
	 * @err: Error propagation and reporting
	 *
	 * Call callback for each element in post order.
	 */
	virtual void foreach_post(GFunc callback, gpointer user_data) = 0;

	/**
	 * @callback: Callback to call for each element.
	 * @user_data: User data to pass back to callback.
	 * @err: Error propagation and reporting
	 *
	 * Call callback for each element in pre order.
	 */
	virtual void foreach_pre(GFunc callback, gpointer user_data) = 0;
};

}
;

#endif
