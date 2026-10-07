#pragma once

#include "base/basic_types.h"

class HistoryItem;
namespace Ui {
class PopupMenu;
} // namespace Ui
namespace Window {
class SessionController;
} // namespace Window

namespace Ikk::Menu {

void InsertMessageToolActions(
	Ui::PopupMenu *menu,
	HistoryItem *item,
	Window::SessionController *controller,
	Fn<void(HistoryItem*)> select);

} // namespace Ikk::Menu
