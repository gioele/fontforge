/******************************************************************************
*******************************************************************************
*******************************************************************************

    Copyright (C) 2013 Ben Martin
    
    This file is part of FontForge.

    FontForge is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation,either version 3 of the License, or
    (at your option) any later version.

    FontForge is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FontForge.  If not, see <http://www.gnu.org/licenses/>.

    For more details see the COPYING.gplv3 file in the root directory of this
    distribution.

*******************************************************************************
*******************************************************************************
******************************************************************************/

#ifndef FONTFORGEEXE_SFUNDO_H
#define FONTFORGEEXE_SFUNDO_H

#include "splinefont.h"

enum sfundotype
{
    sfut_none=0,
    sfut_lookups,
    sfut_lookups_kerns,
    sfut_fontinfo,
    sfut_noop
};

/**
 * A spline font level undo stack. undoes are doubly linked using the
 * 'ln' member and carry some user presentable description of what the
 * undo relates to in 'msg'.
 *
 * The sfdchunk is a pointer to an SFD fragment which will apply the
 * undo to the current state. For example, it might contain
 * information about the old value of kerning pairs which can be used
 * to restore state to how it was. Note that the sfdchunk might only
 * be partial, containing only enough information to restore the state
 * which changed when the undo was created.
 */
typedef struct sfundoes {
    struct dlistnode ln;
    char* msg;
    enum sfundotype type;
    union {
	int dummy;
    } u;
    char* sfdchunk;
} SFUndoes;

void SFUndoFreeAssociated( struct sfundoes *undo );
void SFUndoFree( struct sfundoes *undo );
SFUndoes* SFUndoCreateSFD( enum sfundotype t, char* staticmsg, char* sfdfrag );

/**
 * Remove undo from the font level undoes on splinefont 'sf' and
 * completely free the given undo from memory.
 */
void SFUndoRemoveAndFree( SplineFont *sf, struct sfundoes *undo );


char* SFUndoToString( SFUndoes* undo );
SFUndoes* SFUndoFromString( char* str );

void SFUndoPerform( SFUndoes* undo, SplineFont* sf );
SFUndoes* SFUndoCreateRedo( SFUndoes* undo, SplineFont* sf );

void SFUndoPushFront( struct sfundoes ** undoes, SFUndoes* undo );

#endif /* FONTFORGEEXE_SFUNDO_H */
