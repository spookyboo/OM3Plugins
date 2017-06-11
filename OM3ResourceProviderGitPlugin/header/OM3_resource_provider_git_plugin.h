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

#ifndef OM3_RESOURCE_PROVIDER_GIT_PLUGINSHARED_EXPORT_H
#define OM3_RESOURCE_PROVIDER_GIT_PLUGINSHARED_EXPORT_H

#include <QtCore/qglobal.h>
#include "plugin_resource_provider_interface.h"

// Define import/export
#if defined(OM3_RESOURCE_PROVIDER_GIT_PLUGIN_LIBRARY)
#  define RESOURCE_PROVIDER_GIT_PLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define RESOURCE_PROVIDER_GIT_PLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

static const std::string RESOURCE_PROVIDER_GIT_PLUGIN_NAME = "OM3ResourceProviderGitPlugin";
class AssetsDockWidget;
/****************************************************************************
 The OM3ResourceProviderGitPlugin is an implementation of the PluginInterface and
 provides access to assets in a Git repository
 ***************************************************************************/
class RESOURCE_PROVIDER_GIT_PLUGINSHARED_EXPORT OM3ResourceProviderGitPlugin : public PluginResourceProviderInterface
{
    public:
        OM3ResourceProviderGitPlugin (AssetsDockWidget* assetsDockWidget);
        virtual ~OM3ResourceProviderGitPlugin (void) {}

        // Mandatory functions
        virtual const std::string& getName (void) const;
        virtual void install (void);
        virtual void initialise (void);
        virtual void shutdown (void);
        virtual void uninstall (void);
        virtual void resetWindowLayout (void);

    private:
        QWidget* mMainWidget;
        QMainWindow* mInnerMain;
};

static OM3ResourceProviderGitPlugin* plugin;

/****************************************************************************
 Provide external access by the OM3 application:
 The function 'createPlugin' creates a static instance of OM3ResourceProviderGitPlugin
 and returns it's pointer
 ***************************************************************************/
extern "C" RESOURCE_PROVIDER_GIT_PLUGINSHARED_EXPORT PluginInterface* createPlugin (AssetsDockWidget* assetsDockWidget)
{
    plugin = new OM3ResourceProviderGitPlugin(assetsDockWidget);
    return plugin;
}

/****************************************************************************
 Provide external access by the OM3 application:
 The function 'deletePlugin' deletes the static instance of OM3ResourceProviderGitPlugin
 ***************************************************************************/
extern "C" RESOURCE_PROVIDER_GIT_PLUGINSHARED_EXPORT void deletePlugin (void)
{
    delete plugin;
}

#endif
