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

#include "assets_dockwidget.h"
#include "git_resource_constants.h"
#include "OM3_gitresource_plugin.h"
#include <QHBoxLayout>
#include <QMessageBox>

//****************************************************************************/
OM3GitResourcePlugin::OM3GitResourcePlugin (AssetsDockWidget* assetsDockWidget) :
    mAssetsDockWidget(assetsDockWidget)
{
    // Create the main widget that is added to the assetsDockWidget's tab
    mMainWidget = new QWidget();

    // Add a main window
    QHBoxLayout* mainLayout = new QHBoxLayout;
    mInnerMain = new QMainWindow();
    mainLayout->addWidget(mInnerMain);
    mMainWidget->setLayout(mainLayout);
}

//****************************************************************************/
const std::string& OM3GitResourcePlugin::getName (void) const
{
    return GIT_RESOURCE_PLUGIN_NAME;
}

//****************************************************************************/
void OM3GitResourcePlugin::install (void)
{
    mAssetsDockWidget->addWidget(mMainWidget, PLUGIN_ICON_PATH + PLUGIN_ICON_FOLDER, "Git");
}

//****************************************************************************/
void OM3GitResourcePlugin::initialise (void)
{
}

//****************************************************************************/
void OM3GitResourcePlugin::shutdown (void)
{
}

//****************************************************************************/
void OM3GitResourcePlugin::uninstall (void)
{
}

//****************************************************************************/
void OM3GitResourcePlugin::resetWindowLayout (void)
{
}

//****************************************************************************/
MediaWidget* OM3GitResourcePlugin::addResource (const AssetMetaData& assetMetaData)
{
    return mAssetsDockWidget->createMediaWidget(assetMetaData);
}
