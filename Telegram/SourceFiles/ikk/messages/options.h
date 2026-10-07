#pragma once

#include "ikk/core/options.h"

namespace Ikk::Messages {

inline constexpr auto kRefreshMessageView = static_cast<unsigned>(
	Flag::RefreshMessageView);

inline constexpr auto kSecondsInMessages = Option<bool>{
	"ikk.secondsInMessages", Scope::Device, false,
	Category::Messages, "lng_ikk_seconds_in_messages", kRefreshMessageView };
inline constexpr auto kShowForwardedMessageDate = Option<bool>{
	"ikk.showForwardedMessageDate", Scope::Device, false,
	Category::Messages, "lng_ikk_show_forwarded_message_date", kRefreshMessageView };
inline constexpr auto kShowServiceTime = Option<bool>{
	"ikk.showServiceTime", Scope::Device, false,
	Category::Messages, "lng_ikk_show_service_time", kRefreshMessageView };
inline constexpr auto kShowMessageId = Option<bool>{
	"ikk.showMessageId", Scope::Device, false,
	Category::Messages, "lng_ikk_show_message_id", kRefreshMessageView };
inline constexpr auto kSenderOnlineStatus = Option<int>{
	"ikk.senderOnlineStatus", Scope::Device, 0,
	Category::Messages, "lng_ikk_sender_online", kRefreshMessageView,
	[](const int &value) { return value >= 0 && value <= 2; } };
inline constexpr auto kExactMessageCounters = Option<bool>{
	"ikk.exactMessageCounters", Scope::Device, false,
	Category::Messages, "lng_ikk_exact_message_counters", kRefreshMessageView };
inline constexpr auto kHideMessageViews = Option<bool>{
	"ikk.hideMessageViews", Scope::Device, false,
	Category::Messages, "lng_ikk_hide_message_views", kRefreshMessageView };
inline constexpr auto kShowForwardCount = Option<bool>{
	"ikk.showForwardCount", Scope::Device, false,
	Category::Messages, "lng_ikk_show_forward_count", kRefreshMessageView };
inline constexpr auto kHideChannelSignature = Option<bool>{
	"ikk.hideChannelSignature", Scope::Device, false,
	Category::Messages, "lng_ikk_hide_channel_signature", kRefreshMessageView };
inline constexpr auto kHideEditedBadge = Option<bool>{
	"ikk.hideEditedBadge", Scope::Device, false,
	Category::Messages, "lng_ikk_hide_edited_badge", kRefreshMessageView };
inline const auto kEditedMark = Option<QString>{
	"ikk.editedMark", Scope::Device, QString(),
	Category::Messages, "lng_ikk_edited_mark", kRefreshMessageView };
inline constexpr auto kHideReactions = Option<bool>{
	"ikk.hideReactions", Scope::Device, false,
	Category::Messages, "lng_ikk_hide_reactions", kRefreshMessageView };
inline constexpr auto kHidePrivateReactions = Option<bool>{
	"ikk.hidePrivateReactions", Scope::Device, false,
	Category::Messages, "lng_ikk_hide_private_reactions", kRefreshMessageView };
inline constexpr auto kHideGroupReactions = Option<bool>{
	"ikk.hideGroupReactions", Scope::Device, false,
	Category::Messages, "lng_ikk_hide_group_reactions", kRefreshMessageView };
inline constexpr auto kHideChannelReactions = Option<bool>{
	"ikk.hideChannelReactions", Scope::Device, false,
	Category::Messages, "lng_ikk_hide_channel_reactions", kRefreshMessageView };
inline constexpr auto kHideReactionMenu = Option<bool>{
	"ikk.hideReactionMenu", Scope::Device, false,
	Category::Messages, "lng_ikk_hide_reaction_menu" };
inline constexpr auto kHideReactionMenuWhenSelecting = Option<bool>{
	"ikk.hideReactionMenuWhenSelecting", Scope::Device, false,
	Category::Messages, "lng_ikk_hide_reaction_menu_when_selecting" };
inline constexpr auto kDisablePremiumStickerEffects = Option<bool>{
	"ikk.disablePremiumStickerEffects", Scope::Device, false,
	Category::Messages, "lng_ikk_disable_premium_sticker_effects" };
inline constexpr auto kDisableEmojiInteractions = Option<bool>{
	"ikk.disableEmojiInteractions", Scope::Device, false,
	Category::Messages, "lng_ikk_disable_emoji_interactions" };
inline constexpr auto kDisableMessageEffects = Option<bool>{
	"ikk.disableMessageEffects", Scope::Device, false,
	Category::Messages, "lng_ikk_disable_message_effects" };
inline constexpr auto kRevealSpoilers = Option<bool>{
	"ikk.revealSpoilers", Scope::Device, false,
	Category::Messages, "lng_ikk_reveal_spoilers", kRefreshMessageView };
inline constexpr auto kHideQuickShare = Option<bool>{
	"ikk.hideQuickShare", Scope::Device, false,
	Category::Messages, "lng_ikk_hide_quick_share", kRefreshMessageView };
inline constexpr auto kHideRecommendedChannels = Option<bool>{
	"ikk.hideRecommendedChannels", Scope::Device, false,
	Category::Messages, "lng_ikk_hide_recommended_channels", kRefreshMessageView };
inline constexpr auto kHidePremiumBadges = Option<bool>{
	"ikk.hidePremiumBadges", Scope::Device, false,
	Category::Messages, "lng_ikk_hide_premium_badges", kRefreshMessageView };
inline constexpr auto kEditedIcon = Option<bool>{
	"ikk.editedIcon", Scope::Device, false,
	Category::Messages, "lng_ikk_edited_icon", kRefreshMessageView };
inline constexpr auto kSimplifiedReplies = Option<bool>{
	"ikk.simplifiedReplies", Scope::Device, false,
	Category::Messages, "lng_ikk_simplified_replies", kRefreshMessageView };
inline constexpr auto kDisableVideoUserpics = Option<bool>{
	"ikk.disableVideoUserpics", Scope::Device, false,
	Category::Messages, "lng_ikk_disable_video_userpics", kRefreshMessageView
		| static_cast<unsigned>(Flag::RefreshDialogList) };
inline constexpr auto kCollapseRecommendedChannels = Option<bool>{
	"ikk.collapseRecommendedChannels", Scope::Device, false,
	Category::Messages, "lng_ikk_collapse_recommended_channels" };
inline constexpr auto kHideSavedTags = Option<bool>{
	"ikk.hideSavedTags", Scope::Device, false,
	Category::Messages, "lng_ikk_hide_saved_tags" };
inline constexpr auto kHidePrivateChatActivities = Option<bool>{
	"ikk.hidePrivateChatActivities", Scope::Device, false,
	Category::Messages, "lng_ikk_hide_private_chat_activities" };
inline constexpr auto kReadingSpacing = Option<bool>{
	"ikk.readingSpacing", Scope::Device, false,
	Category::Messages, "lng_ikk_reading_spacing", kRefreshMessageView };
inline constexpr auto kReadingChinese = Option<int>{
	"ikk.readingChinese", Scope::Device, 0,
	Category::Messages, "lng_ikk_reading_chinese", kRefreshMessageView,
	[](const int &value) { return value >= 0 && value <= 2; } };

inline void RegisterOptions(Registry &registry) {
	Expects(registry.Add(kSecondsInMessages));
	Expects(registry.Add(kShowForwardedMessageDate));
	Expects(registry.Add(kShowServiceTime));
	Expects(registry.Add(kShowMessageId));
	Expects(registry.Add(kSenderOnlineStatus));
	Expects(registry.Add(kExactMessageCounters));
	Expects(registry.Add(kHideMessageViews));
	Expects(registry.Add(kShowForwardCount));
	Expects(registry.Add(kHideChannelSignature));
	Expects(registry.Add(kHideEditedBadge));
	Expects(registry.Add(kEditedMark));
	Expects(registry.Add(kHideReactions));
	Expects(registry.Add(kHidePrivateReactions));
	Expects(registry.Add(kHideGroupReactions));
	Expects(registry.Add(kHideChannelReactions));
	Expects(registry.Add(kHideReactionMenu));
	Expects(registry.Add(kHideReactionMenuWhenSelecting));
	Expects(registry.Add(kDisablePremiumStickerEffects));
	Expects(registry.Add(kDisableEmojiInteractions));
	Expects(registry.Add(kDisableMessageEffects));
	Expects(registry.Add(kRevealSpoilers));
	Expects(registry.Add(kHideQuickShare));
	Expects(registry.Add(kHideRecommendedChannels));
	Expects(registry.Add(kHidePremiumBadges));
	Expects(registry.Add(kHideSavedTags));
	Expects(registry.Add(kEditedIcon));
	Expects(registry.Add(kSimplifiedReplies));
	Expects(registry.Add(kDisableVideoUserpics));
	Expects(registry.Add(kCollapseRecommendedChannels));
	Expects(registry.Add(kHidePrivateChatActivities));
	Expects(registry.Add(kReadingSpacing));
	Expects(registry.Add(kReadingChinese));
}

} // namespace Ikk::Messages
