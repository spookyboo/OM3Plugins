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
#include "ogam_gitresource_plugin.h"
#include <QHBoxLayout>
#include <QMessageBox>

//****************************************************************************/
OgamGitResourcePlugin::OgamGitResourcePlugin (AssetsDockWidget* assetsDockWidget) :
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
const std::string& OgamGitResourcePlugin::getName (void) const
{
    return GIT_RESOURCE_PLUGIN_NAME;
}

//****************************************************************************/
void OgamGitResourcePlugin::install (void)
{
    mAssetsDockWidget->addWidget(mMainWidget, PLUGIN_ICON_PATH + PLUGIN_ICON_FOLDER, "Git");
}

//****************************************************************************/
void OgamGitResourcePlugin::initialise (void)
{
}

//****************************************************************************/
void OgamGitResourcePlugin::shutdown (void)
{
}

//****************************************************************************/
void OgamGitResourcePlugin::uninstall (void)
{
}

//****************************************************************************/
void OgamGitResourcePlugin::resetWindowLayout (void)
{
}

//****************************************************************************/
MediaWidget* OgamGitResourcePlugin::addResource (const AssetMetaData& assetMetaData)
{
    return mAssetsDockWidget->createMediaWidget(assetMetaData);
}
