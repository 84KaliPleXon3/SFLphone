/* $Id: scanner_cis_uint.h 2394 2008-12-23 17:27:53Z bennylp $ */
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
#ifndef __PJLIB_UTIL_SCANNER_CIS_BIT_H__
#define __PJLIB_UTIL_SCANNER_CIS_BIT_H__

#include <pj/types.h>

PJ_BEGIN_DECL

/**
 * This describes the type of individual character specification in
 * #pj_cis_buf_t. Basicly the number of bits here
 */
#ifndef PJ_CIS_ELEM_TYPE
#   define PJ_CIS_ELEM_TYPE int
#endif

/**
 * This describes the type of individual character specification in
 * #pj_cis_buf_t.
 */
typedef PJ_CIS_ELEM_TYPE pj_cis_elem_t;

/** pj_cis_buf_t is not used when uint back-end is used. */
typedef int pj_cis_buf_t;

/**
 * Character input specification.
 */
typedef struct pj_cis_t
{
    PJ_CIS_ELEM_TYPE	cis_buf[256];	/**< Internal buffer.	*/
} pj_cis_t;


/**
 * Set the membership of the specified character.
 * Note that this is a macro, and arguments may be evaluated more than once.
 *
 * @param cis       Pointer to character input specification.
 * @param c         The character.
 */
#define PJ_CIS_SET(cis,c)   ((cis)->cis_buf[(int)(c)] = 1)

/**
 * Remove the membership of the specified character.
 * Note that this is a macro, and arguments may be evaluated more than once.
 *
 * @param cis       Pointer to character input specification.
 * @param c         The character to be removed from the membership.
 */
#define PJ_CIS_CLR(cis,c)   ((cis)->cis_buf[(int)c] = 0)

/**
 * Check the membership of the specified character.
 * Note that this is a macro, and arguments may be evaluated more than once.
 *
 * @param cis       Pointer to character input specification.
 * @param c         The character.
 */
#define PJ_CIS_ISSET(cis,c) ((cis)->cis_buf[(int)c])



PJ_END_DECL

#endif	/* __PJLIB_UTIL_SCANNER_CIS_BIT_H__ */