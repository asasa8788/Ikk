#pragma once

#include "ikk/core/options.h"

namespace Ikk::Chats {

inline constexpr auto kRefreshDialogList = static_cast<unsigned>(
	Flag::RefreshDialogList);

inline constexpr auto kCompactList = Option<bool>{
	"ikk.chatListCompact", Scope::Device, false,
	Category::Chats, "lng_ikk_compact_chat_list", kRefreshDialogList };
inline constexpr auto kPreviewLines = Option<int>{
	"ikk.chatPreviewLines", Scope::Device, 0,
	Category::Chats, "lng_ikk_chat_preview_lines", kRefreshDialogList,
	[](const int &value) { return value >= 0 && value <= 3; } };
inline constexpr auto kHideSavedAndArchivedPreviews = Option<bool>{
	"ikk.hideSavedAndArchivedPreviews", Scope::Device, false,
	Category::Chats, "lng_ikk_hide_saved_and_archived_previews",
	kRefreshDialogList };
inline constexpr auto kHideStories = Option<bool>{
	"ikk.hideStories", Scope::Device, false,
	Category::Chats, "lng_ikk_hide_stories" };
inline constexpr auto kHideAllChatsFolder = Option<bool>{
	"ikk.hideAllChatsFolder", Scope::Device, false,
	Category::Chats, "lng_ikk_hide_all_chats_folder" };
inline constexpr auto kShowArchiveInFolders = Option<bool>{
	"ikk.showArchiveInFolders", Scope::Device, false,
	Category::Chats, "lng_ikk_show_archive_in_folders",
	kRefreshDialogList };
inline constexpr auto kArchiveInFolderList = Option<bool>{
	"ikk.archiveInFolderList", Scope::Device, false,
	Category::Chats, "lng_ikk_archive_in_folder_list" };
inline constexpr auto kSavedInFolderList = Option<bool>{
	"ikk.savedInFolderList", Scope::Device, false,
	Category::Chats, "lng_ikk_saved_in_folder_list" };
inline constexpr auto kHideFolderUnreadCounters = Option<bool>{
	"ikk.hideFolderUnreadCounters", Scope::Device, false,
	Category::Chats, "lng_ikk_hide_folder_unread_counters" };
inline constexpr auto kStartupFolderMode = Option<int>{
	"ikk.startupFolderMode", Scope::Account, 0,
	Category::Chats, "lng_ikk_startup_folder", 0,
	[](const int &value) { return value >= 0 && value <= 2; } };
inline constexpr auto kStartupFolderId = Option<int>{
	"ikk.startupFolderId", Scope::Account, 0,
	Category::Chats, "lng_ikk_startup_folder", 0,
	[](const int &value) { return value >= 0; } };
inline constexpr auto kLastOpenedFolderId = Option<int>{
	"ikk.lastOpenedFolderId", Scope::Account, 0,
	Category::Chats, "lng_ikk_startup_folder", 0,
	[](const int &value) { return value >= 0; } };
inline constexpr auto kChatSort = Option<int>{
	"ikk.chatSort", Scope::Device, 0,
	Category::Chats, "lng_ikk_chat_sort", 0,
	[](const int &value) {
		if (value == 0) return true;
		if (value < 0 || value > 0xFFF) return false;
		auto seen = 0;
		for (auto i = 0; i != 4; ++i) {
			seen |= 1 << ((value >> (4 + i * 2)) & 3);
		}
		return seen == 0xF;
	} };
[[nodiscard]] inline bool ValidFolderIds(const QString &value) {
		if (value.isEmpty()) return true;
		auto previous = 0;
		for (const auto &part : value.split(u',')) {
			auto valid = false;
			const auto id = part.toInt(&valid);
			if (!valid || id <= previous || part != QString::number(id)) {
				return false;
			}
			previous = id;
		}
		return true;
}
inline const auto kManagedFolderIds = Option<QString>{
	"ikk.managedFolderIds", Scope::Account, QString(),
	Category::Chats, "lng_ikk_managed_only", 0, ValidFolderIds };
inline const auto kRecentFolderIds = Option<QString>{
	"ikk.recentFolderIds", Scope::Account, QString(),
	Category::Chats, "lng_ikk_recent_chats",
	static_cast<unsigned>(Flag::Hidden), ValidFolderIds };
inline constexpr auto kHideSponsoredMessages = Option<bool>{
	"ikk.hideSponsoredMessages", Scope::Device, false,
	Category::Chats, "lng_ikk_hide_sponsored_messages" };
inline constexpr auto kHideProxySponsor = Option<bool>{
	"ikk.hideProxySponsor", Scope::Device, false,
	Category::Chats, "lng_ikk_hide_proxy_sponsor" };
inline constexpr auto kHidePremiumPromotions = Option<bool>{
	"ikk.hidePremiumPromotions", Scope::Device, false,
	Category::Chats, "lng_ikk_hide_premium_promotions" };
inline constexpr auto kHideBirthdaySuggestions = Option<bool>{
	"ikk.hideBirthdaySuggestions", Scope::Device, false,
	Category::Chats, "lng_ikk_hide_birthday_suggestions" };
inline constexpr auto kDisableCommunityGrouping = Option<bool>{
	"ikk.disableCommunityGrouping", Scope::Device, false,
	Category::Chats, "lng_ikk_disable_community_grouping",
	static_cast<unsigned>(Flag::RequiresRestart) };
inline constexpr auto kCompactFolderTabs = Option<bool>{
	"ikk.compactFolderTabs", Scope::Device, false,
	Category::Chats, "lng_ikk_compact_folder_tabs",
	static_cast<unsigned>(Flag::RequiresRestart) };
inline constexpr auto kDisableGlobalSearch = Option<bool>{
	"ikk.disableGlobalSearch", Scope::Device, false,
	Category::Chats, "lng_ikk_disable_global_search" };
inline constexpr auto kChooseFolderAfterJoin = Option<bool>{
	"ikk.chooseFolderAfterJoin", Scope::Device, false,
	Category::Chats, "lng_ikk_choose_folder_after_join" };
inline constexpr auto kHidePhoneSuggestion = Option<bool>{
	"ikk.hidePhoneSuggestion", Scope::Device, false,
	Category::Chats, "lng_ikk_hide_phone_suggestion" };
inline constexpr auto kDisableScrollToNextChannel = Option<bool>{
	"ikk.disableScrollToNextChannel", Scope::Device, false,
	Category::Chats, "lng_ikk_disable_scroll_to_next_channel" };
inline constexpr auto kDisableScrollToNextTopic = Option<bool>{
	"ikk.disableScrollToNextTopic", Scope::Device, false,
	Category::Chats, "lng_ikk_disable_scroll_to_next_topic" };

inline constexpr auto kMinimumRecentChats = 5;
inline constexpr auto kMaximumRecentChats = 100;

[[nodiscard]] inline bool ValidRecentChats(const QString &value) {
	if (value.isEmpty()) {
		return true;
	}
	const auto parts = value.split(u',');
	if (parts.size() > kMaximumRecentChats) {
		return false;
	}
	for (const auto &part : parts) {
		auto ok = false;
		if (!part.toULongLong(&ok) || !ok) {
			return false;
		}
	}
	return true;
}

inline constexpr auto kRecentChats = Option<bool>{
	"ikk.recentChats", Scope::Device, false,
	Category::Chats, "lng_ikk_recent_chats_option" };
inline constexpr auto kRecentChatsLimit = Option<int>{
	"ikk.recentChatsLimit", Scope::Device, 30,
	Category::Chats, "lng_ikk_recent_chats_limit", 0,
	[](const int &value) {
		return value >= kMinimumRecentChats && value <= kMaximumRecentChats;
	} };
inline const auto kRecentChatsList = Option<QString>{
	"ikk.recentChatsList", Scope::Account, QString(),
	Category::Chats, "lng_ikk_recent_chats",
	static_cast<unsigned>(Flag::Hidden), ValidRecentChats };

inline constexpr auto kMaximumReadingPositions = 100;

[[nodiscard]] inline bool ValidReadingPositions(const QString &value) {
	if (value.isEmpty()) {
		return true;
	}
	const auto entries = value.split(u',');
	if (entries.size() > kMaximumReadingPositions) {
		return false;
	}
	for (const auto &entry : entries) {
		const auto parts = entry.split(u':');
		auto peerOk = false;
		auto msgOk = false;
		if (parts.size() != 2
			|| !parts[0].toULongLong(&peerOk) || !peerOk
			|| parts[1].toLongLong(&msgOk) <= 0 || !msgOk) {
			return false;
		}
	}
	return true;
}

inline constexpr auto kChatTools = Option<bool>{
	"ikk.chatTools", Scope::Device, false,
	Category::Chats, "lng_ikk_chat_tools" };
inline constexpr auto kRecentInShare = Option<bool>{
	"ikk.recentChatsInShare", Scope::Device, false,
	Category::Chats, "lng_ikk_recent_in_share" };
inline constexpr auto kSaveReadingPosition = Option<bool>{
	"ikk.saveReadingPosition", Scope::Device, false,
	Category::Chats, "lng_ikk_save_reading_position" };
inline const auto kReadingPositions = Option<QString>{
	"ikk.readingPositions", Scope::Account, QString(),
	Category::Chats, "lng_ikk_save_reading_position",
	static_cast<unsigned>(Flag::Hidden), ValidReadingPositions };

inline void RegisterOptions(Registry &registry) {
	Expects(registry.Add(kCompactList));
	Expects(registry.Add(kPreviewLines));
	Expects(registry.Add(kHideSavedAndArchivedPreviews));
	Expects(registry.Add(kHideStories));
	Expects(registry.Add(kHideAllChatsFolder));
	Expects(registry.Add(kShowArchiveInFolders));
	Expects(registry.Add(kArchiveInFolderList));
	Expects(registry.Add(kSavedInFolderList));
	Expects(registry.Add(kHideFolderUnreadCounters));
	Expects(registry.Add(kStartupFolderMode));
	Expects(registry.Add(kStartupFolderId));
	Expects(registry.Add(kLastOpenedFolderId));
	Expects(registry.Add(kChatSort));
	Expects(registry.Add(kManagedFolderIds));
	Expects(registry.Add(kHideSponsoredMessages));
	Expects(registry.Add(kHideProxySponsor));
	Expects(registry.Add(kHidePremiumPromotions));
	Expects(registry.Add(kHideBirthdaySuggestions));
	Expects(registry.Add(kHidePhoneSuggestion));
	Expects(registry.Add(kDisableCommunityGrouping));
	Expects(registry.Add(kCompactFolderTabs));
	Expects(registry.Add(kDisableGlobalSearch));
	Expects(registry.Add(kChooseFolderAfterJoin));
	Expects(registry.Add(kDisableScrollToNextChannel));
	Expects(registry.Add(kDisableScrollToNextTopic));
	Expects(registry.Add(kRecentChats));
	Expects(registry.Add(kRecentChatsLimit));
	Expects(registry.Add(kRecentChatsList));
	Expects(registry.Add(kRecentInShare));
	Expects(registry.Add(kRecentFolderIds));
	Expects(registry.Add(kChatTools));
	Expects(registry.Add(kSaveReadingPosition));
	Expects(registry.Add(kReadingPositions));
}

} // namespace Ikk::Chats
