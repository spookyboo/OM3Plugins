# Ogam
Open Game Asset Management

The OgamMediaWidgetTexturePlugin is an Ogam plugin to create MediaWidgets for images. Based on the extension of an asset, the Ogam
application determines which plugin is used to create the MediaWidget. This plugin also is used as a fallback, in case no specialized
plugin is available. Therefor it is considered a mandatory Ogam plugin.  
  
**Installation:**  
- Compile the project using Qt Creator (or Visual Studio). Notice that Linux is not supported out of the box.  
- Add the entry to the 'plugins.cfg'  file (in Ogam/bin/). Don't forget to add +1 to the 'numberOfPlugins' property  
- Copy the icons files from __OgamPlugins/OgamMediaWidgetTexturePlugin/common/icons__ to __Ogam/common/icons__
