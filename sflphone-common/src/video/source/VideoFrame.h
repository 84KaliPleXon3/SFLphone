/*
 *  Copyright (C) 2010 Savoir-Faire Linux inc.
 *  Author: Pierre-Luc Bacon <pierre-luc.bacon@savoirfairelinux.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#ifndef __SFL_VIDEO_FRAME_H__
#define __SFL_VIDEO_FRAME_H__

#include "logger.h"
#include <stdint.h>
#include <string.h>

namespace sfl
{
/**
 * This class represents a captured frame.
 */
class VideoFrame
{
    public:
        /**
         * @param frame The frame data.
         * @param size The frame size.
         * @param height The frame height.
         * @param width The frame width.
         */
        VideoFrame (const uint8_t* frame, const size_t size, unsigned int depth,
                    unsigned int height, unsigned int width);

        ~VideoFrame();

        /**
         * @return The frame data.
         */
        const uint8_t *getFrame() const {
            return frame;
        }
        /**
         * @return The frame height.
         */
        unsigned int getHeight() const {
            return height;
        }

        /**
         * @return The frame width.
         */
        unsigned int getWidth() const {
            return width;
        }

        /**
         * @return The frame depth in bytes (eg: 3 bytes)
         */
        unsigned int getDepth() const {
            return depth;
        }

        /**
         * @return The buffer size.
         */
        size_t getSize() const {
            return size;
        }

    private:
        uint8_t* frame;
        size_t size;
        unsigned int height;
        unsigned int width;
        unsigned int depth;
};
}
#endif