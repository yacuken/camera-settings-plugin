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

class Q_DECL_EXPORT OnyxCameraSettingsPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
#if QT_VERSION >= QT_VERSION_CHECK(5, 0, 0)
    Q_PLUGIN_METADATA(IID "com.kimmoli.onyxcamerasettings")
#endif
public:
    OnyxCameraSettingsPlugin()
    {
    }

    virtual ~OnyxCameraSettingsPlugin()
    {
    }

    void registerTypes(const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("com.kimmoli.onyxcamerasettings"));

        qmlRegisterType<SettingsUi>(uri, 1, 0, "CameraSettings");
    }

    void initializeEngine(QQmlEngine *engine, const char *uri)
    {
        Q_ASSERT(uri == QLatin1String("com.kimmoli.onyxcamerasettings"));

        Translator *engineeringEnglish = new Translator(engine);
        if (!engineeringEnglish->load("onyx-camera-settings_eng_en", "/usr/share/translations"))
            qWarning() << "failed loading translator" << "onyx-camera-settings_eng_en";

        Translator *translator = new Translator(engine);
        if (!translator->load(QLocale(), "onyx-camera-settings", "-", "/usr/share/translations"))
            qWarning() << "failed loading translator" << "onyx-camera-settings" << QLocale();

        QQmlExtensionPlugin::initializeEngine(engine, uri);
    }
};

#include "plugin.moc"
