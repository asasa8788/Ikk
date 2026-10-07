#include "ikk/settings/messages.h"

#include "ikk/core/options.h"
#include "ikk/messages/options.h"
#include "ikk/messages/reading.h"
#include "ikk/settings/home.h"
#include "lang/lang_keys.h"
#include "settings/settings_builder.h"
#include "settings/settings_common_session.h"
#include "ui/vertical_list.h"
#include "ui/layers/generic_box.h"
#include "ui/widgets/buttons.h"
#include "ui/widgets/checkbox.h"
#include "ui/widgets/fields/input_field.h"
#include "ui/wrap/vertical_layout.h"
#include "window/window_session_controller.h"
#include "styles/style_menu_icons.h"
#include "styles/style_layers.h"
#include "styles/style_settings.h"

namespace Ikk {
namespace {

using namespace ::Settings;
using namespace ::Settings::Builder;

class MessagesSection final : public Section<MessagesSection> {
public:
	MessagesSection(
		QWidget *parent,
		not_null<Window::SessionController*> controller)
	: Section(parent, controller) {
		const auto content = Ui::CreateChild<Ui::VerticalLayout>(this);
		build(content, kBuild);
		Ui::ResizeFitChild(this, content);
	}

	[[nodiscard]] rpl::producer<QString> title() override {
		return tr::lng_ikk_messages();
	}

	static const SectionBuildMethod kBuild;
};

Ui::SettingsButton *AddToggle(
		SectionBuilder &builder,
		const Option<bool> &option,
		rpl::producer<QString> title,
		QString id,
		QStringList keywords) {
	const auto button = builder.addButton({
		.id = std::move(id),
		.title = std::move(title),
		.st = &st::settingsButtonNoIcon,
		.toggled = ForDevice().Value(option),
		.keywords = std::move(keywords),
	});
	if (button) {
		button->toggledChanges(
		) | rpl::on_next([option](bool value) {
			Expects(ForDevice().Set(option, value));
		}, button->lifetime());
	}
	return button;
}

void AddReactionChild(
		SectionBuilder &builder,
		const Option<bool> &option,
		rpl::producer<QString> title,
		QString id,
		QStringList keywords) {
	if (const auto button = AddToggle(builder, option,
			std::move(title), std::move(id), std::move(keywords))) {
		ForDevice().Value(Messages::kHideReactions
		) | rpl::on_next([button](bool hidden) {
			button->setDisabled(hidden);
			button->setEnabled(!hidden);
		}, button->lifetime());
	}
}

void EditMarkBox(not_null<Ui::GenericBox*> box) {
	box->setTitle(tr::lng_ikk_edited_mark());
	const auto field = box->addRow(
		object_ptr<Ui::InputField>(
			box,
			st::defaultInputField,
			tr::lng_edited(),
			ForDevice().Get(Messages::kEditedMark)),
		st::boxRowPadding);
	box->setFocusCallback([=] { field->setFocusFast(); });
	const auto submit = [=] {
		if (ForDevice().Set(Messages::kEditedMark, field->getLastText())) {
			box->closeBox();
		}
	};
	field->submits() | rpl::on_next(submit, field->lifetime());
	box->addButton(tr::lng_settings_save(), submit);
	box->addButton(tr::lng_cancel(), [=] { box->closeBox(); });
}

QString ReadingChineseLabel(int value) {
	switch (value) {
	case 1: return tr::lng_ikk_reading_simplified(tr::now);
	case 2: return tr::lng_ikk_reading_traditional(tr::now);
	default: return tr::lng_ikk_reading_off(tr::now);
	}
}

QString SenderOnlineLabel(int value) {
	switch (value) {
	case 1: return tr::lng_ikk_sender_online_now(tr::now);
	case 2: return tr::lng_ikk_sender_online_recently(tr::now);
	default: return tr::lng_ikk_reading_off(tr::now);
	}
}

void SenderOnlineBox(not_null<Ui::GenericBox*> box) {
	box->setTitle(tr::lng_ikk_sender_online());
	const auto group = std::make_shared<Ui::RadiobuttonGroup>(
		ForDevice().Get(Messages::kSenderOnlineStatus));
	for (auto value = 0; value != 3; ++value) {
		box->addRow(object_ptr<Ui::Radiobutton>(
			box, group, value, SenderOnlineLabel(value),
			st::settingsSendType), st::settingsSendTypePadding);
	}
	group->setChangedCallback([=](int value) {
		Expects(ForDevice().Set(Messages::kSenderOnlineStatus, value));
		box->closeBox();
	});
}

void ReadingChineseBox(not_null<Ui::GenericBox*> box) {
	box->setTitle(tr::lng_ikk_reading_chinese());
	const auto group = std::make_shared<Ui::RadiobuttonGroup>(
		ForDevice().Get(Messages::kReadingChinese));
	for (auto value = 0; value != 3; ++value) {
		box->addRow(object_ptr<Ui::Radiobutton>(
			box, group, value, ReadingChineseLabel(value),
			st::settingsSendType), st::settingsSendTypePadding);
	}
	group->setChangedCallback([=](int value) {
		Expects(ForDevice().Set(Messages::kReadingChinese, value));
		box->closeBox();
	});
}

const auto kMeta = BuildHelper({
	.id = MessagesSection::Id(),
	.parentId = HomeId(),
	.title = &tr::lng_ikk_messages,
	.icon = &st::menuIconChatBubble,
}, [](SectionBuilder &builder) {
	builder.addSubsectionTitle({
		.id = u"ikk/messages/time"_q,
		.title = tr::lng_ikk_time_and_info(),
		.keywords = { u"time"_q, u"info"_q },
	});
	AddToggle(builder, Messages::kSecondsInMessages,
		tr::lng_ikk_seconds_in_messages(),
		u"ikk/messages/seconds"_q,
		{ u"seconds"_q, u"timestamp"_q });
	AddToggle(builder, Messages::kShowForwardedMessageDate,
		tr::lng_ikk_show_forwarded_message_date(),
		u"ikk/messages/forwarded-date"_q,
		{ u"forwarded"_q, u"original time"_q });
	AddToggle(builder, Messages::kShowServiceTime,
		tr::lng_ikk_show_service_time(),
		u"ikk/messages/service-time"_q,
		{ u"service"_q, u"time"_q });
	AddToggle(builder, Messages::kShowMessageId,
		tr::lng_ikk_show_message_id(),
		u"ikk/messages/id"_q,
		{ u"message ID"_q, u"tooltip"_q });
	const auto onlineController = builder.controller();
	builder.addButton({
		.id = u"ikk/messages/sender-online"_q,
		.title = tr::lng_ikk_sender_online(),
		.st = &st::settingsButtonNoIcon,
		.label = ForDevice().Value(Messages::kSenderOnlineStatus)
			| rpl::map(SenderOnlineLabel),
		.onClick = [=] { onlineController->show(Box(SenderOnlineBox)); },
		.keywords = { u"online"_q, u"last seen"_q, u"avatar"_q },
	});
	builder.addSubsectionTitle({
		.id = u"ikk/messages/marks"_q,
		.title = tr::lng_ikk_marks_and_counts(),
		.keywords = { u"labels"_q, u"counts"_q },
	});
	AddToggle(builder, Messages::kExactMessageCounters,
		tr::lng_ikk_exact_message_counters(),
		u"ikk/messages/exact-counters"_q,
		{ u"exact"_q, u"views"_q, u"replies"_q });
	AddToggle(builder, Messages::kShowForwardCount,
		tr::lng_ikk_show_forward_count(),
		u"ikk/messages/forward-count"_q,
		{ u"forwards"_q, u"shares"_q, u"count"_q });
	AddToggle(builder, Messages::kHideMessageViews,
		tr::lng_ikk_hide_message_views(),
		u"ikk/messages/hide-views"_q,
		{ u"hide"_q, u"views"_q });
	AddToggle(builder, Messages::kHideChannelSignature,
		tr::lng_ikk_hide_channel_signature(),
		u"ikk/messages/hide-signature"_q,
		{ u"channel"_q, u"signature"_q });
	AddToggle(builder, Messages::kHideEditedBadge,
		tr::lng_ikk_hide_edited_badge(),
		u"ikk/messages/hide-edited"_q,
		{ u"edited"_q, u"badge"_q });
	AddToggle(builder, Messages::kEditedIcon,
		tr::lng_ikk_edited_icon(),
		u"ikk/messages/edited-icon"_q,
		{ u"edited"_q, u"icon"_q });
	const auto controller = builder.controller();
	builder.addButton({
		.id = u"ikk/messages/edited-mark"_q,
		.title = tr::lng_ikk_edited_mark(),
		.st = &st::settingsButtonNoIcon,
		.label = ForDevice().Value(Messages::kEditedMark)
			| rpl::map([](const QString &text) {
				return text.isEmpty()
					? tr::lng_settings_notifications_display_default(tr::now)
					: text;
			}),
		.onClick = [=] { controller->show(Box(EditMarkBox)); },
		.keywords = { u"edited"_q, u"label"_q, u"text"_q },
		.shown = rpl::combine(
			ForDevice().Value(Messages::kHideEditedBadge),
			ForDevice().Value(Messages::kEditedIcon)
		) | rpl::map([](bool hidden, bool icon) { return !hidden && !icon; }),
	});
	builder.addSubsectionTitle({
		.id = u"ikk/messages/reactions"_q,
		.title = tr::lng_ikk_reactions(),
		.keywords = { u"reactions"_q },
	});
	AddToggle(builder, Messages::kHideReactions,
		tr::lng_ikk_hide_reactions(),
		u"ikk/messages/hide-reactions"_q,
		{ u"hide"_q, u"reactions"_q });
	AddReactionChild(builder, Messages::kHidePrivateReactions,
		tr::lng_ikk_hide_private_reactions(),
		u"ikk/messages/reactions-private"_q,
		{ u"private"_q, u"chat reactions"_q });
	AddReactionChild(builder, Messages::kHideGroupReactions,
		tr::lng_ikk_hide_group_reactions(),
		u"ikk/messages/reactions-group"_q,
		{ u"group"_q, u"chat reactions"_q });
	AddReactionChild(builder, Messages::kHideChannelReactions,
		tr::lng_ikk_hide_channel_reactions(),
		u"ikk/messages/reactions-channel"_q,
		{ u"channel"_q, u"chat reactions"_q });
	AddToggle(builder, Messages::kHideReactionMenu,
		tr::lng_ikk_hide_reaction_menu(),
		u"ikk/messages/reaction-menu"_q,
		{ u"context menu"_q, u"reaction panel"_q });
	AddToggle(builder, Messages::kHideReactionMenuWhenSelecting,
		tr::lng_ikk_hide_reaction_menu_when_selecting(),
		u"ikk/messages/reaction-selection"_q,
		{ u"selection"_q, u"reaction panel"_q });
	builder.addSubsectionTitle({
		.id = u"ikk/messages/effects"_q,
		.title = tr::lng_ikk_effects(),
		.keywords = { u"effects"_q, u"animation"_q },
	});
	AddToggle(builder, Messages::kDisablePremiumStickerEffects,
		tr::lng_ikk_disable_premium_sticker_effects(),
		u"ikk/messages/effects-premium"_q,
		{ u"Premium"_q, u"sticker effects"_q });
	AddToggle(builder, Messages::kDisableEmojiInteractions,
		tr::lng_ikk_disable_emoji_interactions(),
		u"ikk/messages/effects-emoji"_q,
		{ u"emoji"_q, u"interactions"_q });
	AddToggle(builder, Messages::kDisableMessageEffects,
		tr::lng_ikk_disable_message_effects(),
		u"ikk/messages/effects-message"_q,
		{ u"message effects"_q });
	builder.addSubsectionTitle({
		.id = u"ikk/messages/content"_q,
		.title = tr::lng_ikk_content_display(),
		.keywords = { u"content"_q, u"display"_q },
	});
	AddToggle(builder, Messages::kRevealSpoilers,
		tr::lng_ikk_reveal_spoilers(),
		u"ikk/messages/reveal-spoilers"_q,
		{ u"reveal"_q, u"spoilers"_q });
	builder.addDividerText(tr::lng_ikk_reveal_spoilers_note());
	AddToggle(builder, Messages::kHideQuickShare,
		tr::lng_ikk_hide_quick_share(),
		u"ikk/messages/hide-quick-share"_q,
		{ u"quick forward"_q, u"share"_q });
	AddToggle(builder, Messages::kHideRecommendedChannels,
		tr::lng_ikk_hide_recommended_channels(),
		u"ikk/messages/hide-recommended"_q,
		{ u"recommended"_q, u"channels"_q });
	AddToggle(builder, Messages::kCollapseRecommendedChannels,
		tr::lng_ikk_collapse_recommended_channels(),
		u"ikk/messages/collapse-recommended"_q,
		{ u"similar"_q, u"channels"_q, u"collapse"_q });
	AddToggle(builder, Messages::kSimplifiedReplies,
		tr::lng_ikk_simplified_replies(),
		u"ikk/messages/simplified-replies"_q,
		{ u"reply"_q, u"quote"_q, u"simple"_q });
	AddToggle(builder, Messages::kDisableVideoUserpics,
		tr::lng_ikk_disable_video_userpics(),
		u"ikk/messages/disable-video-userpics"_q,
		{ u"animated"_q, u"avatar"_q, u"video"_q });
	AddToggle(builder, Messages::kHidePremiumBadges,
		tr::lng_ikk_hide_premium_badges(),
		u"ikk/messages/hide-premium"_q,
		{ u"Premium"_q, u"emoji status"_q });
	AddToggle(builder, Messages::kHideSavedTags,
		tr::lng_ikk_hide_saved_tags(),
		u"ikk/messages/hide-tags"_q,
		{ u"saved messages"_q, u"tags"_q });
	AddToggle(builder, Messages::kHidePrivateChatActivities,
		tr::lng_ikk_hide_private_chat_activities(),
		u"ikk/messages/hide-private-activity"_q,
		{ u"typing"_q, u"recording"_q, u"private chat"_q });
	builder.addDividerText(tr::lng_ikk_private_activities_note());
	AddToggle(builder, Messages::kReadingSpacing,
		tr::lng_ikk_reading_spacing(),
		u"ikk/messages/reading-spacing"_q,
		{ u"reading"_q, u"spacing"_q });
	const auto chinese = builder.addButton({
		.id = u"ikk/messages/reading-chinese"_q,
		.title = tr::lng_ikk_reading_chinese(),
		.st = &st::settingsButtonNoIcon,
		.label = Messages::ChineseConversionAvailable()
			? rpl::producer<QString>(ForDevice().Value(Messages::kReadingChinese)
				| rpl::map([](int value) { return ReadingChineseLabel(value); }))
			: rpl::producer<QString>(rpl::single(
				tr::lng_ikk_reading_unavailable(tr::now))),
		.onClick = [=] { controller->show(Box(ReadingChineseBox)); },
		.keywords = { u"Chinese"_q, u"simplified"_q, u"traditional"_q },
	});
	if (chinese && !Messages::ChineseConversionAvailable()) {
		chinese->setDisabled(true);
	}
	builder.addDividerText(tr::lng_ikk_reading_chinese_note());
});

const SectionBuildMethod MessagesSection::kBuild = kMeta.build;

} // namespace

Settings::Type MessagesId() {
	return MessagesSection::Id();
}

} // namespace Ikk
