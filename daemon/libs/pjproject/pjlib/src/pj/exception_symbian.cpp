/* $Id: exception_symbian.cpp 2394 2008-12-23 17:27:53Z bennylp $ */
/*
 * Copyright (C) 2008-2009 Teluu Inc. (http://www.teluu.com)
 * Copyright (C) 2003-2008 Benny Prijono <benny@prijono.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  Additional permission under GNU GPL version 3 section 7:
 *
 *  If you modify this program, or any covered work, by linking or
 *  combining it with the OpenSSL project's OpenSSL library (or a
 *  modified version of that library), containing parts covered by the
 *  terms of the OpenSSL or SSLeay licenses, Teluu Inc. (http://www.teluu.com)
 *  grants you additional permission to convey the resulting work.
 *  Corresponding Source for a non-source form of such a combination
 *  shall include the source code for the parts of OpenSSL used as well
 *  as that of the covered work.
 */
#include <pj/except.h>
#include <pj/os.h>
#include <pj/assert.h>
#include <pj/log.h>
#include <pj/errno.h>


#if defined(PJ_HAS_EXCEPTION_NAMES) && PJ_HAS_EXCEPTION_NAMES != 0
static const char *exception_id_names[PJ_MAX_EXCEPTION_ID];
#else
/*
 * Start from 1 (not 0)!!!
 * Exception 0 is reserved for normal path of setjmp()!!!
 */
static int last_exception_id = 1;
#endif  /* PJ_HAS_EXCEPTION_NAMES */


#if defined(PJ_HAS_EXCEPTION_NAMES) && PJ_HAS_EXCEPTION_NAMES != 0
PJ_DEF (pj_status_t) pj_exception_id_alloc (const char *name,
        pj_exception_id_t *id)
{
    unsigned i;

    pj_enter_critical_section();

    /*
     * Start from 1 (not 0)!!!
     * Exception 0 is reserved for normal path of setjmp()!!!
     */
    for (i=1; i<PJ_MAX_EXCEPTION_ID; ++i) {
        if (exception_id_names[i] == NULL) {
            exception_id_names[i] = name;
            *id = i;
            pj_leave_critical_section();
            return PJ_SUCCESS;
        }
    }

    pj_leave_critical_section();
    return PJ_ETOOMANY;
}

PJ_DEF (pj_status_t) pj_exception_id_free (pj_exception_id_t id)
{
    /*
     * Start from 1 (not 0)!!!
     * Exception 0 is reserved for normal path of setjmp()!!!
     */
    PJ_ASSERT_RETURN (id>0 && id<PJ_MAX_EXCEPTION_ID, PJ_EINVAL);

    pj_enter_critical_section();
    exception_id_names[id] = NULL;
    pj_leave_critical_section();

    return PJ_SUCCESS;

}

PJ_DEF (const char*) pj_exception_id_name (pj_exception_id_t id)
{
    /*
     * Start from 1 (not 0)!!!
     * Exception 0 is reserved for normal path of setjmp()!!!
     */
    PJ_ASSERT_RETURN (id>0 && id<PJ_MAX_EXCEPTION_ID, "<Invalid ID>");

    if (exception_id_names[id] == NULL)
        return "<Unallocated ID>";

    return exception_id_names[id];
}

#else   /* PJ_HAS_EXCEPTION_NAMES */
PJ_DEF (pj_status_t) pj_exception_id_alloc (const char *name,
        pj_exception_id_t *id)
{
    PJ_ASSERT_RETURN (last_exception_id < PJ_MAX_EXCEPTION_ID-1, PJ_ETOOMANY);

    *id = last_exception_id++;
    return PJ_SUCCESS;
}

PJ_DEF (pj_status_t) pj_exception_id_free (pj_exception_id_t id)
{
    return PJ_SUCCESS;
}

PJ_DEF (const char*) pj_exception_id_name (pj_exception_id_t id)
{
    return "";
}

#endif  /* PJ_HAS_EXCEPTION_NAMES */



