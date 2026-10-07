#pragma once

#include <gsl/pointers>

namespace Window {
class SessionController;
} // namespace Window

namespace Ikk::Chats {

void ShowCleanup(gsl::not_null<Window::SessionController*> controller);

} // namespace Ikk::Chats
