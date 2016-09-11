#include <QtGlobal>
#include <QtQml>
#include <QQmlEngine>
#include <QQmlExtensionPlugin>
#include <QTranslator>
#include "settingsui.h"

class Translator : public QTranslator
{
public:
    Translator(QObject *parent)
        : QTranslator(parent)
    {
        qApp->installTranslator(this);
    }

    ~Translator()
    {
        qApp->removeTranslator(this);
    }
};

class Q_DECL_EXPORT CameraSettingsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "com.kimmoli.camerasettings")
#endif
public:
    CameraSettingsPlugin()
    {
    }

    virtual ~CameraSettingsPlugin()
    {
    }

    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("com.kimmoli.camerasettings"));

        qmlRegisterType<SettingsUi>(uri, 1, 0, "CameraSettings");
    }

    void initializeEngine(QQmlEngine *engine, const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("com.kimmoli.camerasettings"));

        Translator *engineeringEnglish = new Translator(engine);
        if (!engineeringEnglish->load("camera-settings_eng_en", "/usr/share/translations"))
            qWarning() << "failed loading translator" << "camera-settings_eng_en";

        Translator *translator = new Translator(engine);
        if (!translator->load(QLocale(), "camera-settings", "-", "/usr/share/translations"))
            qWarning() << "failed loading translator" << "camera-settings" << QLocale();

        QQmlExtensionPlugin::initializeEngine(engine, uri);
    }
};

#include "plugin.moc"
