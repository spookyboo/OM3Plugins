/****************************************************************************
**
** Copyright (C) 2017, Henry van Merode
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/

#include <QLabel>
#include <QPixmap>
#include <QImageReader>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <algorithm>
#include "assets_dockwidget.h"
#include "media_widget_image_constants.h"
#include "media_image_widget.h"
#include "OM3_media_widget_image_plugin.h"

//****************************************************************************/
OM3MediaWidgetImagePlugin::OM3MediaWidgetImagePlugin (AssetsDockWidget* assetsDockWidget)
{
    setAssetsDockWidget(assetsDockWidget);
    mDummyQString = QString("");

    // Define which IMAGES are supported by this plugin; add them also to the supported extensions vector
    mSupportedImages.push_back("png");
    mSupportedImages.push_back("jpg");
    mSupportedImages.push_back("jpeg");
    mSupportedImages.push_back("gif");
    mSupportedImages.push_back("ico");
    mSupportedImages.push_back("svg");
    mSupportedImages.push_back("tga");
    mSupportedImages.push_back("tiff");
    mSupportedImages.push_back("bmp");
    mSupportedImages.push_back("webp");
    mSupportedExtensions = mSupportedImages;

    /* Add other extensions, to indicate that more extensions are supported (although this only results in displaying an icon)
     * Include a reference to the fallback icon
    */
    mSupportedExtensions.push_back("default"); // This plugin creates a default MediaWidget when all other available plugins cannot create the MediaWidget

    // 3d Model formats
    mSupportedExtensions.push_back("3ds"); // 3D studio (old)
    mSupportedExtensions.push_back("blend"); // blender
    mSupportedExtensions.push_back("dae"); // collada
    mSupportedExtensions.push_back("fbx");
    mSupportedExtensions.push_back("max");
    mSupportedExtensions.push_back("mesh"); // Ogre3d
    mSupportedExtensions.push_back("mtl");
    mSupportedExtensions.push_back("obj"); // wavefront
    mFallbackIcons["3ds"] = PLUGIN_ICON_PATH + PLUGIN_ICON_3D_MODEL_DEFAULT;
    mFallbackIcons["blend"] = PLUGIN_ICON_PATH + PLUGIN_ICON_3D_MODEL_BLEND;
    mFallbackIcons["dae"] = PLUGIN_ICON_PATH + PLUGIN_ICON_3D_MODEL_BLEND;
    mFallbackIcons["fbx"] = PLUGIN_ICON_PATH + PLUGIN_ICON_3D_MODEL_DEFAULT;
    mFallbackIcons["max"] = PLUGIN_ICON_PATH + PLUGIN_ICON_3D_MODEL_DEFAULT;
    mFallbackIcons["mesh"] = PLUGIN_ICON_PATH + PLUGIN_ICON_3D_MODEL_MESH;
    mFallbackIcons["mtl"] = PLUGIN_ICON_PATH + PLUGIN_ICON_3D_MODEL_MESH;
    mFallbackIcons["obj"] = PLUGIN_ICON_PATH + PLUGIN_ICON_3D_MODEL_OBJ;

    // Audio formats
    mSupportedExtensions.push_back("aiff");
    mSupportedExtensions.push_back("mp3");
    mSupportedExtensions.push_back("ogg");
    mSupportedExtensions.push_back("flac");
    mSupportedExtensions.push_back("wav");
    mSupportedExtensions.push_back("wma");
    mFallbackIcons["aiff"] = PLUGIN_ICON_PATH + PLUGIN_ICON_AUDIO_DEFAULT;
    mFallbackIcons["mp3"] = PLUGIN_ICON_PATH + PLUGIN_ICON_AUDIO_DEFAULT;
    mFallbackIcons["ogg"] = PLUGIN_ICON_PATH + PLUGIN_ICON_AUDIO_DEFAULT;
    mFallbackIcons["flac"] = PLUGIN_ICON_PATH + PLUGIN_ICON_AUDIO_DEFAULT;
    mFallbackIcons["wav"] = PLUGIN_ICON_PATH + PLUGIN_ICON_AUDIO_DEFAULT;
    mFallbackIcons["wma"] = PLUGIN_ICON_PATH + PLUGIN_ICON_AUDIO_DEFAULT;

    // Video formats
    mSupportedExtensions.push_back("avi");
    mSupportedExtensions.push_back("flv");
    mSupportedExtensions.push_back("mkv");
    mSupportedExtensions.push_back("mp4");
    mSupportedExtensions.push_back("mpg");
    mSupportedExtensions.push_back("mov");
    mSupportedExtensions.push_back("mts");
    mSupportedExtensions.push_back("vob");
    mSupportedExtensions.push_back("wmv");
    mFallbackIcons["avi"] = PLUGIN_ICON_PATH + PLUGIN_ICON_VIDEO_DEFAULT;
    mFallbackIcons["flv"] = PLUGIN_ICON_PATH + PLUGIN_ICON_VIDEO_DEFAULT;
    mFallbackIcons["mkv"] = PLUGIN_ICON_PATH + PLUGIN_ICON_VIDEO_DEFAULT;
    mFallbackIcons["mp4"] = PLUGIN_ICON_PATH + PLUGIN_ICON_VIDEO_DEFAULT;
    mFallbackIcons["mpg"] = PLUGIN_ICON_PATH + PLUGIN_ICON_VIDEO_DEFAULT;
    mFallbackIcons["mov"] = PLUGIN_ICON_PATH + PLUGIN_ICON_VIDEO_DEFAULT;
    mFallbackIcons["mts"] = PLUGIN_ICON_PATH + PLUGIN_ICON_VIDEO_DEFAULT;
    mFallbackIcons["vob"] = PLUGIN_ICON_PATH + PLUGIN_ICON_VIDEO_DEFAULT;
    mFallbackIcons["wmv"] = PLUGIN_ICON_PATH + PLUGIN_ICON_VIDEO_DEFAULT;

    // Fonts
    mSupportedExtensions.push_back("ttf");
    mFallbackIcons["ttf"] = PLUGIN_ICON_PATH + PLUGIN_ICON_FONT_DEFAULT;

    // Non-media formats (sometimes used for media though)
    mSupportedExtensions.push_back("zip");
    mFallbackIcons["zip"] = PLUGIN_ICON_PATH + PLUGIN_ICON_ZIP;
    mFallbackIcons["7z"] = PLUGIN_ICON_PATH + PLUGIN_ICON_7ZIP;
}

//****************************************************************************/
const std::string& OM3MediaWidgetImagePlugin::getName (void) const
{
    return MEDIAWIDGET_IMAGE_PLUGIN_NAME;
}

//****************************************************************************/
void OM3MediaWidgetImagePlugin::install (void)
{
}

//****************************************************************************/
void OM3MediaWidgetImagePlugin::initialise (void)
{
}

//****************************************************************************/
void OM3MediaWidgetImagePlugin::shutdown (void)
{
}

//****************************************************************************/
void OM3MediaWidgetImagePlugin::uninstall (void)
{
}

//****************************************************************************/
MediaWidget* OM3MediaWidgetImagePlugin::createMediaWidget (AssetMetaData* assetMetaData, QWidget* parent)
{
    QSize size(120, 120);
    QPixmap pixmap;
    QImage image;
    if (isSupportedImage (assetMetaData->extensionOrMimeType))
    {
        if (assetMetaData->fullQualifiedFileNamePulled == "" || !fileExist(assetMetaData->fullQualifiedFileNamePulled.c_str()))
        {
            // TODO: Try to retrieve it first from the resource provider
        }

        if (assetMetaData->fullQualifiedFileNamePulled != "" && fileExist(assetMetaData->fullQualifiedFileNamePulled.c_str()))
        {
            try
            {
                // Decrease the image, otherwise it cannot be loaded by the pixmap
                QImageReader reader(assetMetaData->fullQualifiedFileNamePulled.c_str());
                reader.setScaledSize(size); // Prevents from reading to much data in memory
                image = reader.read();
                pixmap.convertFromImage(image);
            }
            catch (QException e)
            {
                pixmap.load(PLUGIN_ICON_PATH + PLUGIN_ICON_NO_IMAGE);
            }
        }
        else
        {
            pixmap.load(PLUGIN_ICON_PATH + PLUGIN_ICON_NO_IMAGE);
        }
    }
    else
    {
        // It is a non-image or an unsupported image, so try to use a fallback icon
        QString fileNameIcon = getFallbackIcon (assetMetaData->extensionOrMimeType);
        if (fileNameIcon == "")
        {
            // It is not supported at all, so use a default
            pixmap.load(PLUGIN_ICON_PATH + PLUGIN_ICON_ASSET_DEFAULT);
        }
        else
        {
            pixmap.load(fileNameIcon);
        }
    }

    MediaImageWidget* mediaImageWidget = new MediaImageWidget (assetMetaData, pixmap);
    mediaImageWidget->setMinimumSize(size);
    mediaImageWidget->setMaximumSize(size);
    return mediaImageWidget;
}

//****************************************************************************/
const PluginMediaWidgetInterface::SupportedExtensions& OM3MediaWidgetImagePlugin::getSupportedExtensions (void) const
{
    return mSupportedExtensions;
}

//****************************************************************************/
const QString& OM3MediaWidgetImagePlugin::getFallbackIcon (const std::string& extension) const
{
    FallbackIcons::const_iterator it = mFallbackIcons.find(extension);
    if (it != mFallbackIcons.end())
    {
        return it.value();
    }

    return mDummyQString;
}

//****************************************************************************/
bool OM3MediaWidgetImagePlugin::isSupportedImage (const std::string& extension)
{
    std::string nonConstextension = extension;
    std::transform(nonConstextension.begin(), nonConstextension.end(), nonConstextension.begin(), ::tolower);
    SupportedExtensions::iterator it = mSupportedImages.begin();
    SupportedExtensions::iterator itEnd = mSupportedImages.end();
    while (it != itEnd)
    {
        if (nonConstextension == *it)
            return true;

        ++it;
    }
    return false;
}

//****************************************************************************/
bool OM3MediaWidgetImagePlugin::fileExist(const QString& fileName)
{
    QFileInfo checkFile(fileName);
    return (checkFile.exists() && checkFile.isFile());
}

