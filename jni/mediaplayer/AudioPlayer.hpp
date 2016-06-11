/*
 * AudioPlayer.hpp
 *
 *  Created on: 2016��6��9��
 *      Author: loushuai
 */

#ifndef JNI_MEDIAPLAYER_AUDIOPLAYER_H_
#define JNI_MEDIAPLAYER_AUDIOPLAYER_H_

#include <memory>
#include "mediabase/MediaCodec.hpp"
#include "mediasink/audiosink/opensl/openslsink.hpp"

namespace whitebean {

class AudioPlayer {
public:
	AudioPlayer() {}
	~AudioPlayer() {}

	void setSource(std::shared_ptr<MediaSource> source);
	int start();
private:
	static size_t audioSinkCallBack(std::unique_ptr<uint8_t[]> &buf, void *cookie = nullptr);
	size_t fillBuffer(std::unique_ptr<uint8_t[]> &buf);
	
	MediaDecoder mDecoder;
	std::shared_ptr<MediaSource> mSourcePtr;
	std::shared_ptr<AudioSink> mSinkPtr;
	
};
	
}

#endif