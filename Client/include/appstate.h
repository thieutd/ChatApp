#ifndef APPSTATE_H
#define APPSTATE_H

#include <QMetaEnum>

namespace AppStateNameSpace {
Q_NAMESPACE

enum class AppState { Unknown, Initializing, AuthCheck, Login, Main, LoggedOut, Final };
Q_ENUM_NS(AppState)

} // namespace AppStateNameSpace
using AppStateNameSpace::AppState;

#endif // APPSTATE_H
