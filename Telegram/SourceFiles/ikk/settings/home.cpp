#include "ikk/settings/home.h"
#include "ikk/settings/interface.h"
#include "ikk/settings/messages.h"
#include "ikk/settings/menu.h"
#include "ikk/settings/chats.h"
#include "ikk/settings/compose.h"
#include "ikk/settings/config.h"
#include "ikk/settings/media.h"
#include "ikk/settings/privacy.h"
#include "ikk/settings/services.h"
#include "ikk/settings/rules.h"
#include "ikk/settings/network.h"

#include "boxes/about_box.h"
#include "core/click_handler_types.h"
#include "lang/lang_keys.h"
#include "settings/sections/settings_main.h"
#include "settings/settings_builder.h"
#include "settings/settings_common_session.h"
#include "ui/vertical_list.h"
#include "window/window_session_controller.h"
#include "styles/style_menu_icons.h"

namespace Ikk {
namespace {

using namespace ::Settings;
using namespace ::Settings::Builder;

class Home final : public Section<Home> {
public:
	Home(QWidget *parent, not_null<Window::SessionController*> controller)
	: Section(parent, controller) {
		const auto content = Ui::CreateChild<Ui::VerticalLayout>(this);
		build(content, kBuild);
		Ui::ResizeFitChild(this, content);
	}

	[[nodiscard]] rpl::producer<QString> title() override {
		return tr::lng_ikk_settings();
	}

	static const SectionBuildMethod kBuild;
};

const auto kMeta = BuildHelper({
	.id = Home::Id(),
	.parentId = MainId(),
	.title = &tr::lng_ikk_settings,
	.icon = &st::menuIconIkk,
}, [](SectionBuilder &builder) {
	builder.addButton({
		.title = tr::lng_ikk_settings(),
		.icon = { &st::menuIconIkk },
		.label = rpl::single(tr::lng_settings_current_version(
			tr::now, lt_version, currentVersionShortText())),
	});
	builder.addButton({
		.title = tr::lng_ikk_source_code(),
		.icon = { &st::menuIconLink },
		.onClick = [] {
			UrlClickHandler::Open(u"https://github.com/ikk-dev/Ikk"_q);
		},
	});
	builder.addSectionButton({
		.title = tr::lng_ikk_interface(),
		.targetSection = InterfaceId(),
		.icon = { &st::menuIconPalette },
		.keywords = { u"interface"_q, u"appearance"_q },
	});
	builder.addSectionButton({
		.title = tr::lng_ikk_messages(),
		.targetSection = MessagesId(),
		.icon = { &st::menuIconChatBubble },
		.keywords = { u"messages"_q, u"time"_q },
	});
	builder.addSectionButton({
		.title = tr::lng_ikk_chats(),
		.targetSection = ChatsId(),
		.icon = { &st::menuIconChats },
		.keywords = { u"chats"_q, u"list"_q },
	});
	builder.addSectionButton({
		.title = tr::lng_ikk_compose(),
		.targetSection = ComposeId(),
		.icon = { &st::menuIconShortcut },
		.keywords = { u"compose"_q, u"send"_q },
	});
	builder.addSectionButton({
		.title = tr::lng_ikk_media(),
		.targetSection = MediaId(),
		.icon = { &st::menuIconStickers },
		.keywords = { u"media"_q, u"sticker"_q, u"emoji"_q },
	});
	builder.addSectionButton({
		.title = tr::lng_ikk_menu(),
		.targetSection = MenuId(),
		.icon = { &st::menuIconShowAll },
		.keywords = { u"menu"_q, u"actions"_q },
	});
	builder.addSectionButton({
		.title = tr::lng_ikk_privacy(),
		.targetSection = PrivacyId(),
		.icon = { &st::menuIconLock },
		.keywords = { u"privacy"_q, u"phone"_q },
	});
	builder.addSectionButton({
		.title = tr::lng_ikk_services(),
		.targetSection = ServicesId(),
		.icon = { &st::menuIconTranslate },
		.keywords = { u"translation"_q, u"AI"_q, u"service"_q },
	});
	builder.addSectionButton({
		.title = tr::lng_ikk_rules(),
		.targetSection = RulesId(),
		.icon = { &st::menuIconTagFilter },
		.keywords = { u"filter"_q, u"link"_q },
	});
	builder.addSectionButton({
		.title = tr::lng_ikk_network(),
		.targetSection = NetworkId(),
		.icon = { &st::menuIconNetwork },
		.keywords = { u"network"_q, u"connection"_q, u"IPv6"_q },
	});
	builder.addSectionButton({
		.title = tr::lng_ikk_config_title(),
		.targetSection = ConfigId(),
		.icon = { &st::menuIconStorage },
		.keywords = { u"backup"_q, u"import"_q, u"export"_q },
	});
	builder.addDividerText(tr::lng_ikk_settings_note());
});

const SectionBuildMethod Home::kBuild = kMeta.build;

} // namespace

Settings::Type HomeId() {
	return Home::Id();
}

void AddSettingsEntry(SectionBuilder &builder) {
	builder.addSectionButton({
		.title = tr::lng_ikk_settings(),
		.targetSection = Home::Id(),
		.icon = { &st::menuIconIkk },
		.keywords = { u"Ikk"_q, u"desktop"_q },
	});
}

} // namespace Ikk
