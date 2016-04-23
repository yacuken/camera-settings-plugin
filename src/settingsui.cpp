#include "settingsui.h"
#include <QDir>
#include <QDebug>
#include <gst/gst.h>

SettingsUi::SettingsUi(QObject *parent) :
    QObject(parent)
{
    qDebug() << "hoplaa!";
    gst_init(0, 0);
    scan();
}

SettingsUi::~SettingsUi()
{
}

void SettingsUi::scan()
{
    QList<QPair<QString, QVariant> > devices;

    // Too bad there's no way to get the values of an enum without creating the element :(
    GstElement *elem = gst_element_factory_make("droidcamsrc", NULL);
    if (!elem) {
      qWarning() << "QtCamScanner: Failed to create an instance of droidcamsrc";
      return;
    }

    GParamSpec *spec = g_object_class_find_property(G_OBJECT_GET_CLASS(elem), "camera-device");
    if (!spec) {
      qWarning() << "QtCamScanner: Failed to get property caemra-device";
      gst_object_unref(elem);
      return;
    }

    if (!G_IS_PARAM_SPEC_ENUM(spec)) {
      qWarning() << "QtCamScanner: Property camera-device is not an enum";
      gst_object_unref(elem);
      return;
    }

    GParamSpecEnum *e = G_PARAM_SPEC_ENUM(spec);
    // First add the default:
    devices << qMakePair<QString, QVariant>(e->enum_class->values[e->default_value].value_name,
                        QByteArray::number(e->default_value));

    qDebug() << "default" << devices;

    for (int x = e->enum_class->minimum; x <= e->enum_class->maximum; x++) {
      if (x != e->default_value) {
        devices << qMakePair<QString, QVariant>(e->enum_class->values[x].value_name,
                            QByteArray::number(x));
      }
    }

    qDebug() << "all" << devices;

    gst_object_unref(elem);
}
