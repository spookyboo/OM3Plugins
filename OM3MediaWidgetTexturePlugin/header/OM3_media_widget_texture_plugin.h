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

#ifndef OM3_MEDIAWIDGET_TEXTURE_PLUGIN_H
#define OM3_MEDIAWIDGET_TEXTURE_PLUGIN_H

#include <QtCore/qglobal.h>
#include "plugin_media_widget_interface.h"

// Define import/export
#if defined(OM3_MEDIAWIDGET_TEXTURE_PLUGIN_LIBRARY)
#  define MEDIAWIDGET_TEXTURE_PLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MEDIAWIDGET_TEXTURE_PLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

static const std::string MEDIAWIDGET_TEXTURE_PLUGIN_NAME = "OM3MediaWidgetTexturePlugin";
class AssetsDockWidget;
/****************************************************************************
 The OM3MediaWidgetTexturePlugin is an implementation of the
 PluginMediaWidgetInterface and creates a MediaWidget, based on extension
 of the asset.
 ***************************************************************************/
class MEDIAWIDGET_TEXTURE_PLUGINSHARED_EXPORT OM3MediaWidgetTexturePlugin : public PluginMediaWidgetInterface
{
    public:
        typedef QMap <std::string, QString> FallbackIcons;
        OM3MediaWidgetTexturePlugin (AssetsDockWidget* assetsDockWidget);
        virtual ~OM3MediaWidgetTexturePlugin (void) {}

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
        bool OM3MediaWidgetTexturePlugin::isSupportedTexture (const std::string& extension);

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

static OM3MediaWidgetTexturePlugin* plugin;

/****************************************************************************
 Provide external access by the OM3 application:
 The function 'createPlugin' creates a static instance of OM3MediaWidgetTexturePlugin
 and returns it's pointer
 ***************************************************************************/
extern "C" MEDIAWIDGET_TEXTURE_PLUGINSHARED_EXPORT PluginInterface* createPlugin (AssetsDockWidget* assetsDockWidget)
{
    plugin = new OM3MediaWidgetTexturePlugin(assetsDockWidget);
    return plugin;
}

/****************************************************************************
 Provide external access by the OM3 application:
 The function 'deletePlugin' deletes the static instance of OM3MediaWidgetTexturePlugin
 ***************************************************************************/
extern "C" MEDIAWIDGET_TEXTURE_PLUGINSHARED_EXPORT void deletePlugin (void)
{
    delete plugin;
}

#endif
