import QtQuick 2.0
import Sailfish.Silica 1.0
import org.nemomobile.configuration 1.0
import com.kimmoli.onyxcamerasettings 1.0

Page
{
    id: page

    SilicaFlickable
    {
        id: flick
        anchors.fill: parent

        contentHeight: column.height

        Column
        {
            id: column

            width: page.width

            PageHeader
            {
                //: page header
                //% "Camera settings"
                title: qsTrId("onyx-camera-settings-title")
            }
            
            Label
            {
                text: primary_image_resolution.value
            }
            Label
            {
                text: primary_image_viewfinder_resolution.value
            }
            Label
            {
                text: primary_video_resolution.value
            }
            Label
            {
                text: primary_video_viewfinder_resolution.value
            }
            
            Label
            {
                text: secondary_image_resolution.value
            }
            Label
            {
                text: secondary_image_viewfinder_resolution.value
            }
            Label
            {
                text: secondary_video_resolution.value
            }
            Label
            {
                text: secondary_video_viewfinder_resolution.value
            }
            
        }
    }    

    ConfigurationValue
    {
        id: primary_image_resolution
        key: "/apps/jolla-camera/primary/image/imageResolution"
    }
    ConfigurationValue
    {
        id: primary_image_viewfinder_resolution
        key: "/apps/jolla-camera/primary/image/viewfinderResolution"
    }
    ConfigurationValue
    {
        id: primary_video_resolution
        key: "/apps/jolla-camera/primary/video/videoResolution"
    }
    ConfigurationValue
    {
        id: primary_video_viewfinder_resolution
        key: "/apps/jolla-camera/primary/video/viewfinderResolution"
    }
    ConfigurationValue
    {
        id: secondary_image_resolution
        key: "/apps/jolla-camera/secondary/image/imageResolution"
    }
    ConfigurationValue
    {
        id: secondary_image_viewfinder_resolution
        key: "/apps/jolla-camera/secondary/image/viewfinderResolution"
    }
    ConfigurationValue
    {
        id: secondary_video_resolution
        key: "/apps/jolla-camera/secondary/video/videoResolution"
    }
    ConfigurationValue
    {
        id: secondary_video_viewfinder_resolution
        key: "/apps/jolla-camera/secondary/video/viewfinderResolution"
    }
}

