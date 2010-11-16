/*
 * This file is part of TelepathyQt4
 *
 * Copyright (C) 2010 Collabora Ltd. <http://www.collabora.co.uk/>
 * Copyright (C) 2010 Nokia Corporation
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef _TelepathyQt4_not_filter_h_HEADER_GUARD_
#define _TelepathyQt4_not_filter_h_HEADER_GUARD_

#ifndef IN_TELEPATHY_QT4_HEADER
#error IN_TELEPATHY_QT4_HEADER
#endif

#include <TelepathyQt4/Filter>
#include <TelepathyQt4/Types>

namespace Tp
{

template <class T>
class NotFilter : public Filter<T>
{
public:
    static SharedPtr<NotFilter<T> > create(
            const SharedPtr<const Filter<T> > &filter = SharedPtr<const Filter<T> >())
    {
        return SharedPtr<NotFilter<T> >(new NotFilter<T>(filter));
    }

    inline virtual ~NotFilter() { }

    inline virtual bool isValid() const
    {
        return mFilter && mFilter->isValid();
    }

    inline virtual bool matches(const SharedPtr<T> &t) const
    {
        if (!isValid()) {
            return false;
        }

        return !mFilter->matches(t);
    }

    inline SharedPtr<const Filter<T> > filter() const { return mFilter; }

private:
    NotFilter(const SharedPtr<const Filter<T> > &filter)
        : Filter<T>(), mFilter(filter) { }

    SharedPtr<const Filter<T> > mFilter;
};

} // Tp

#endif
