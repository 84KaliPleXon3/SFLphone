/*
 *  Copyright (C) 2004, 2005, 2006, 2009, 2008, 2009, 2010 Savoir-Faire Linux Inc.
 *  Author: Pierre-Luc Bacon <pierre-luc.bacon@savoirfairelinux.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *  Additional permission under GNU GPL version 3 section 7:
 *
 *  If you modify this program, or any covered work, by linking or
 *  combining it with the OpenSSL project's OpenSSL library (or a
 *  modified version of that library), containing parts covered by the
 *  terms of the OpenSSL or SSLeay licenses, Savoir-Faire Linux Inc.
 *  grants you additional permission to convey the resulting work.
 *  Corresponding Source for a non-source form of such a combination
 *  shall include the source code for the parts of OpenSSL used as well
 *  as that of the covered work.
 */
#ifndef __SFL_OBSERVERVABLE_H__
#define __SFL_OBSERVERABLE_H__

#include "Observer.h"

namespace sfl {
/**
 * Interface for an Observable type.
 */
template<class T>
class Observable {
public:
	/**
	 * @param observer The observer object to be notify by this observable object.
	 */
	void addObserver(Observer* observer);

	/**
	 * @param observer The observer object to be removed.
	 */
	void removeObserver(Observer* observer);

	/**
	 * @param data The data to be pushed to the observers.
	 */
	void notifyAll(T data);

protected:
	/**
	 * This method must be overridden by the user, as in the template design pattern.
	 * It will get called by notifyAll()
	 * @see AbstractObservable#notifyAll
	 */
	virtual void notify(Observer* observer, T data) = 0;
};
}
#endif