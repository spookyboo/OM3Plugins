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
#include <QHBoxLayout>
#include <QLineEdit>
#include "media_texture_widget.h"

//****************************************************************************/
MediaTextureWidget::MediaTextureWidget (const AssetMetaData& assetMetaData,
                                        const QPixmap& pixmap,
                                        QWidget* parent) :
    MediaWidget(assetMetaData, parent)
{
    QLabel* label = new QLabel();
    QHBoxLayout* layout = new QHBoxLayout;
    label->setPixmap(pixmap);
    label->setScaledContents(true);
    layout->addWidget(label);
    setLayout(layout);
    setMouseTracking(true);
}
