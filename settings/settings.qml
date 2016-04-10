import QtQuick 2.0
import Sailfish.Silica 1.0
import org.nemomobile.configuration 1.0
import com.kimmoli.onyxcamerasettings 1.0

Page
{
    id: page

    property string viewfinderResolution_4_3: "1440x1080"
    property string viewfinderResolution_16_9: "1920x1080"

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

            SectionHeader
            {
                //: section header for primary camera settings
                //% "Rear camera"
                text: qsTrId("primary-camera-settings")
            }

            ComboBox
            {
                id: primary_image_resolution_combo
                //: Combobox label for image resolution
                //% "Image resolution"
                label: qsTrId("image-resolution")
                menu: ContextMenu {
                    Repeater
                    {
                        model: primary_image_resolutions_model
                        delegate: MenuItem {
                            text: resolution + " (" + aspectRatio + ")"
                            onClicked: set(primary_image_resolutions_model, index, primary_image_resolution_combo, primary_image_resolution, primary_image_viewfinder_resolution)
                        }
                    }
                }
            }
            ComboBox
            {
                id: primary_video_resolution_combo
                //: Combobox label for video resolution
                //% "Video resolution"
                label: qsTrId("video-resolution")
                menu: ContextMenu {
                    Repeater
                    {
                        model: primary_video_resolutions_model
                        delegate: MenuItem {
                            text: resolution + " (" + aspectRatio + ")"
                            onClicked: set(primary_video_resolutions_model, index, primary_video_resolution_combo, primary_video_resolution, primary_video_viewfinder_resolution)
                        }
                    }
                }
            }

            SectionHeader
            {
                //: section header for secondary camera settings
                //% "Front camera"
                text: qsTrId("secondary-camera-settings")
            }

            ComboBox
            {
                id: secondary_image_resolution_combo
                label: qsTrId("image-resolution")
                menu: ContextMenu {
                    Repeater
                    {
                        model: secondary_image_resolutions_model
                        delegate: MenuItem {
                            text: resolution + " (" + aspectRatio + ")"
                            onClicked: set(secondary_image_resolutions_model, index, secondary_image_resolution_combo, secondary_image_resolution, secondary_image_viewfinder_resolution)
                        }
                    }
                }
            }
            ComboBox
            {
                id: secondary_video_resolution_combo
                label: qsTrId("video-resolution")
                menu: ContextMenu {
                    Repeater
                    {
                        model: secondary_video_resolutions_model
                        delegate: MenuItem {
                            text: resolution + " (" + aspectRatio + ")"
                            onClicked: set(secondary_video_resolutions_model, index, secondary_video_resolution_combo, secondary_video_resolution, secondary_video_viewfinder_resolution)
                        }
                    }
                }
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

    ListModel
    {
        id: primary_image_resolutions_model
    }

    ListModel
    {
        id: primary_video_resolutions_model
    }

    ListModel
    {
        id: secondary_image_resolutions_model
    }

    ListModel
    {
        id: secondary_video_resolutions_model
    }

    Component.onCompleted:
    {
        request("./camera-resolutions.json", function(o)
        {
            var data = JSON.parse(o.responseText)

            var i
            for (i=0 ; i < data.primary.image.length ; i++)
                primary_image_resolutions_model.append({ resolution: data.primary.image[i].resolution,
                                                  aspectRatio: data.primary.image[i].aspectRatio })
            update(primary_image_resolutions_model, primary_image_resolution_combo, primary_image_resolution)

            for (i=0 ; i < data.primary.video.length ; i++)
                primary_video_resolutions_model.append({ resolution: data.primary.video[i].resolution,
                                                  aspectRatio: data.primary.video[i].aspectRatio })
            update(primary_video_resolutions_model, primary_video_resolution_combo, primary_video_resolution)

            for (i=0 ; i < data.secondary.image.length ; i++)
                secondary_image_resolutions_model.append({ resolution: data.secondary.image[i].resolution,
                                                  aspectRatio: data.secondary.image[i].aspectRatio })
            update(secondary_image_resolutions_model, secondary_image_resolution_combo, secondary_image_resolution)

            for (i=0 ; i < data.secondary.video.length ; i++)
                secondary_video_resolutions_model.append({ resolution: data.secondary.video[i].resolution,
                                                  aspectRatio: data.secondary.video[i].aspectRatio })
            update(secondary_video_resolutions_model, secondary_video_resolution_combo, secondary_video_resolution)

            viewfinderResolution_4_3 = data.viewfinder.viewfinderResolution_4_3
            viewfinderResolution_16_9 = data.viewfinder.viewfinderResolution_16_9
        })
    }

    function set(model, index, combo, confval, vfconfval)
    {
        var d = model.get(index)
        confval.value = d.resolution
        if (d.aspectRatio == "4:3")
            vfconfval.value = viewfinderResolution_4_3
        else if (d.aspectRatio == "16:9")
            vfconfval.value = viewfinderResolution_16_9

        update(model, combo, confval)
    }

    function update(model, combo, confval)
    {
        combo._updating = false
        for (var i=0 ; i<model.count; i++)
        {
            console.log("ir " + model.get(i).resolution + " cv " + confval.value)
            if (model.get(i).resolution == confval.value)
            {
                combo.currentIndex = i
                break
            }
        }
    }

    function request(url, callback)
    {
        var xhr = new XMLHttpRequest();
        xhr.onreadystatechange = (function(myxhr)
        {
            return function()
            {
                if(myxhr.readyState === 4) callback(myxhr);
            }
        })(xhr);
        xhr.open('GET', url, true);
        xhr.send('');
    }
}

