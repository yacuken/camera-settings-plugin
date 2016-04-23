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
    QList<QPair<QString, QVariant> > devices;

    foreach (const QString& dv, entries)
    {
        QString dev = d.absoluteFilePath(dv);
        struct v4l2_capability cap;
        memset(&cap, 0x0, sizeof(cap));

        int fd = open(dev.toLocal8Bit().constData(), O_RDONLY);
        if (fd == -1)
        {
            continue;
        }

        if (ioctl(fd, VIDIOC_QUERYCAP, &cap) != 0)
        {
            close(fd);
            continue;
        }

        close(fd);

        if (cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)
        {
            devices << qMakePair<QString, QVariant>((char *)cap.card, dev.toLocal8Bit());
        }
    }
    qDebug() << devices;
}
