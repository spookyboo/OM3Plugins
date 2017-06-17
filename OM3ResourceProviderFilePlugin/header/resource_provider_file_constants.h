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

#ifndef RESOURCE_PROVIDER_FILE_CONSTANTS_H
#define RESOURCE_PROVIDER_FILE_CONSTANTS_H

#include <QString>

//************************************ Misc *******************************************/
static const QString PLUGIN_NAME = QString("OM3ResourceProviderFilePlugin");

//************************************ Icons *******************************************/
static const QString PLUGIN_ICON_PATH = QString("../common/icons/");
static const QString PLUGIN_ICON_FOLDER = QString("folder.png");
static const QString PLUGIN_ICON_ASSET_DEFAULT = QString("asset_default.png");

//************************************ Contextmenu directory actions *******************************************/
static const QString PLUGIN_CONTEXT_MENU_ACTION_ADD_DIR = QString("Add directory");
static const QString PLUGIN_CONTEXT_MENU_ACTION_REMOVE_DIR = QString("Remove directory");

//************************************ Contextmenu media widget actions *******************************************/
static const QString PLUGIN_CONTEXT_MENU_ACTION_ADD_TO_WORKSPACE = QString("Add selected resource(s) to the workspace");

//************************************ Warning, info and error texts *******************************************/
static const QString PLUGIN_INFO_TEXT_ASSET_ADDED_TO_WS = QString("asset(s) added to the workspace");

#endif
