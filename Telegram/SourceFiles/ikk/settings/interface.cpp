#include "ikk/settings/interface.h"

#include "ikk/notifications/settings.h"

#include "ikk/interface/app_icon.h"
#include "ikk/interface/options.h"
#include "ikk/interface/main_menu.h"
#include "ikk/settings/home.h"
#include "ikk/settings/restart.h"
#include "lang/lang_keys.h"
#include "settings/settings_builder.h"
#include "settings/settings_common.h"
#include "settings/settings_common_session.h"
#include "ui/layers/generic_box.h"
#include "ui/vertical_list.h"
#include "ui/widgets/buttons.h"
#include "ui/widgets/checkbox.h"
#include "ui/widgets/continuous_sliders.h"
#include "ui/widgets/fields/input_field.h"
#include "ui/widgets/labels.h"
#include "window/window_session_controller.h"
#include "styles/style_layers.h"
#include "styles/style_menu_icons.h"
#include "styles/style_ikk_interface.h"
#include "styles/style_settings.h"
#include "styles/style_widgets.h"

namespace Ikk {
namespace {

using namespace ::Settings;
using namespace ::Settings::Builder;

class InterfaceSection final : public Section<InterfaceSection> {
public:
	InterfaceSection(
		QWidget *parent,
		not_null<Window::SessionController*> controller)
	: Section(parent, controller) {
		const auto content = Ui::CreateChild<Ui::VerticalLayout>(this);
		build(content, kBuild);
		Ui::ResizeFitChild(this, content);
	}

	[[nodiscard]] rpl::producer<QString> title() override {
		return tr::lng_ikk_interface();
	}

	static const SectionBuildMethod kBuild;
};

constexpr auto kMinRoundness = 10;
constexpr auto kMaxRoundness = 100;

QString RoundnessLabel(int value) {
	return (value
		? QString::number(value) + u"%"_q
		: tr::lng_ikk_preview_follow(tr::now))
		+ u" · "_q + tr::lng_ikk_restart_required(tr::now);
}

void RoundnessBox(
		not_null<Ui::GenericBox*> box,
		const Option<int> &option,
		QString title,
		not_null<Window::SessionController*> controller) {
	box->setTitle(title);
	const auto current = ForDevice().Get(option);
	const auto follow = box->addRow(object_ptr<Ui::Checkbox>(
		box,
		tr::lng_ikk_preview_follow(tr::now),
		!current,
		st::defaultBoxCheckbox));
	auto row = MakeSliderWithLabel(
		box,
		st::settingsScale,
		st::settingsScaleLabel,
		st::normalFont->spacew * 2,
		st::settingsScaleLabel.style.font->width(u"100%"_q),
		true);
	const auto slider = row.slider;
	const auto label = row.label;
	box->addRow(std::move(row.widget), st::settingsBigScalePadding);
	slider->setAccessibleName(title);

	const auto value = box->lifetime().make_state<int>(
		current ? current : kMaxRoundness);
	const auto show = [=](int percent) {
		*value = percent;
		label->setText(QString::number(percent) + u"%"_q);
	};
	slider->setPseudoDiscrete(
		kMaxRoundness - kMinRoundness + 1,
		[](int index) { return kMinRoundness + index; },
		*value,
		show);
	show(*value);
	follow->checkedValue(
	) | rpl::on_next([=](bool checked) {
		slider->setDisabled(checked);
	}, slider->lifetime());

	box->addButton(tr::lng_settings_save(), [=] {
		const auto chosen = follow->checked() ? 0 : *value;
		if (chosen != current) {
			Expects(ForDevice().Set(option, chosen));
			ShowRestartPrompt(controller);
		}
		box->closeBox();
	});
	box->addButton(tr::lng_cancel(), [=] { box->closeBox(); });
}

void AddRoundness(
		SectionBuilder &builder,
		const Option<int> &option,
		rpl::producer<QString> title,
		QString id,
		QStringList keywords) {
	const auto controller = builder.controller();
	builder.addButton({
		.id = std::move(id),
		.title = std::move(title),
		.st = &st::settingsButtonNoIcon,
		.label = ForDevice().Value(option) | rpl::map(RoundnessLabel),
		.onClick = [=] {
			controller->show(Box([=](not_null<Ui::GenericBox*> box) {
				RoundnessBox(box, option, (option.key == Interface::kBubbleRoundness.key)
					? tr::lng_ikk_bubble_roundness(tr::now)
					: tr::lng_ikk_avatar_roundness(tr::now), controller);
			}));
		},
		.keywords = std::move(keywords),
	});
}

void TextWidthBox(not_null<Ui::GenericBox*> box) {
	box->setTitle(tr::lng_ikk_text_message_width());
	const auto current = ForDevice().Get(Interface::kTextMessageWidth);
	const auto field = box->addRow(object_ptr<Ui::InputField>(
		box,
		st::defaultInputField,
		tr::lng_ikk_text_width_hint(),
		current ? QString::number(current) : QString()));
	field->setInputMethodHints(Qt::ImhDigitsOnly);
	box->setFocusCallback([=] { field->setFocusFast(); });
	const auto submit = [=] {
		const auto text = field->getLastText().trimmed();
		auto valid = false;
		const auto value = text.isEmpty() ? 0 : text.toInt(&valid);
		if ((!text.isEmpty() && !valid)
			|| (value != 0 && (value < 50 || value > 400))) {
			field->showError();
			return;
		}
		if (value != current) {
			Expects(ForDevice().Set(Interface::kTextMessageWidth, value));
		}
		box->closeBox();
	};
	field->submits(
	) | rpl::on_next([=](auto) { submit(); }, field->lifetime());
	box->addButton(tr::lng_settings_save(), submit);
	box->addButton(tr::lng_cancel(), [=] { box->closeBox(); });
}

QString DelayLabel(int milliseconds) {
	return milliseconds
		? QString::number(milliseconds / 1000.0)
			+ tr::lng_ikk_seconds_suffix(tr::now)
		: tr::lng_ikk_preview_follow(tr::now);
}

void DelayBox(
		not_null<Ui::GenericBox*> box,
		const Option<int> &option,
		QString title) {
	box->setTitle(std::move(title));
	const auto group = std::make_shared<Ui::RadiobuttonGroup>(
		ForDevice().Get(option));
	for (const auto &value : { 0, 500, 1000, 2000, 5000, 10000, 30000, 60000 }) {
		box->addRow(object_ptr<Ui::Radiobutton>(
			box, group, value, DelayLabel(value), st::settingsSendType),
			st::settingsSendTypePadding);
	}
	group->setChangedCallback([=](int value) {
		Expects(ForDevice().Set(option, value));
		box->closeBox();
	});
}

void AddDelay(
		SectionBuilder &builder,
		const Option<int> &option,
		rpl::producer<QString> title,
		QString id) {
	const auto controller = builder.controller();
	builder.addButton({
		.id = std::move(id),
		.title = std::move(title),
		.st = &st::settingsButtonNoIcon,
		.label = ForDevice().Value(option) | rpl::map(DelayLabel),
		.onClick = [=] {
			controller->show(Box([=](not_null<Ui::GenericBox*> box) {
				DelayBox(box, option, option.key == Interface::kNotificationDelay.key
					? tr::lng_ikk_notification_delay(tr::now)
					: tr::lng_ikk_other_device_notification_delay(tr::now));
			}));
		},
		.keywords = { u"notification"_q, u"delay"_q },
	});
}

void AppIconBox(not_null<Ui::GenericBox*> box) {
	box->setTitle(tr::lng_ikk_app_icon());
	const auto choices = Interface::AppIconChoices();
	const auto current = ForDevice().Get(Interface::kAppIcon);
	const auto shown = box->lifetime().make_state<QString>(current);
	const auto size = st::ikkAppIconPreview;
	const auto preview = box->addRow(
		object_ptr<Ui::RpWidget>(box),
		st::ikkAppIconPreviewMargin);
	preview->resize(st::boxWidth, size);
	preview->paintRequest(
	) | rpl::on_next([=] {
		auto p = QPainter(preview);
		const auto ratio = style::DevicePixelRatio();
		auto image = Interface::AppIconPreview(*shown).scaled(
			QSize(size, size) * ratio,
			Qt::IgnoreAspectRatio,
			Qt::SmoothTransformation);
		image.setDevicePixelRatio(ratio);
		p.drawImage((preview->width() - size) / 2, 0, image);
	}, preview->lifetime());
	auto selected = 0;
	for (auto i = 0; i != int(choices.size()); ++i) {
		if (choices[i].id == current) {
			selected = i;
		}
	}
	const auto group = std::make_shared<Ui::RadiobuttonGroup>(selected);
	for (auto i = 0; i != int(choices.size()); ++i) {
		box->addRow(object_ptr<Ui::Radiobutton>(
			box, group, i, choices[i].title, st::settingsSendType),
			st::settingsSendTypePadding);
	}
	group->setChangedCallback([=](int value) {
		*shown = choices[value].id;
		Expects(ForDevice().Set(Interface::kAppIcon, *shown));
		preview->update();
	});
	box->addRow(
		object_ptr<Ui::FlatLabel>(
			box,
			tr::lng_ikk_app_icon_about(),
			st::boxDividerLabel),
		st::settingsSendTypePadding);
	box->addButton(tr::lng_close(), [=] { box->closeBox(); });
}

void AddToggle(
		SectionBuilder &builder,
		const Option<bool> &option,
		rpl::producer<QString> title,
		QString id,
		QStringList keywords) {
	const auto controller = builder.controller();
	const auto button = builder.addButton({
		.id = std::move(id),
		.title = std::move(title),
		.st = &st::settingsButtonNoIcon,
		.toggled = ForDevice().Value(option),
		.keywords = std::move(keywords),
	});
	if (button) {
		button->toggledChanges(
		) | rpl::on_next([option, controller](bool value) {
			Expects(ForDevice().Set(option, value));
			if (option.flags & Interface::kRestart) {
				ShowRestartPrompt(controller);
			}
		}, button->lifetime());
	}
}

const auto kMeta = BuildHelper({
	.id = InterfaceSection::Id(),
	.parentId = HomeId(),
	.title = &tr::lng_ikk_interface,
	.icon = &st::menuIconChatBubble,
}, [](SectionBuilder &builder) {
	builder.addSubsectionTitle({
		.id = u"ikk/interface/roundness"_q,
		.title = tr::lng_ikk_roundness_and_shapes(),
		.keywords = { u"corners"_q, u"shapes"_q },
	});
	AddRoundness(builder, Interface::kBubbleRoundness,
		tr::lng_ikk_bubble_roundness(),
		u"ikk/interface/bubble-roundness"_q,
		{ u"bubble"_q, u"roundness"_q });
	AddRoundness(builder, Interface::kAvatarRoundness,
		tr::lng_ikk_avatar_roundness(),
		u"ikk/interface/avatar-roundness"_q,
		{ u"avatar"_q, u"roundness"_q });
	const auto controller = builder.controller();
	const auto button = builder.addButton({
		.id = u"ikk/interface/uniform-avatars"_q,
		.title = tr::lng_ikk_uniform_avatar_shapes(),
		.st = &st::settingsButtonNoIcon,
		.label = rpl::single(tr::lng_ikk_restart_required(tr::now)),
		.toggled = ForDevice().Value(Interface::kUniformAvatarShapes),
		.keywords = { u"forum"_q, u"channel"_q, u"avatar"_q },
		.shown = ForDevice().Value(Interface::kAvatarRoundness)
			| rpl::map([](int value) { return value != 0; }),
	});
	if (button) {
		button->toggledChanges(
		) | rpl::on_next([=](bool value) {
			Expects(ForDevice().Set(Interface::kUniformAvatarShapes, value));
			ShowRestartPrompt(controller);
		}, button->lifetime());
	}
	builder.addSubsectionTitle({
		.id = u"ikk/interface/message-style"_q,
		.title = tr::lng_ikk_message_style(),
		.keywords = { u"messages"_q, u"style"_q },
	});
	builder.addButton({
		.id = u"ikk/interface/text-width"_q,
		.title = tr::lng_ikk_text_message_width(),
		.st = &st::settingsButtonNoIcon,
		.label = ForDevice().Value(Interface::kTextMessageWidth)
			| rpl::map([](int value) {
				return value ? QString::number(value) + u"%"_q
					: tr::lng_ikk_preview_follow(tr::now);
			}),
		.onClick = [=] { controller->show(Box(TextWidthBox)); },
		.keywords = { u"text"_q, u"width"_q },
	});
	AddToggle(builder, Interface::kWideChannelPosts,
		tr::lng_ikk_wide_channel_posts(),
		u"ikk/interface/wide-channel-posts"_q,
		{ u"channel"_q, u"width"_q });
	AddToggle(builder, Interface::kHideBubbleTail,
		tr::lng_ikk_hide_bubble_tail(),
		u"ikk/interface/hide-bubble-tail"_q,
		{ u"bubble"_q, u"tail"_q });
	AddToggle(builder, Interface::kThemeReplyColors,
		tr::lng_ikk_theme_reply_colors(),
		u"ikk/interface/theme-reply-colors"_q,
		{ u"reply"_q, u"quote"_q, u"color"_q });
	AddToggle(builder, Interface::kHideReplyThumbnail,
		tr::lng_ikk_hide_reply_thumbnail(),
		u"ikk/interface/hide-reply-thumbnail"_q,
		{ u"reply"_q, u"thumbnail"_q });
	AddToggle(builder, Interface::kIgnoreChatTheme,
		tr::lng_ikk_ignore_chat_theme(),
		u"ikk/interface/ignore-chat-theme"_q,
		{ u"chat"_q, u"theme"_q, u"wallpaper"_q });
	AddToggle(builder, Interface::kIgnorePrivateChatTheme,
		tr::lng_ikk_ignore_private_chat_theme(),
		u"ikk/interface/ignore-private-theme"_q,
		{ u"private"_q, u"theme"_q, u"wallpaper"_q });
	AddToggle(builder, Interface::kIgnoreChannelChatTheme,
		tr::lng_ikk_ignore_channel_chat_theme(),
		u"ikk/interface/ignore-channel-theme"_q,
		{ u"channel"_q, u"theme"_q, u"wallpaper"_q });
	builder.addSubsectionTitle({
		.id = u"ikk/interface/main-menu-heading"_q,
		.title = tr::lng_ikk_main_menu(),
		.keywords = { u"menu"_q, u"title"_q },
	});
	builder.addButton({
		.id = u"ikk/interface/main-menu"_q,
		.title = tr::lng_ikk_main_menu(),
		.st = &st::settingsButtonNoIcon,
		.onClick = [=] { controller->show(Box(Interface::MainMenuBox)); },
		.keywords = { u"menu"_q, u"order"_q, u"visibility"_q },
	});
	AddToggle(builder, Interface::kAlwaysSeasonal,
		tr::lng_ikk_always_seasonal(),
		u"ikk/interface/always-seasonal"_q,
		{ u"holiday"_q, u"snow"_q, u"decoration"_q });
	builder.addSubsectionTitle({
		.id = u"ikk/interface/window-notification"_q,
		.title = tr::lng_ikk_window_notification(),
		.keywords = { u"window"_q, u"notification"_q },
	});
	builder.addButton({
		.id = u"ikk/interface/app-icon"_q,
		.title = tr::lng_ikk_app_icon(),
		.st = &st::settingsButtonNoIcon,
		.label = ForDevice().Value(Interface::kAppIcon)
			| rpl::map(Interface::AppIconTitle),
		.onClick = [=] { controller->show(Box(AppIconBox)); },
		.keywords = { u"icon"_q, u"dock"_q, u"taskbar"_q },
	});
	AddToggle(builder, Interface::kHideAppIconBadge,
		tr::lng_ikk_hide_app_icon_badge(),
		u"ikk/interface/hide-app-icon-badge"_q,
		{ u"dock"_q, u"icon"_q, u"badge"_q });
	AddToggle(builder, Interface::kAccountNameInTitle,
		tr::lng_ikk_account_name_in_title(),
		u"ikk/interface/account-name-title"_q,
		{ u"window"_q, u"title"_q, u"account"_q });
	AddDelay(builder, Interface::kNotificationDelay,
		tr::lng_ikk_notification_delay(),
		u"ikk/interface/notification-delay"_q);
	AddDelay(builder, Interface::kOtherDeviceNotificationDelay,
		tr::lng_ikk_other_device_notification_delay(),
		u"ikk/interface/other-device-notification-delay"_q);
	builder.addButton({
		.id = u"ikk/interface/quiet-hours"_q,
		.title = tr::lng_ikk_quiet_hours(),
		.st = &st::settingsButtonNoIcon,
		.label = Notifications::QuietHoursLabel(),
		.onClick = [=] {
			controller->show(Box(Notifications::QuietHoursBox));
		},
		.keywords = { u"notification"_q, u"quiet"_q, u"mute"_q, u"night"_q },
	});
	builder.addSubsectionTitle({
		.id = u"ikk/interface/text"_q,
		.title = tr::lng_ikk_ui_text(),
		.keywords = { u"text"_q, u"punctuation"_q },
	});
	AddToggle(builder, Interface::kHalfwidthUiPunctuation,
		tr::lng_ikk_halfwidth_ui_punctuation(),
		u"ikk/interface/halfwidth-ui-punctuation"_q,
		{ u"text"_q, u"punctuation"_q });
});

const SectionBuildMethod InterfaceSection::kBuild = kMeta.build;

} // namespace

Settings::Type InterfaceId() {
	return InterfaceSection::Id();
}

} // namespace Ikk
