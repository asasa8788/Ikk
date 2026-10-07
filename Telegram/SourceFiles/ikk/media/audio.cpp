#include "ikk/media/audio.h"

#include "ikk/media/backend_options.h"

namespace Ikk::Media {

int VoiceRecordBitrate(int fallback) {
	return VoiceRecordBitrate(ForDevice(), fallback);
}

bool GroupCallRawAudio() {
	return ForDevice().Get(kGroupCallRawAudio);
}

} // namespace Ikk::Media
