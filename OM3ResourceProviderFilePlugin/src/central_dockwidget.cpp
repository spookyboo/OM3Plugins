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
#include "media_listwidget.h"
#include "media_widget.h"

//****************************************************************************/
CentralDockWidget::CentralDockWidget (const QString& title, QMainWindow* parent, Qt::WindowFlags flags) :
    QDockWidget (title, parent, flags),
    mPlugin(0)
{
    mMediaListWidget = new MediaListWidget ();
    setWidget(mMediaListWidget);
    //connect(mMediaListWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(handleSelected(QListWidgetItem*)));
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
void CentralDockWidget::addResource (const AssetMetaData& assetMetaData)
{
    MediaWidget* mediaWidget = mPlugin->createMediaWidget(assetMetaData, mMediaListWidget);
    mMediaListWidget->addMediaWidget(mediaWidget);
}

//****************************************************************************/
void CentralDockWidget::removeResources (const QString& topLevelPath)
{
    mMediaListWidget->removeMediaWidgetsByOriginAndTopLevelPath(PLUGIN_NAME, topLevelPath);
}

//****************************************************************************/
void CentralDockWidget::handleSelected(QListWidgetItem* item)
{
    QMessageBox::information(0, QString("QtDefaultTextureWidget::handleSelected"), QString("Item selected"));
}
