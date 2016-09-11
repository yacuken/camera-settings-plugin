#ifndef SETTINGSUI_H
#define SETTINGSUI_H
#include <QObject>

class Q_DECL_EXPORT SettingsUi : public QObject
{
    Q_OBJECT

public:
    explicit SettingsUi(QObject *parent = 0);
    virtual ~SettingsUi();

};


#endif // SETTINGSUI_H
