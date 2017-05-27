#include "ogam_fileresource_plugin.h"
#include "file_resource_constants.h"
#include "assets_dockwidget.h"
#include <QHBoxLayout>
#include <QMessageBox>

//****************************************************************************/
OgamFileResourcePlugin::OgamFileResourcePlugin (AssetsDockWidget* assetsDockWidget) :
    mAssetsDockWidget(assetsDockWidget)
{
    // Create the main widget that is added to the assetsDockWidget's tab
    mMainWidget = new QWidget();

    // Add a main window
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mInnerMain = new QMainWindow();
    mainLayout->addWidget(mInnerMain);
    mMainWidget->setLayout(mainLayout);

    // Create DockWidgets in the main window
    mCentralDockWidget = new CentralDockWidget("Main", mInnerMain);
    mFileExplorerDockWidget = new FileExplorerDockWidget("File system", mInnerMain);
    mInnerMain->addDockWidget(Qt::RightDockWidgetArea, mFileExplorerDockWidget);
    mInnerMain->setCentralWidget(mCentralDockWidget);
}

//****************************************************************************/
const std::string& OgamFileResourcePlugin::getName (void) const
{
    return FILE_RESOURCE_PLUGIN_NAME;
}

//****************************************************************************/
void OgamFileResourcePlugin::install (void)
{
    mAssetsDockWidget->addWidget(mMainWidget, PLUGIN_ICON_PATH + PLUGIN_ICON_FOLDER, "Filesystem");
}

//****************************************************************************/
void OgamFileResourcePlugin::initialise (void)
{
}

//****************************************************************************/
void OgamFileResourcePlugin::shutdown (void)
{
}

//****************************************************************************/
void OgamFileResourcePlugin::uninstall (void)
{
}
