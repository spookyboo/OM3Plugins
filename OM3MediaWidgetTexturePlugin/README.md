# OM3MediaWidgetTexturePlugin  
The OM3MediaWidgetTexturePlugin is an OM3 plugin to create MediaWidgets to display images (for example in the Workbench). 
Based on the extension of an asset, the OM3 application determines which plugin is used to create the MediaWidget. 
This plugin also is used as a fallback, in case no specialized plugin is available. Therefore it is considered a mandatory OM3 plugin.  
  
**Installation:**  
- Compile the project using Qt Creator (or Visual Studio). Notice that Linux is not supported out of the box.  
- Add the entry to the 'plugins.cfg'  file (in __OM3/bin/__). Don't forget to add +1 to the 'numberOfPlugins' property  
- Copy the icons files from __OM3Plugins/OM3MediaWidgetTexturePlugin/common/icons__ to __OM3/common/icons__
