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

#ifndef OGAM_MEDIAWIDGET_TEXTURE_PLUGIN_H
#define OGAM_MEDIAWIDGET_TEXTURE_PLUGIN_H

#include <QtCore/qglobal.h>
#include "plugin_media_widget_interface.h"

// Define import/export
#if defined(OGAM_MEDIAWIDGET_TEXTURE_PLUGIN_LIBRARY)
#  define MEDIAWIDGET_TEXTURE_PLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MEDIAWIDGET_TEXTURE_PLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

static const std::string MEDIAWIDGET_TEXTURE_PLUGIN_NAME = "OgamMediaWidgetTexturePlugin";
class AssetsDockWidget;
/****************************************************************************
 The OgamMediaWidgetTexturePlugin is an implementation of the
 PluginMediaWidgetInterface and creates a MediaWidget, based on extension
 of the asset.
 ***************************************************************************/
class MEDIAWIDGET_TEXTURE_PLUGINSHARED_EXPORT OgamMediaWidgetTexturePlugin : public PluginMediaWidgetInterface
{
    public:
        typedef QMap <std::string, QString> FallbackIcons;
        OgamMediaWidgetTexturePlugin (AssetsDockWidget* assetsDockWidget);
        virtual ~OgamMediaWidgetTexturePlugin (void) {}

        virtual const std::string& getName (void) const;
        virtual void install (void);
        virtual void initialise (void);
        virtual void shutdown (void);
        virtual void uninstall (void);
        virtual void resetWindowLayout (void) {}
        virtual MediaWidget* createMediaWidget (const AssetMetaData& assetMetaData);
        virtual const SupportedExtensions& getSupportedExtensions (void) const;

    protected:
        // Returns true if the extension is a supported texture
        bool OgamMediaWidgetTexturePlugin::isSupportedTexture (const std::string& extension);

        // Returns the filename of the icon, based on the extension
        const QString& getFallbackIcon (const std::string& extension) const;

        // Checks whether a file exists
        bool fileExist(const QString& fileName);

    private:
        AssetsDockWidget* mAssetsDockWidget;
        SupportedExtensions mSupportedExtensions;
        FallbackIcons mFallbackIcons;
        SupportedExtensions mSupportedTextures;
        QString mDummyQString;
};

static OgamMediaWidgetTexturePlugin* plugin;

/****************************************************************************
 Provide external access by the Ogam application:
 The function 'createPlugin' creates a static instance of OgamMediaWidgetTexturePlugin
 and returns it's pointer
 ***************************************************************************/
extern "C" MEDIAWIDGET_TEXTURE_PLUGINSHARED_EXPORT PluginInterface* createPlugin (AssetsDockWidget* assetsDockWidget)
{
    plugin = new OgamMediaWidgetTexturePlugin(assetsDockWidget);
    return plugin;
}

/****************************************************************************
 Provide external access by the Ogam application:
 The function 'deletePlugin' deletes the static instance of OgamMediaWidgetTexturePlugin
 ***************************************************************************/
extern "C" MEDIAWIDGET_TEXTURE_PLUGINSHARED_EXPORT void deletePlugin (void)
{
    delete plugin;
}

#endif
