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
#include <QFileDialog>
#include <time.h>
#include "resource_provider_file_constants.h"
#include "file_explorer_dockwidget.h"
#include "central_dockwidget.h"

//****************************************************************************/
FileExplorerDockWidget::FileExplorerDockWidget (const QString& title, QMainWindow* parent, Qt::WindowFlags flags) :
    QDockWidget (title, parent, flags),
    mPlugin(0),
    mCentralDockWidget(0)
{
    mResourceTreeWidget = new QtResourceTreeWidget (PLUGIN_ICON_PATH);
    mResourceTreeWidget->generateUniqueResourceId(); // Start with 0

    // Custom actions
    mResourceTreeWidget->addCustomContextMenuItem(PLUGIN_CONTEXT_MENU_ACTION_ADD_DIR);
    mResourceTreeWidget->addCustomContextMenuItem(PLUGIN_CONTEXT_MENU_ACTION_REMOVE_DIR);
    mResourceTreeWidget->setDeleteResourceContextMenuItemEnabled(false);

    // Toplevel group settings
    mResourceTreeWidget->setCreateTopLevelGroupContextMenuItemEnabled(false);
    mResourceTreeWidget->setTopLevelGroupItemEditable(true);

    // Sub group settings
    mResourceTreeWidget->setCreateSubGroupContextMenuItemEnabled(false);
    mResourceTreeWidget->setSubLevelGroupItemEditable(true);

    // Assets settings
    mResourceTreeWidget->setCreateAssetContextMenuItemEnabled(false);
    mResourceTreeWidget->setImportAssetContextMenuItemEnabled(false);
    mResourceTreeWidget->setDuplicateAssetContextMenuItemEnabled(false);
    mResourceTreeWidget->setAssetItemEditable(false);

    // Handlers
    connect(mResourceTreeWidget, SIGNAL(customContextMenuItemSelected(QString, int)), this, SLOT(handleCustomContextMenuItemSelected(QString, int)));

    // Perform standard functions
    setWidget(mResourceTreeWidget);
}

//****************************************************************************/
FileExplorerDockWidget::~FileExplorerDockWidget (void)
{
}

//****************************************************************************/
void FileExplorerDockWidget::setPlugin (PluginResourceProviderInterface* plugin)
{
    mPlugin = plugin;
}

//****************************************************************************/
void FileExplorerDockWidget::setCentralDockWidget (CentralDockWidget* widget)
{
    mCentralDockWidget = widget;
}


//****************************************************************************/
void FileExplorerDockWidget::handleCustomContextMenuItemSelected (const QString& menuItemText, int resourceId)
{
    if (menuItemText == PLUGIN_CONTEXT_MENU_ACTION_ADD_DIR)
    {
        addDirectory();
    }
    else if (menuItemText == PLUGIN_CONTEXT_MENU_ACTION_REMOVE_DIR)
    {
        removeDirectory(resourceId);
    }
}

//****************************************************************************/
void FileExplorerDockWidget::addDirectory (void)
{
    QString topLevelPath;
    QString path;
    QFileDialog dialog;
    dialog.setFileMode(QFileDialog::Directory);
    if (dialog.exec())
    {
        //QApplication::setOverrideCursor(Qt::WaitCursor);
        //setCursor(QCursor(Qt::WaitCursor));
        //mCentralDockWidget->setCursor(QCursor(Qt::WaitCursor));
        QStringList names = dialog.selectedFiles();
        topLevelPath = names.at(0);
        path = topLevelPath;
        int id = mResourceTreeWidget->generateUniqueResourceId();
        mResourceTreeWidget->addResource (0,
                                          topLevelPath,
                                          topLevelPath,
                                          PLUGIN_ICON_FOLDER,
                                          false,
                                          true);

        // Scan through alle media files
        QString fileName;
        QString fullQualifiedFileNameOrReference;

        /* Iterate through the items in the selected directory.
         * Depending on the define in the project file, resources in subdirectories are
         * included in the result.
         */
        QDirIterator* dirIt;
#ifdef PLUGIN_INCLUDE_SUBDIRS
        dirIt = new QDirIterator(topLevelPath, QDirIterator::Subdirectories);
#else
        dirIt = new QDirIterator(topLevelPath, QDirIterator::NoIteratorFlags); // No subdirs
#endif

        while (dirIt->hasNext())
        {
            dirIt->next();
            if (QFileInfo(dirIt->filePath()).isFile())
            {
                // It is a file
                fileName = dirIt->fileName();
                QFileInfo info = dirIt->fileInfo();
                path = info.absolutePath();
                fullQualifiedFileNameOrReference = path + QString("/") + fileName;
                AssetMetaData assetMetaData;
                assetMetaData.origin = PLUGIN_NAME.toStdString();
                assetMetaData.assetId = 0; // For now it has no meaning
                assetMetaData.topLevelPath = topLevelPath.toStdString();
                assetMetaData.path = path.toStdString();
                assetMetaData.baseNameOrReference = fileName.toStdString();
                assetMetaData.fullQualifiedFileNameOrReference = fullQualifiedFileNameOrReference.toStdString();
                assetMetaData.tags.push_back("test");
                assetMetaData.extension = info.suffix().toStdString();
                time_t rawTime = info.created().toTime_t();
                assetMetaData.dateTimeAssetCreation = *gmtime(&rawTime);
                rawTime = info.lastModified().toTime_t();
                assetMetaData.dateTimeModified = *gmtime(&rawTime);
                assetMetaData.byteSize = info.size();

                // TODO: Other properties

                mCentralDockWidget->addResource(assetMetaData);
            }
        }

        delete dirIt;
        //QApplication::restoreOverrideCursor();
        //mCentralDockWidget->setCursor(QCursor(Qt::ArrowCursor));
        //setCursor(QCursor(Qt::ArrowCursor));
    }
}

//****************************************************************************/
void FileExplorerDockWidget::removeDirectory (int resourceId)
{
    // Get the name (= topLevelPath) of the item
    QString topLevelPath = mResourceTreeWidget->getResourceName(resourceId);

    // Remove all items from the central widget
    mCentralDockWidget->removeResources(topLevelPath);

    // Remove the directory from the resource tree
    mResourceTreeWidget->deleteResource(resourceId, true);
}
