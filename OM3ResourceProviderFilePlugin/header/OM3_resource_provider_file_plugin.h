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

#ifndef OM3_RESOURCE_PROVIDER_FILE_PLUGIN_H
#define OM3_RESOURCE_PROVIDER_FILE_PLUGIN_H

#include <QtCore/qglobal.h>
#include "plugin_resource_provider_interface.h"
#include "file_explorer_dockwidget.h"
#include "central_dockwidget.h"

// Define import/export
#if defined(OM3_RESOURCE_PROVIDER_FILE_PLUGIN_LIBRARY)
#  define RESOURCE_PROVIDER_FILE_PLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RESOURCE_PROVIDER_FILE_PLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

static const std::string RESOURCE_PROVIDER_PLUGIN_FILE_NAME = "OM3ResourceProviderFilePlugin";
class AssetsDockWidget;
/****************************************************************************
 The OM3ResourceProviderFilePlugin is an implementation of the PluginInterface and
 provides access to assets on a file system
 ***************************************************************************/
class RESOURCE_PROVIDER_FILE_PLUGINSHARED_EXPORT OM3ResourceProviderFilePlugin : public PluginResourceProviderInterface
{
    public:
        OM3ResourceProviderFilePlugin (AssetsDockWidget* assetsDockWidget);
        virtual ~OM3ResourceProviderFilePlugin (void) {}

        virtual const std::string& getName (void) const;
        virtual void install (void);
        virtual void initialise (void);
        virtual void shutdown (void);
        virtual void uninstall (void);
        virtual void resetWindowLayout (void);
        virtual MediaWidget* createMediaWidget (const AssetMetaData& assetMetaData, QWidget* parent = 0);

    private:
        AssetsDockWidget* mAssetsDockWidget;
        QWidget* mMainWidget;
        QMainWindow* mInnerMain;
        CentralDockWidget* mCentralDockWidget;
        FileExplorerDockWidget* mFileExplorerDockWidget;
};

static OM3ResourceProviderFilePlugin* plugin;

/****************************************************************************
 Provide external access by the OM3 application:
 The function 'createPlugin' creates a static instance of OM3ResourceProviderFilePlugin
 and returns it's pointer
 ***************************************************************************/
extern "C" RESOURCE_PROVIDER_FILE_PLUGINSHARED_EXPORT PluginInterface* createPlugin (AssetsDockWidget* assetsDockWidget)
{
    plugin = new OM3ResourceProviderFilePlugin(assetsDockWidget);
    return plugin;
}

/****************************************************************************
 Provide external access by the OM3 application:
 The function 'deletePlugin' deletes the static instance of OM3ResourceProviderFilePlugin
 ***************************************************************************/
extern "C" RESOURCE_PROVIDER_FILE_PLUGINSHARED_EXPORT void deletePlugin (void)
{
    delete plugin;
}

#endif
