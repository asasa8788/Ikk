#pragma once

#include "ikk/core/options.h"

namespace Ikk::Media {

inline constexpr auto kStickerScale = Option<int>{
	"ikk.stickerScale", Scope::Device, 100,
	Category::Media, "lng_ikk_sticker_scale",
	static_cast<unsigned>(Flag::RefreshMessageView),
	[](const int &value) {
		return value >= 50 && value <= 200 && value % 25 == 0;
	} };
inline constexpr auto kHideStickerTime = Option<bool>{
	"ikk.hideStickerTime", Scope::Device, false,
	Category::Media, "lng_ikk_hide_sticker_time",
	static_cast<unsigned>(Flag::RefreshMessageView) };
inline constexpr auto kRecentStickerLimit = Option<int>{
	"ikk.recentStickerLimit", Scope::Device, 0,
	Category::Media, "lng_ikk_recent_sticker_limit", 0,
	[](const int &value) { return value >= 0 && value <= 200; } };
inline constexpr auto kHideGroupStickers = Option<bool>{
	"ikk.hideGroupStickers", Scope::Device, false,
	Category::Media, "lng_ikk_hide_group_stickers" };
inline constexpr auto kHideRecommendedStickers = Option<bool>{
	"ikk.hideRecommendedStickers", Scope::Device, false,
	Category::Media, "lng_ikk_hide_recommended_stickers" };
inline constexpr auto kHideRecommendedEmoji = Option<bool>{
	"ikk.hideRecommendedEmoji", Scope::Device, false,
	Category::Media, "lng_ikk_hide_recommended_emoji" };
inline constexpr auto kHideGifCategories = Option<bool>{
	"ikk.hideGifCategories", Scope::Device, false,
	Category::Media, "lng_ikk_hide_gif_categories" };
inline constexpr auto kHideGreetingSticker = Option<bool>{
	"ikk.hideGreetingSticker", Scope::Device, false,
	Category::Media, "lng_ikk_hide_greeting_sticker" };
inline constexpr auto kDisableVideoAutoplay = Option<bool>{
	"ikk.disableVideoAutoplay", Scope::Device, false,
	Category::Media, "lng_ikk_disable_video_autoplay",
	static_cast<unsigned>(Flag::RefreshMessageView) };
inline constexpr auto kGifPlaybackControls = Option<bool>{
	"ikk.gifPlaybackControls", Scope::Device, false,
	Category::Media, "lng_ikk_gif_playback_controls" };
inline constexpr auto kMp4FilePreview = Option<bool>{
	"ikk.mp4FilePreview", Scope::Device, false,
	Category::Media, "lng_ikk_mp4_file_preview" };

inline constexpr auto kSmallGifs = Option<bool>{
	"ikk.smallGifs", Scope::Device, false,
	Category::Media, "lng_ikk_small_gifs",
	static_cast<unsigned>(Flag::RefreshMessageView) };
inline constexpr auto kStickerPanelScale = Option<int>{
	"ikk.stickerPanelScale", Scope::Device, 100,
	Category::Media, "lng_ikk_sticker_panel_scale",
	static_cast<unsigned>(Flag::RequiresRestart),
	[](const int &value) {
		return value >= 50 && value <= 200 && value % 25 == 0;
	} };
inline constexpr auto kDownloadsInMainMenu = Option<bool>{
	"ikk.downloadsInMainMenu", Scope::Device, false,
	Category::Media, "lng_ikk_downloads_in_main_menu" };
inline constexpr auto kBlockExecutableAutoDownload = Option<bool>{
	"ikk.blockExecutableAutoDownload", Scope::Device, false,
	Category::Media, "lng_ikk_block_executable_auto_download" };
inline constexpr auto kBlockArchiveAutoDownload = Option<bool>{
	"ikk.blockArchiveAutoDownload", Scope::Device, false,
	Category::Media, "lng_ikk_block_archive_auto_download" };

inline void RegisterOptions(Registry &registry) {
	Expects(registry.Add(kStickerScale));
	Expects(registry.Add(kHideStickerTime));
	Expects(registry.Add(kRecentStickerLimit));
	Expects(registry.Add(kHideGroupStickers));
	Expects(registry.Add(kHideRecommendedStickers));
	Expects(registry.Add(kHideRecommendedEmoji));
	Expects(registry.Add(kHideGifCategories));
	Expects(registry.Add(kHideGreetingSticker));
	Expects(registry.Add(kDisableVideoAutoplay));
	Expects(registry.Add(kGifPlaybackControls));
	Expects(registry.Add(kMp4FilePreview));
	Expects(registry.Add(kSmallGifs));
	Expects(registry.Add(kStickerPanelScale));
	Expects(registry.Add(kDownloadsInMainMenu));
	Expects(registry.Add(kBlockExecutableAutoDownload));
	Expects(registry.Add(kBlockArchiveAutoDownload));
}

} // namespace Ikk::Media
