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


#ifndef __I_PROVIDER__
#define __I_PROVIDER__


#include "Iterable.h"

namespace armstrong {

  /**
   * @short_description: Provider for autocompletion features
   */

  class IProvider
  {
  public:
    // default virtual destructor
    virtual ~IProvider() {}

    /**
     * @iter: the text iter where the provider should be populated
     *
     * Show completion for the context at position @iter. The provider should
     * call assist_proposals here to add proposals to the list.
     *
     * Note that this is called after every character typed and the list of proposals
     * has to be completely renewed.
     */
    virtual void populate(Iterable* iter) = 0;

    /**
     * Get the iter where the current completion started
     *
     * Returns: current start iter
     */
    virtual Iterable* get_start_iter() = 0;

    /**
     * @iter: position where the completion occurs
     * @data: data assigned to the proposal
     *
     * Show completion for the context at position @iter
     */
    virtual void activate(Iterable* iter, gpointer data) = 0;

    /**
     * Return a (translatable) name for the provider
     */
    virtual const gchar* get_name() = 0;

  };
};

#endif
