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

#include "GstDecoder.h"
#include "util/gstreamer/InjectablePipeline.h"
#include "util/gstreamer/RetrievablePipeline.h"
#include "util/gstreamer/VideoFormatToGstCaps.h"

namespace sfl {

GstDecoder::GstDecoder() throw (VideoDecodingException, MissingPluginException) :
	VideoDecoder(), injectableEnd(NULL), retrievableEnd(NULL) {
	currentCaps = gst_caps_new_simple("video/x-raw-rgb", "format",
			GST_TYPE_FOURCC, GST_MAKE_FOURCC('R', 'G', 'B', 'A'), "bpp",
			G_TYPE_INT, 32, "depth", G_TYPE_INT, 32, NULL);
}

GstDecoder::GstDecoder(VideoFormat& format) throw (VideoDecodingException,
		MissingPluginException) :
	VideoDecoder(), outputVideoFormat(format), injectableEnd(NULL),
			retrievableEnd(NULL) {
	// FIXME VideoFormat not taken into account.
	currentCaps = gst_caps_new_simple("video/x-raw-rgb", "format",
			GST_TYPE_FOURCC, GST_MAKE_FOURCC('R', 'G', 'B', 'A'), "bpp",
			G_TYPE_INT, 32, "depth", G_TYPE_INT, 32, NULL);
}

void GstDecoder::setParameter(const std::string& name, const std::string& value) {
	if (injectableEnd == NULL) {
		_debug ("Pushing parameter in list since injectableEnd is null");
		parameters.push_back(std::pair<std::string, std::string>(name, value));
	} else {
		injectableEnd->setField(name, value);
	}
}

std::string GstDecoder::getParameter(const std::string& name) {
	return injectableEnd->getField(name);
}

void GstDecoder::init() throw (VideoDecodingException, MissingPluginException) {
	gst_init(0, NULL);

	// Create the encoding portion of the pipeline
	// TODO catch exceptions
	Pipeline pipeline(std::string("sfl_") + getMimeSubtype() + std::string(
			"_decoding"));
	pipeline.setPrefix("sfl_decoder_");

	// Ask the derived child to take care of building the encoding portion of the pipeline itself. A knowledge that we
	// can't have at this point in the object hierarchy (template design pattern).
	buildFilter(pipeline);

	//    pipeline.addTee ("main_tee", getTail());
	//    GstPad* debugBranch = pipeline.branch ("main_tee");
	//    GstElement* previous = pipeline.addElement ("queue", debugBranch);
	//    previous = pipeline.addElement ("ffmpegcolorspace", previous);
	//    previous = pipeline.addElement ("deinterlace", previous);
	//    pipeline.addElement ("autovideosink", previous);
	//    GstPad* outputBranch = pipeline.branch ("main_tee");
	GstElement* previous = pipeline.addElement("ffmpegcolorspace", getTail());
	GstElement* capsfilter = pipeline.addElement("capsfilter", previous);

	// Add injectable endpoint
	std::ostringstream caps;
	caps << "application/x-rtp," << "media=(string)video,"
			<< "encoding-name=(string)" << getMimeSubtype() << ","
			<< "clock-rate=(int)" << getClockRate() << "," << "payload=(int)"
			<< (int) getPayloadType();

	GstCaps* sourceCaps = gst_caps_from_string((caps.str()).c_str());
	_debug ("Setting caps %s on decoder source", caps.str().c_str());

	injectableEnd = new InjectablePipeline(pipeline, sourceCaps);

	// If there are any optional parameters that were added before activate()
	// was called, apply them now.
	std::list<std::pair<std::string, std::string> >::iterator it;
	_debug ("Unwinding parameters ...");

	for (it = parameters.begin(); it != parameters.end(); it++) {
		injectableEnd->setField((*it).first, (*it).second);
	}

	// Add retrievable endpoint
	retrievableEnd = new RetrievablePipeline(pipeline);
	outputObserver = new PipelineEventObserver(this);
	retrievableEnd->addObserver(outputObserver);

	// Color space transform to RGBA if needed
	g_object_set(G_OBJECT(capsfilter), "caps", currentCaps, NULL);

	// Connect both endpoints to the graph.
	injectableEnd->setSink(getHead());
	retrievableEnd->setSource(capsfilter);
}

GstDecoder::~GstDecoder() {
	deactivate();

	delete retrievableEnd;
	delete injectableEnd;
}

void GstDecoder::decode(Buffer<uint8>& data) throw (VideoDecodingException) {
	//_debug ("Decoding RTP packet ...");

	// Convert the raw decrypted packet to a GstBuffer that can be sent downstream in the pipeline.
	// TODO Figure out if we can avoid copying the data.
	GstBuffer* buffer = gst_rtp_buffer_new_copy_data(data.getBuffer(),
			data.getSize());

	// This function takes ownership of the buffer.
	injectableEnd->inject(buffer);
}

void GstDecoder::setOutputFormat(VideoFormat& format) {
	_debug("Setting output format on decoder to %s", format.toString().c_str());
	VideoFormatToGstCaps convert;
	retrievableEnd->setCaps(convert(format));
}

VideoFormat GstDecoder::getOutputFormat() {
	// Extract the colospace, width and height from caps
	_debug ("caps are %" GST_PTR_FORMAT, currentCaps);

	GstStructure* structure = gst_caps_get_structure(currentCaps, 0);

	guint32 fourcc;
	gst_structure_get_fourcc(structure, "format", &fourcc);

	gint width;
	gst_structure_get_int (structure, "width", &width);

	gint height;
	gst_structure_get_int (structure, "height", &height);

	// Extract the mime type
	const gchar* mimetype = gst_structure_get_name(structure);

	// Extract the framerate
	int fps_n = 1;
	int fps_d = 1;
	gst_structure_get_fraction (structure, "framerate", &fps_n, &fps_d);

	VideoFormat videoFormat;
	videoFormat.setFourcc(fourcc);
	videoFormat.setWidth(width);
	videoFormat.setHeight(height);
	videoFormat.setMimetype(std::string(mimetype));
	videoFormat.setFramerate(fps_n, fps_d);

	_debug("Fourcc format is %d", fourcc);

	return videoFormat;
}

void GstDecoder::activate() {
	_info ("Activating decoder");

	init();

	// Does not matter whether we call start() on injectable or retrievable endpoints.
	injectableEnd->start();
}

void GstDecoder::deactivate() {
	_info ("Deactivating gstreamer decoder");

	// Clear our own observers
	clearObservers();

	// Unsubscribe this object from appsink events.
	retrievableEnd->removeObserver(outputObserver);

	// Does not matter whether we call stop() on injectable or retrievable endpoints.
	retrievableEnd->stop();

	// Clear the parameter set
	parameters.clear();
}

}