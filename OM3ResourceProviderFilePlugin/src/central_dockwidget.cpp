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

// Include
#include <QMessageBox>
#include "resource_provider_file_constants.h"
#include "central_dockwidget.h"
#include "file_media_listwidget.h"
#include "media_widget.h"
#include "assets_dockwidget.h"

//****************************************************************************/
CentralDockWidget::CentralDockWidget (const QString& title, QMainWindow* parent, Qt::WindowFlags flags) :
    QDockWidget (title, parent, flags),
    mPlugin(0)
{
    QFile File(QString("dark.qss"));
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    setStyleSheet(styleSheet);

    mFileMediaListWidget = new FileMediaListWidget ();
    mFileMediaListWidget->addContextMenuItem (PLUGIN_CONTEXT_MENU_ACTION_ADD_TO_WORKBENCH, FileMediaListWidget::CONTEXT_MEDIA_ITEMS_SELECTED);
    setWidget(mFileMediaListWidget);
    connect(mFileMediaListWidget, SIGNAL(contextMenuItemSelected(QAction*)), this, SLOT(handleContextMenuItemSelected(QAction*)));
}

//****************************************************************************/
CentralDockWidget::~CentralDockWidget (void)
{
}

//****************************************************************************/
void CentralDockWidget::setPlugin (PluginResourceProviderInterface* plugin)
{
    mPlugin = plugin;
}

//****************************************************************************/
void CentralDockWidget::addResource (AssetMetaData* assetMetaData)
{
    //MediaWidget* mediaWidget = mPlugin->createMediaWidget(assetMetaData, mFileMediaListWidget);
    MediaWidget* mediaWidget = mPlugin->getAssetsDockWidget()->createMediaWidget(assetMetaData, mFileMediaListWidget);
    mFileMediaListWidget->addMediaWidget(mediaWidget);
}

//****************************************************************************/
void CentralDockWidget::removeResources (const QString& topLevelPath)
{
    mFileMediaListWidget->removeMediaWidgetsByOriginAndTopLevelPath(PLUGIN_NAME, topLevelPath);
}

//****************************************************************************/
void CentralDockWidget::handleContextMenuItemSelected(QAction* action)
{
    if (action->text() == PLUGIN_CONTEXT_MENU_ACTION_ADD_TO_WORKBENCH)
    {
        QList<QListWidgetItem*> list = mFileMediaListWidget->selectedItems();
        if (!list.empty())
        {
            MediaWidget* widget;
            foreach (QListWidgetItem* item, list)
            {
                widget = static_cast<MediaWidget*>(mFileMediaListWidget->itemWidget(item));
                mPlugin->getAssetsDockWidget()->addResourceToWorkbench(widget->getAssetMetaData());
            }
        }
    }
}
