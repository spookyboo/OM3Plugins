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

#include <QLabel>
#include <QPixmap>
#include <QImageReader>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMessageBox>
#include "media_image_widget.h"

//****************************************************************************/
MediaImageWidget::MediaImageWidget (AssetMetaData* assetMetaData,
                                    const QPixmap& pixmap,
                                    QWidget* parent) :
    MediaWidget(assetMetaData, parent)
{
    setStyleSheet("background-color: rgba(0,0,0,0)"); // Make it transparent around the edges, so it becomes visible when selected
    QSize size = QSize(128, 128); // Give it a default size
    setMinimumSize(size);
    setMaximumSize(size);
    QLabel* label = new QLabel();
    QLabel* pix = new QLabel();
    QVBoxLayout* layout = new QVBoxLayout;
    label->setText(assetMetaData->baseNameOrReference.c_str());
    pix->setPixmap(pixmap);
    pix->setScaledContents(true);
    layout->addWidget(label, 1);
    layout->addWidget(pix, 1000);
    setLayout(layout);
    setToolTip(assetMetaData->fullQualifiedFileNameOrReference.c_str());

    // Set the action properties
    AssetMetaData::MediaWidgetAction action;
    action.actionText = "Open with Abobe Photoshop (this is a test)";
    mAssetMetaData.mediaWidgetActionVec.push_back(action);
    action.actionText = "Play video (this is a test)";
    mAssetMetaData.mediaWidgetActionVec.push_back(action);
    action.actionText = "Play audio  (this is a test)";
    mAssetMetaData.mediaWidgetActionVec.push_back(action);
}

//****************************************************************************/
void MediaImageWidget::delegateActionByText (const QString& actionText)
{
    // TODO: Perform the action
    QMessageBox::information(0, "MediaImageWidget::delegateActionByText", "Perform the action of this widget");
}
