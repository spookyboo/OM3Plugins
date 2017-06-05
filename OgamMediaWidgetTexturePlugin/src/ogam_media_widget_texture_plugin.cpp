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
#include "assets_dockwidget.h"
#include "media_widget_texture_constants.h"
#include "media_texture_widget.h"
#include "ogam_media_widget_texture_plugin.h"

//****************************************************************************/
OgamMediaWidgetTexturePlugin::OgamMediaWidgetTexturePlugin (AssetsDockWidget* assetsDockWidget) :
    mAssetsDockWidget(assetsDockWidget)
{
    mDummyQString = QString("");

    // Define which TEXTURES are supported by this plugin; add them also to the supported extensions vector
    mSupportedTextures.push_back("png");
    mSupportedTextures.push_back("jpg");
    mSupportedTextures.push_back("jpeg");
    mSupportedTextures.push_back("gif");
    mSupportedTextures.push_back("ico");
    mSupportedTextures.push_back("svg");
    mSupportedTextures.push_back("tga");
    mSupportedTextures.push_back("tiff");
    mSupportedTextures.push_back("bmp");
    mSupportedTextures.push_back("webp");
    mSupportedExtensions = mSupportedTextures;

    // Add other extensions, to indicate that more extensions are supported (although this only results in displaying an icon)
    mSupportedExtensions.push_back("default"); // This plugin creates a default MediaWidget when all other available plugins cannot create the MediaWidget
    mSupportedExtensions.push_back("max");
    mSupportedExtensions.push_back("fbx");
    mSupportedExtensions.push_back("3ds");
    mSupportedExtensions.push_back("obj");
    mSupportedExtensions.push_back("blend");

    // Define fallback icons for non-texture extensions
    mFallbackIcons["max"] = PLUGIN_ICON_PATH + PLUGIN_3D_MODEL_MAX;
    mFallbackIcons["fbx"] = PLUGIN_ICON_PATH + PLUGIN_3D_MODEL_DEFAULT;
    mFallbackIcons["3ds"] = PLUGIN_ICON_PATH + PLUGIN_3D_MODEL_DEFAULT;
    mFallbackIcons["obj"] = PLUGIN_ICON_PATH + PLUGIN_3D_MODEL_OBJ;
    mFallbackIcons["blend"] = PLUGIN_ICON_PATH + PLUGIN_3D_MODEL_BLEND;
}

//****************************************************************************/
const std::string& OgamMediaWidgetTexturePlugin::getName (void) const
{
    return MEDIAWIDGET_TEXTURE_PLUGIN_NAME;
}

//****************************************************************************/
void OgamMediaWidgetTexturePlugin::install (void)
{
}

//****************************************************************************/
void OgamMediaWidgetTexturePlugin::initialise (void)
{
}

//****************************************************************************/
void OgamMediaWidgetTexturePlugin::shutdown (void)
{
}

//****************************************************************************/
void OgamMediaWidgetTexturePlugin::uninstall (void)
{
}

//****************************************************************************/
MediaWidget* OgamMediaWidgetTexturePlugin::createMediaWidget (const AssetMetaData& assetMetaData)
{
    QSize size(120, 120);
    QPixmap pixmap;
    QImage image;
    if (isSupportedTexture (assetMetaData.extension))
    {
        // The extension refers to a texture, supported by this plugin, so display the texture
        if (fileExist(assetMetaData.fullQualifiedFileNameOrReference.c_str()))
        {
            try
            {
                // Decrease the texture, otherwise it cannot be loaded by the pixmap
                QImageReader reader(assetMetaData.fullQualifiedFileNameOrReference.c_str());
                reader.setScaledSize(size); // Prevents from reading to much data in memory
                image = reader.read();
                pixmap.convertFromImage(image);
            }
            catch (QException e)
            {
                pixmap.load(PLUGIN_ICON_PATH + PLUGIN_NO_IMAGE);
            }
        }
        else
        {
            pixmap.load(PLUGIN_ICON_PATH + PLUGIN_NO_IMAGE);
        }
    }
    else
    {
        // It is a non-texture or an unsupported texture, so try to use a fallback icon
        QString fileNameIcon = getFallbackIcon (assetMetaData.extension);
        if (fileNameIcon == "")
        {
            // It is not supported at all, so use a default
            pixmap.load(PLUGIN_ICON_PATH + PLUGIN_NO_IMAGE);
        }
        else
        {
            pixmap.load(fileNameIcon);
        }
    }

    MediaTextureWidget* mediaTextureWidget = new MediaTextureWidget (assetMetaData, pixmap);
    mediaTextureWidget->setMinimumSize(size);
    mediaTextureWidget->setMaximumSize(size);
    return mediaTextureWidget;
}

//****************************************************************************/
const PluginMediaWidgetInterface::SupportedExtensions& OgamMediaWidgetTexturePlugin::getSupportedExtensions (void) const
{
    return mSupportedExtensions;
}

//****************************************************************************/
const QString& OgamMediaWidgetTexturePlugin::getFallbackIcon (const std::string& extension) const
{
    FallbackIcons::const_iterator it = mFallbackIcons.find(extension);
    if (it != mFallbackIcons.end())
    {
        return it.value();
    }

    return mDummyQString;
}

//****************************************************************************/
bool OgamMediaWidgetTexturePlugin::isSupportedTexture (const std::string& extension)
{
    SupportedExtensions::iterator it = mSupportedTextures.begin();
    SupportedExtensions::iterator itEnd = mSupportedTextures.end();
    while (it != itEnd)
    {
        if (extension == *it)
            return true;

        ++it;
    }
    return false;
}

//****************************************************************************/
bool OgamMediaWidgetTexturePlugin::fileExist(const QString& fileName)
{
    QFileInfo checkFile(fileName);
    return (checkFile.exists() && checkFile.isFile());
}

