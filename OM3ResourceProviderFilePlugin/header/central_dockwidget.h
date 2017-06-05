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

#ifndef CENTRAL_DOCWIDGET_H
#define CENTRAL_DOCWIDGET_H

#include <QtWidgets>
#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include "plugin_resource_provider_interface.h"

QT_BEGIN_NAMESPACE
class QDockWidget;
QT_END_NAMESPACE

/****************************************************************************
 This class represents a DockWidget
 ***************************************************************************/
class MediaListWidget;
class CentralDockWidget : public QDockWidget
{
	Q_OBJECT

	public:
        CentralDockWidget (const QString& title, QMainWindow* parent, Qt::WindowFlags flags = 0);
        ~CentralDockWidget (void);

        /** Set the pointer to the plugin. This is used to communicate with the main OM3 application
         */
        void setPlugin (PluginResourceProviderInterface* plugin);

        /** Add a resource to this central widget. This results in showing a list of widgets containing
         * an image, video, model, audio, etc.
         */
        void addResource (const AssetMetaData& assetMetaData);

        /** Remove all resources belonging to a specific path
         */
        void removeResources (const QString& path);

    private:
        PluginResourceProviderInterface* mPlugin;
        MediaListWidget* mMediaListWidget;
};

#endif

