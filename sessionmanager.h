#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H
#include <QString>
#include <QSettings>

class SessionManager {
public:
    static void saveSession(const QString &username, const QString &email) {
        QSettings settings("GridMasters", "Tic Tac Toe");
        settings.setValue("username", username);
        settings.setValue("email", email);
    }
    static void deleteSession() {
        QSettings settings("GridMasters", "Tic Tac Toe");
        settings.remove( "username");
        settings.remove( "email");
    }

    static void loadSession(QString &username, QString &email) {
        QSettings settings("GridMasters", "Tic Tac Toe");
        username = settings.value("username", "").toString();
        email = settings.value("email", "").toString();
    }
};

#endif // SESSIONMANAGER_H
