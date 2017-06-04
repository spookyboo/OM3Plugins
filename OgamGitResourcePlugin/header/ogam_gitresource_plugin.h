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

#ifndef OGAM_GITRESOURCE_PLUGIN_H
#define OGAM_GITRESOURCE_PLUGIN_H

#include <QtCore/qglobal.h>
#include "plugin_resource_interface.h"

// Define import/export
#if defined(OGAM_GITRESOURCE_PLUGIN_LIBRARY)
#  define GITRESOURCE_PLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define GITRESOURCE_PLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

static const std::string GIT_RESOURCE_PLUGIN_NAME = "OgamGitResourcePlugin";
class AssetsDockWidget;
/****************************************************************************
 The OgamGitResourcePlugin is an implementation of the PluginInterface and
 provides access to assets in a Git repository
 ***************************************************************************/
class GITRESOURCE_PLUGINSHARED_EXPORT OgamGitResourcePlugin : public PluginResourceInterface
{
    public:
        OgamGitResourcePlugin (AssetsDockWidget* assetsDockWidget);
        virtual ~OgamGitResourcePlugin (void) {}

        virtual const std::string& getName (void) const;
        virtual void install (void);
        virtual void initialise (void);
        virtual void shutdown (void);
        virtual void uninstall (void);
        virtual void resetWindowLayout (void);
        virtual MediaWidget* addResource (const AssetMetaData& assetMetaData);

    private:
        AssetsDockWidget* mAssetsDockWidget;
        QWidget* mMainWidget;
        QMainWindow* mInnerMain;
};

static OgamGitResourcePlugin* plugin;

/****************************************************************************
 Provide external access by the Ogam application:
 The function 'createPlugin' creates a static instance of OgamGitResourcePlugin
 and returns it's pointer
 ***************************************************************************/
extern "C" GITRESOURCE_PLUGINSHARED_EXPORT PluginInterface* createPlugin (AssetsDockWidget* assetsDockWidget)
{
    plugin = new OgamGitResourcePlugin(assetsDockWidget);
    return plugin;
}

/****************************************************************************
 Provide external access by the Ogam application:
 The function 'deletePlugin' deletes the static instance of OgamGitResourcePlugin
 ***************************************************************************/
extern "C" GITRESOURCE_PLUGINSHARED_EXPORT void deletePlugin (void)
{
    delete plugin;
}

#endif
