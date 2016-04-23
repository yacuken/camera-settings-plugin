#include "settingsui.h"
#include <QDir>
#include <QDebug>
#include <QSize>
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
    QList<QSize> res;

    // Too bad there's no way to get the values of an enum without creating the element :(
    GstElement *elem = gst_element_factory_make("droidcamsrc", NULL);
    if (!elem)
    {
        qWarning() << "QtCamScanner: Failed to create an instance of droidcamsrc";
        return;
    }

    GParamSpec *spec = g_object_class_find_property(G_OBJECT_GET_CLASS(elem), "camera-device");
    if (!spec)
    {
        qWarning() << "QtCamScanner: Failed to get property camera-device";
        gst_object_unref(elem);
        return;
    }

    if (!G_IS_PARAM_SPEC_ENUM(spec))
    {
        qWarning() << "QtCamScanner: Property camera-device is not an enum";
        gst_object_unref(elem);
        return;
    }

    GParamSpecEnum *e = G_PARAM_SPEC_ENUM(spec);
    // First add the default:
    devices << qMakePair<QString, QVariant>(e->enum_class->values[e->default_value].value_name,
                        QByteArray::number(e->default_value));

    qDebug() << "default" << devices;

    for (int x = e->enum_class->minimum; x <= e->enum_class->maximum; x++)
    {
        if (x != e->default_value)
        {
            devices << qMakePair<QString, QVariant>(e->enum_class->values[x].value_name, QByteArray::number(x));
        }
    }

    qDebug() << "all" << devices;

    GstElement *cameraBin = gst_element_factory_make("camerabin", NULL);
    if (!cameraBin)
    {
        qWarning() << "failed to create cameraBin";
        gst_object_unref(elem);
        return;
    }

    GstElement *videoSource = gst_element_factory_make("droidcamsrc", NULL);
    if (!videoSource)
    {
        qWarning() << "failed to create videoSource";
        gst_object_unref(elem);
        gst_object_unref(cameraBin);
        return;
    }

    qDebug() << "using device" << devices.at(0).second.toInt() << devices.at(0).first;
    g_object_set(videoSource, "camera-device", devices.at(0).second.toInt(), NULL);

    qDebug() << "setting camera source";
    g_object_set(cameraBin, "camera-source", videoSource, NULL);

    qDebug() << "getting caps";
    GstCaps *caps = NULL;
    g_object_get(cameraBin, "image-capture-supported-caps", &caps, NULL);

    if (!caps)
    {
        qWarning() << "no caps";
        gst_object_unref(elem);
        return;
    }

    for (guint x = 0; x < gst_caps_get_size(caps); x++)
    {
        const GstStructure *s = gst_caps_get_structure(caps, x);
        const GValue *width = gst_structure_get_value(s, "width");
        const GValue *height = gst_structure_get_value(s, "height");

        if (!width || !height)
        {
            qWarning() << "queryResolutions: no dimensions";
            continue;
        }

        bool width_is_list = GST_VALUE_HOLDS_LIST(width) ? true : false;
        bool height_is_list = GST_VALUE_HOLDS_LIST(height) ? true : false;

        if (!width_is_list && !height_is_list)
        {
            res << QSize(g_value_get_int(width), g_value_get_int(height));
        }
        else if (width_is_list && height_is_list)
        {
            guint ws = gst_value_list_get_size(width);
            guint hs = gst_value_list_get_size(width);
            for (guint wc = 0; wc < ws; wc++)
            {
                int w = g_value_get_int(gst_value_list_get_value(width, wc));
                for (guint hc = 0; hc < hs; hc++)
                {
                    int h = g_value_get_int(gst_value_list_get_value(height, hc));
                    res << QSize(w, h);
                }
            }
        }
        else if (width_is_list)
        {
            int h = g_value_get_int(height);
            for (guint i = 0; i < gst_value_list_get_size(width); i++)
            {
                int w = g_value_get_int(gst_value_list_get_value(width, i));
                res << QSize(w, h);
            }
        }
        else if (height_is_list)
        {
            int w = g_value_get_int(width);
            for (guint i = 0; i < gst_value_list_get_size(height); i++)
            {
                int h = g_value_get_int(gst_value_list_get_value(height, i));
                res << QSize(w, h);
            }
        }
    }

    qDebug() << res;

    gst_caps_unref(caps);
    gst_object_unref(elem);
}
