# OM3MediaWidgetImagePlugin  
The OM3MediaWidgetImagePlugin is an OM3 plugin to create a MediaWidget, which displays an image (for example in the Workbench). 
Based on the extension of an asset, the OM3 application determines which plugin is used to create the MediaWidget. 
This plugin is also used as a fallback, in case no specialized plugin is available. Therefore it is considered a mandatory OM3 plugin.  
  
**Installation:**  
- Compile the project using Qt Creator (or Visual Studio). Notice that Linux is not supported out of the box.  
- Add the entry to the 'plugins.cfg'  file (in __OM3/bin/__). Don't forget to add +1 to the 'numberOfPlugins' property  
- Copy the icons files from __OM3Plugins/OM3MediaWidgetImagePlugin/common/icons__ to __OM3/common/icons__
