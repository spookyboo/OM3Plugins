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

#ifndef OM3_MEDIAWIDGET_IMAGE_PLUGIN_H
#define OM3_MEDIAWIDGET_IMAGE_PLUGIN_H

#include <QtCore/qglobal.h>
#include "plugin_media_widget_interface.h"

// Define import/export
#if defined(OM3_MEDIAWIDGET_IMAGE_PLUGIN_LIBRARY)
#  define MEDIAWIDGET_IMAGE_PLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MEDIAWIDGET_IMAGE_PLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

static const std::string MEDIAWIDGET_IMAGE_PLUGIN_NAME = "OM3MediaWidgetImagePlugin";
class AssetsDockWidget;
/****************************************************************************
 The OM3MediaWidgetImagePlugin is an implementation of the
 PluginMediaWidgetInterface and creates a MediaWidget, based on extension
 of the asset.
 ***************************************************************************/
class MEDIAWIDGET_IMAGE_PLUGINSHARED_EXPORT OM3MediaWidgetImagePlugin : public PluginMediaWidgetInterface
{
    public:
        typedef QMap <std::string, QString> FallbackIcons;
        OM3MediaWidgetImagePlugin (AssetsDockWidget* assetsDockWidget);
        virtual ~OM3MediaWidgetImagePlugin (void) {}

        virtual const std::string& getName (void) const;
        virtual void install (void);
        virtual void initialise (void);
        virtual void shutdown (void);
        virtual void uninstall (void);
        virtual void resetWindowLayout (void) {}
        virtual MediaWidget* createMediaWidget (const AssetMetaData& assetMetaData);
        virtual const SupportedExtensions& getSupportedExtensions (void) const;

    protected:
        // Returns true if the extension is a supported image
        bool OM3MediaWidgetImagePlugin::isSupportedImage (const std::string& extension);

        // Returns the filename of the icon, based on the extension
        const QString& getFallbackIcon (const std::string& extension) const;

        // Checks whether a file exists
        bool fileExist(const QString& fileName);

    private:
        AssetsDockWidget* mAssetsDockWidget;
        SupportedExtensions mSupportedExtensions;
        FallbackIcons mFallbackIcons;
        SupportedExtensions mSupportedImages;
        QString mDummyQString;
};

static OM3MediaWidgetImagePlugin* plugin;

/****************************************************************************
 Provide external access by the OM3 application:
 The function 'createPlugin' creates a static instance of OM3MediaWidgetImagePlugin
 and returns it's pointer
 ***************************************************************************/
extern "C" MEDIAWIDGET_IMAGE_PLUGINSHARED_EXPORT PluginInterface* createPlugin (AssetsDockWidget* assetsDockWidget)
{
    plugin = new OM3MediaWidgetImagePlugin(assetsDockWidget);
    return plugin;
}

/****************************************************************************
 Provide external access by the OM3 application:
 The function 'deletePlugin' deletes the static instance of OM3MediaWidgetImagePlugin
 ***************************************************************************/
extern "C" MEDIAWIDGET_IMAGE_PLUGINSHARED_EXPORT void deletePlugin (void)
{
    delete plugin;
}

#endif
