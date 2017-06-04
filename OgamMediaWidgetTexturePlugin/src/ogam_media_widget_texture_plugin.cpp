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
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include "assets_dockwidget.h"
#include "media_widget_texture_constants.h"
#include "ogam_media_widget_texture_plugin.h"

//****************************************************************************/
OgamMediaWidgetTexturePlugin::OgamMediaWidgetTexturePlugin (AssetsDockWidget* assetsDockWidget) :
    mAssetsDockWidget(assetsDockWidget)
{
    mSupportedExtensions.push_back("default"); // This plugin creates a default MediaWidget when all other available plugins cannot create the MediaWidget
    mSupportedExtensions.push_back("jpg");
    mSupportedExtensions.push_back("jpeg");
    mSupportedExtensions.push_back("gif");
    mSupportedExtensions.push_back("ico");
    mSupportedExtensions.push_back("svg");
    mSupportedExtensions.push_back("tga");
    mSupportedExtensions.push_back("tiff");
    mSupportedExtensions.push_back("bmp");
    mSupportedExtensions.push_back("webp");

    // Default icons for major tools
    mSupportedExtensions.push_back("max");
    mSupportedExtensions.push_back("fbx");
    mSupportedExtensions.push_back("3ds");
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
    // TODO: Create a subclass of MediaWidget, but use a MediaWidget for testing purposes
    // TEST
    MediaWidget* mediaWidget = new MediaWidget (assetMetaData);
    QPixmap pixmap;
    if (assetMetaData.extension == "max" ||
        assetMetaData.extension == "fbx" ||
        assetMetaData.extension == "3ds")
        pixmap.load(PLUGIN_ICON_PATH + PLUGIN_3D_MODEL_IMAGE);
    else
        pixmap.load(PLUGIN_ICON_PATH + PLUGIN_NO_IMAGE);
    QLabel* label = new QLabel();
    QHBoxLayout* layout = new QHBoxLayout;
    label->setPixmap(pixmap);
    label->setScaledContents(true);
    layout->addWidget(label);
    mediaWidget->setLayout(layout);
    QSize size(100, 100);
    mediaWidget->setMinimumSize(size);
    mediaWidget->setMaximumSize(size);
    mediaWidget->setMouseTracking(true);
    return mediaWidget;
}

//****************************************************************************/
const PluginMediaWidgetInterface::SupportedExtensions& OgamMediaWidgetTexturePlugin::getSupportedExtensions (void) const
{
    return mSupportedExtensions;
}
