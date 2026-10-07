#pragma once

#include "ikk/core/options.h"
#include "ikk/media/url_template.h"
#include "ikk/media/sticker_export_model.h"

namespace Ikk::Media {

[[nodiscard]] constexpr bool ValidVoiceBitrate(const int &value) {
	return value == 0 || value == 16 || value == 24 || value == 48
		|| value == 64 || value == 96 || value == 128;
}

inline constexpr auto kVoiceRecordBitrate = Option<int>{
	"ikk.voiceRecordBitrate", Scope::Device, 0,
	Category::Media, "lng_ikk_voice_record_bitrate", 0,
	ValidVoiceBitrate };

inline constexpr auto kGroupCallRawAudio = Option<bool>{
	"ikk.groupCallRawAudio", Scope::Device, false,
	Category::Media, "lng_ikk_group_call_raw_audio" };

inline const auto kMusicCoverUrl = Option<QString>{
	"ikk.musicCoverUrl", Scope::Device, QString(),
	Category::Media, "lng_ikk_music_cover_url",
	static_cast<unsigned>(Flag::Hidden), ValidCoverUrl };

inline const auto kStickerExportPath = Option<QString>{
	"ikk.stickerExportPath", Scope::Device, QString(),
	Category::Media, "lng_ikk_sticker_export_path",
	static_cast<unsigned>(Flag::Hidden), ValidExportPath };
inline constexpr auto kStickerExportAutoSync = Option<bool>{
	"ikk.stickerExportAutoSync", Scope::Device, false,
	Category::Media, "lng_ikk_sticker_export_auto_sync" };
inline constexpr auto kStickerExportDirNaming = Option<int>{
	"ikk.stickerExportDirNaming", Scope::Device, 0,
	Category::Media, "lng_ikk_sticker_export_dir_naming", 0,
	ValidExportDirNaming };

[[nodiscard]] constexpr int ResolveVoiceBitrate(int kbps, int fallback) {
	return (kbps > 0 && ValidVoiceBitrate(kbps)) ? (kbps * 1000) : fallback;
}

[[nodiscard]] inline int VoiceRecordBitrate(Options &options, int fallback) {
	return ResolveVoiceBitrate(options.Get(kVoiceRecordBitrate), fallback);
}

[[nodiscard]] inline QString CoverRequestUrl(
		Options &options,
		const QString &artist,
		const QString &title) {
	const auto address = options.Get(kMusicCoverUrl);
	return address.isEmpty()
		? QString()
		: ExpandCoverUrl(address, artist, title);
}

inline void RegisterBackendOptions(Registry &registry) {
	Expects(registry.Add(kVoiceRecordBitrate));
	Expects(registry.Add(kGroupCallRawAudio));
	Expects(registry.Add(kMusicCoverUrl));
	Expects(registry.Add(kStickerExportPath));
	Expects(registry.Add(kStickerExportAutoSync));
	Expects(registry.Add(kStickerExportDirNaming));
}

} // namespace Ikk::Media
