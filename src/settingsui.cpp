#include "settingsui.h"
#include <QDir>
#include <QDebug>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <unistd.h>

SettingsUi::SettingsUi(QObject *parent) :
    QObject(parent)
{
    /* Leaving this here for future needs */
    scanV4l2();
}

SettingsUi::~SettingsUi()
{
}

void SettingsUi::scanV4l2()
{
    QDir d("/dev/", "video?", QDir::Name | QDir::IgnoreCase, QDir::System);

    QStringList entries = d.entryList();

    foreach (const QString& dv, entries)
    {
        QString dev = d.absoluteFilePath(dv);
        struct v4l2_capability cap;
        memset(&cap, 0x0, sizeof(cap));

        qDebug() << "*** looking at" << dev << "***";

        int fd = open(dev.toLocal8Bit().constData(), O_RDONLY);
        if (fd == -1)
        {
            qDebug() << "failed to open";
            continue;
        }

        if (ioctl(fd, VIDIOC_QUERYCAP, &cap) != 0)
        {
            qDebug() << "query device capabilities failed";
            close(fd);
            continue;
        }

        close(fd);

        qDebug() << "driver" << (char *)cap.driver;
        qDebug() << "card" << (char *)cap.card;
        qDebug() << "bus" << (char *)cap.bus_info;
        qDebug() << "version" << (long)cap.version;
        qDebug() << "capabilities" << (long)cap.capabilities;
        qDebug() << "device caps" << (long)cap.device_caps;
    }
}
